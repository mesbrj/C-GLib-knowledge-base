## Features Demonstrated

### Hash Tables (GHashTable)
**Computer Science Fundamentals**: [Hash Table Data Structure](https://en.wikipedia.org/wiki/Hash_table)

- **Hash Functions**: Demonstrates string hashing and collision handling - [Hash Function Theory](https://en.wikipedia.org/wiki/Hash_function)
- **Associative Arrays**: Key-value mapping with O(1) average lookup complexity
- **Load Factor Management**: Automatic resizing and rehashing - [Hash Table Load Factor](https://en.wikipedia.org/wiki/Hash_table#Load_factor)
- **Memory Safety**: Custom destructors and automatic cleanup
- **Iteration Patterns**: Hash table traversal and filtering algorithms

**Key Learning Outcomes**:
- Understanding hash function design and collision resolution
- Analyzing average vs worst-case time complexity
- Implementing custom hash and equality functions
- Space-time tradeoff considerations

## Comprehensive Code Examples and Usage

This section provides direct, practical code examples that demonstrate real-world usage patterns for each GLib feature, going beyond the basic demonstrations in the interactive program.

### GHashTable (Hash Tables) - Advanced Examples

#### Multi-Value Hash Table with Custom Types
```c
#include <glib.h>

// Student record with multiple courses
typedef struct {
    char *name;
    int age;
    GList *courses;  // List of course names
    GHashTable *grades;  // Course -> Grade mapping
} Student;

// Course grade structure
typedef struct {
    char *course_name;
    double grade;
    int credits;
} CourseGrade;

// Create student
Student* student_new(const char *name, int age) {
    Student *student = g_malloc(sizeof(Student));
    student->name = g_strdup(name);
    student->age = age;
    student->courses = NULL;
    student->grades = g_hash_table_new_full(g_str_hash, g_str_equal, 
                                           g_free, g_free);
    return student;
}

// Free student
void student_free(Student *student) {
    if (student) {
        g_free(student->name);
        g_list_free_full(student->courses, g_free);
        g_hash_table_destroy(student->grades);
        g_free(student);
    }
}

// Add course to student
void student_add_course(Student *student, const char *course, double grade, int credits) {
    // Add to courses list
    student->courses = g_list_prepend(student->courses, g_strdup(course));
    
    // Add grade information
    CourseGrade *cg = g_malloc(sizeof(CourseGrade));
    cg->course_name = g_strdup(course);
    cg->grade = grade;
    cg->credits = credits;
    
    g_hash_table_insert(student->grades, g_strdup(course), cg);
}

// Calculate GPA
double student_calculate_gpa(Student *student) {
    double total_points = 0.0;
    int total_credits = 0;
    
    GHashTableIter iter;
    gpointer key, value;
    
    g_hash_table_iter_init(&iter, student->grades);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        CourseGrade *cg = (CourseGrade*)value;
        total_points += cg->grade * cg->credits;
        total_credits += cg->credits;
    }
    
    return total_credits > 0 ? total_points / total_credits : 0.0;
}

// University database example
void demonstrate_university_database() {
    // Create university database (student_id -> Student)
    GHashTable *university = g_hash_table_new_full(g_str_hash, g_str_equal,
                                                   g_free, (GDestroyNotify)student_free);
    
    // Create students with courses
    Student *alice = student_new("Alice Cooper", 20);
    student_add_course(alice, "Computer Science 101", 3.7, 4);
    student_add_course(alice, "Mathematics 201", 3.9, 3);
    student_add_course(alice, "Physics 101", 3.2, 4);
    g_hash_table_insert(university, g_strdup("STU001"), alice);
    
    Student *bob = student_new("Bob Dylan", 21);
    student_add_course(bob, "Computer Science 101", 3.5, 4);
    student_add_course(bob, "English Literature", 3.8, 3);
    student_add_course(bob, "History 101", 3.6, 3);
    g_hash_table_insert(university, g_strdup("STU002"), bob);
    
    Student *carol = student_new("Carol King", 19);
    student_add_course(carol, "Mathematics 201", 4.0, 3);
    student_add_course(carol, "Computer Science 201", 3.9, 4);
    student_add_course(carol, "Statistics 101", 3.7, 3);
    g_hash_table_insert(university, g_strdup("STU003"), carol);
    
    // Query database
    g_print("University Database - %d students enrolled\n\n", 
            g_hash_table_size(university));
    
    // Look up specific student
    Student *student = g_hash_table_lookup(university, "STU001");
    if (student) {
        g_print("Student: %s (Age: %d)\n", student->name, student->age);
        g_print("GPA: %.2f\n", student_calculate_gpa(student));
        g_print("Courses: %d\n", g_list_length(student->courses));
    }
    
    // Iterate through all students
    g_print("\nAll Students:\n");
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, university);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *student_id = (char*)key;
        Student *s = (Student*)value;
        g_print("%s: %s (GPA: %.2f)\n", student_id, s->name, 
                student_calculate_gpa(s));
    }
    
    // Cleanup automatically handled by hash table destroy
    g_hash_table_destroy(university);
}
```

#### Advanced Hash Table Operations
```c
// Custom hash function for case-insensitive strings
guint case_insensitive_hash(gconstpointer key) {
    const char *str = (const char*)key;
    char *lower = g_ascii_strdown(str, -1);
    guint hash = g_str_hash(lower);
    g_free(lower);
    return hash;
}

// Custom equality function for case-insensitive strings
gboolean case_insensitive_equal(gconstpointer a, gconstpointer b) {
    return g_ascii_strcasecmp((const char*)a, (const char*)b) == 0;
}

// Configuration manager example
typedef struct {
    GHashTable *string_values;
    GHashTable *int_values;
    GHashTable *double_values;
} ConfigManager;

ConfigManager* config_manager_new() {
    ConfigManager *config = g_malloc(sizeof(ConfigManager));
    
    // Case-insensitive string keys
    config->string_values = g_hash_table_new_full(case_insensitive_hash,
                                                  case_insensitive_equal,
                                                  g_free, g_free);
    config->int_values = g_hash_table_new_full(case_insensitive_hash,
                                               case_insensitive_equal,
                                               g_free, g_free);
    config->double_values = g_hash_table_new_full(case_insensitive_hash,
                                                  case_insensitive_equal,
                                                  g_free, g_free);
    return config;
}

void config_manager_free(ConfigManager *config) {
    if (config) {
        g_hash_table_destroy(config->string_values);
        g_hash_table_destroy(config->int_values);
        g_hash_table_destroy(config->double_values);
        g_free(config);
    }
}

// Set configuration values
void config_set_string(ConfigManager *config, const char *key, const char *value) {
    g_hash_table_insert(config->string_values, g_strdup(key), g_strdup(value));
}

void config_set_int(ConfigManager *config, const char *key, int value) {
    g_hash_table_insert(config->int_values, g_strdup(key), g_memdup2(&value, sizeof(int)));
}

void config_set_double(ConfigManager *config, const char *key, double value) {
    g_hash_table_insert(config->double_values, g_strdup(key), g_memdup2(&value, sizeof(double)));
}

// Get configuration values with defaults
const char* config_get_string(ConfigManager *config, const char *key, const char *default_value) {
    const char *value = g_hash_table_lookup(config->string_values, key);
    return value ? value : default_value;
}

int config_get_int(ConfigManager *config, const char *key, int default_value) {
    int *value = g_hash_table_lookup(config->int_values, key);
    return value ? *value : default_value;
}

double config_get_double(ConfigManager *config, const char *key, double default_value) {
    double *value = g_hash_table_lookup(config->double_values, key);
    return value ? *value : default_value;
}

void demonstrate_config_manager() {
    ConfigManager *config = config_manager_new();
    
    // Set configuration (case-insensitive keys)
    config_set_string(config, "DATABASE_URL", "postgresql://localhost:5432/mydb");
    config_set_string(config, "log_level", "INFO");
    config_set_int(config, "MAX_CONNECTIONS", 100);
    config_set_int(config, "timeout_seconds", 30);
    config_set_double(config, "CACHE_SIZE_GB", 2.5);
    
    // Retrieve configuration (demonstrating case insensitivity)
    g_print("Config Values:\n");
    g_print("Database: %s\n", config_get_string(config, "database_url", "not set"));
    g_print("Log Level: %s\n", config_get_string(config, "LOG_LEVEL", "DEBUG"));
    g_print("Max Connections: %d\n", config_get_int(config, "max_connections", 50));
    g_print("Timeout: %d seconds\n", config_get_int(config, "TIMEOUT_SECONDS", 10));
    g_print("Cache Size: %.1f GB\n", config_get_double(config, "cache_size_gb", 1.0));
    
    // Non-existent key with default
    g_print("Unknown Setting: %s\n", config_get_string(config, "unknown_key", "default_value"));
    
    config_manager_free(config);
}
```