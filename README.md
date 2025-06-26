# GLib Knowledge Base - Educational Data Structures & Algorithms Demo

A comprehensive educational demonstration program showcasing fundamental data structures and algorithms through GLib's robust implementations, including advanced GObject features for object-oriented programming and event-driven architecture. This project serves as a hands-on learning tool for computer science students and developers wanting to understand core algorithmic concepts in a practical context.

## Current Project Status

- Double Linked Lists (GList) with comprehensive demos
- Hash Tables (GHashTable) with student database examples  
- Async Queues (GAsyncQueue) with multi-threading demos
- GObject basics (Object-oriented programming in C)
- Signals & Properties (Event-driven programming)
- Interactive menu system with all 5 demo modules
- Docker containerization
- Comprehensive educational documentation

## Educational Objectives

This project demonstrates five fundamental concepts in computer science:

### 1. Dynamic Data Structures (Linked Lists)
**Academic Context**: Linear data structures and pointer manipulation  
**Algorithmic Concepts**: Sequential access, dynamic memory allocation, list traversal algorithms

### 2. Hash-Based Data Structures (Hash Tables) 
**Academic Context**: Associative arrays and hash function theory  
**Algorithmic Concepts**: Hash collision resolution, average O(1) lookup complexity, load factor optimization

### 3. Concurrent Programming Primitives (Thread-Safe Queues)
**Academic Context**: Operating systems, concurrent programming, and synchronization  
**Algorithmic Concepts**: Producer-consumer patterns, thread synchronization, deadlock prevention

### 4. Object-Oriented Programming in C (GObject System)
**Academic Context**: OOP principles, design patterns, and software architecture  
**Programming Concepts**: Inheritance, polymorphism, encapsulation, type systems, memory management

### 5. Event-Driven Programming (Signals and Properties)
**Academic Context**: Observer pattern, event-driven architecture, and reactive programming  
**Programming Concepts**: Signal/slot mechanism, property change notifications, interface design

## Features Demonstrated

### Double Linked Lists (GList)
**Computer Science Fundamentals**: [Doubly linked list Data Structure](https://en.wikipedia.org/wiki/Doubly_linked_list)

- **Dynamic Collections**: Demonstrates dynamic memory allocation and pointer-based data structures
- **List Operations**: Insertion (O(1) prepend, O(n) append), deletion (O(n)), traversal (O(n))
- **Sorting Algorithms**: In-place sorting with custom comparators - [Comparison Sorting](https://en.wikipedia.org/wiki/Comparison_sort)
- **Search Algorithms**: Linear search with custom predicates - [Linear Search](https://en.wikipedia.org/wiki/Linear_search)
- **Memory Management**: Automatic cleanup demonstrating [RAII principles](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization)

**Key Learning Outcomes**:
- Understanding pointer manipulation and memory management
- Time complexity analysis of list operations
- Implementation of custom comparison functions
- Memory leak prevention techniques

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

### Async Queues (GAsyncQueue)
**Computer Science Fundamentals**: [Concurrent Programming](https://en.wikipedia.org/wiki/Concurrent_computing)

- **Thread Safety**: Lock-free data structures and atomic operations - [Thread Safety](https://en.wikipedia.org/wiki/Thread_safety)
- **Producer-Consumer Pattern**: Classic synchronization problem - [Producer-Consumer Problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
- **Blocking vs Non-blocking**: Different queue operation modes - [Blocking Queue](https://en.wikipedia.org/wiki/Blocking_queue)
- **Timeout Handling**: Robust concurrent programming with timeouts
- **Deadlock Prevention**: Safe multi-threaded communication - [Deadlock Prevention](https://en.wikipedia.org/wiki/Deadlock_prevention_algorithms)

**Key Learning Outcomes**:
- Understanding concurrent programming challenges
- Implementing thread-safe data structures
- Analyzing synchronization primitives
- Designing robust multi-threaded applications

### GObject Basics (Object-Oriented Programming in C)
**Computer Science Fundamentals**: [Object-Oriented Programming](https://en.wikipedia.org/wiki/Object-oriented_programming)

- **Type System**: Runtime type information and introspection - [Type System Theory](https://en.wikipedia.org/wiki/Type_system)
- **Inheritance**: Single inheritance hierarchy with method overriding - [Inheritance in OOP](https://en.wikipedia.org/wiki/Inheritance_(object-oriented_programming))
- **Polymorphism**: Dynamic method dispatch and type casting - [Polymorphism](https://en.wikipedia.org/wiki/Polymorphism_(computer_science))
- **Memory Management**: Reference counting and automatic cleanup - [Memory Management](https://en.wikipedia.org/wiki/Memory_management)
- **Encapsulation**: Private data with public interfaces - [Encapsulation](https://en.wikipedia.org/wiki/Encapsulation_(computer_science))

**Key Learning Outcomes**:
- Understanding object-oriented design in C
- Implementing inheritance without native language support
- Managing object lifecycles and references
- Designing type-safe APIs in C

### Signals and Properties (Event-Driven Programming)
**Computer Science Fundamentals**: [Observer Pattern](https://en.wikipedia.org/wiki/Observer_pattern) and [Event-Driven Programming](https://en.wikipedia.org/wiki/Event-driven_programming)

- **Signal System**: Observer pattern implementation with type safety - [Signal/Slot Pattern](https://en.wikipedia.org/wiki/Signals_and_slots)
- **Property System**: Automatic change notifications and validation - [Property Pattern](https://en.wikipedia.org/wiki/Property_(programming))
- **Interface Design**: Contract-based programming with interfaces - [Interface Segregation](https://en.wikipedia.org/wiki/Interface_segregation_principle)
- **Event Handling**: Asynchronous communication between objects - [Event Handling](https://en.wikipedia.org/wiki/Event_handling)
- **Loose Coupling**: Decoupled architecture with message passing - [Loose Coupling](https://en.wikipedia.org/wiki/Loose_coupling)

**Key Learning Outcomes**:
- Understanding event-driven architecture patterns
- Implementing observer pattern in C
- Designing reactive user interfaces
- Managing complex object interactions

## Comprehensive Code Examples and Usage

This section provides direct, practical code examples that demonstrate real-world usage patterns for each GLib feature, going beyond the basic demonstrations in the interactive program.

### 1. GList (Doubly Linked Lists) - Advanced Examples

#### Basic Operations with Custom Data
```c
#include <glib.h>
#include <stdio.h>

// Custom data structure
typedef struct {
    int id;
    char *name;
    double salary;
} Employee;

// Create employee
Employee* employee_new(int id, const char *name, double salary) {
    Employee *emp = g_malloc(sizeof(Employee));
    emp->id = id;
    emp->name = g_strdup(name);
    emp->salary = salary;
    return emp;
}

// Free employee
void employee_free(Employee *emp) {
    if (emp) {
        g_free(emp->name);
        g_free(emp);
    }
}

// Comparison function for sorting by salary
gint compare_by_salary(gconstpointer a, gconstpointer b) {
    const Employee *emp1 = (const Employee*)a;
    const Employee *emp2 = (const Employee*)b;
    
    if (emp1->salary < emp2->salary) return -1;
    if (emp1->salary > emp2->salary) return 1;
    return 0;
}

// Find employee by ID
gboolean find_by_id(gconstpointer data, gconstpointer user_data) {
    const Employee *emp = (const Employee*)data;
    int target_id = GPOINTER_TO_INT(user_data);
    return emp->id == target_id;
}

// Example usage
void demonstrate_glist_advanced() {
    GList *employees = NULL;
    
    // Build employee list
    employees = g_list_prepend(employees, employee_new(101, "Alice Johnson", 75000.0));
    employees = g_list_prepend(employees, employee_new(102, "Bob Smith", 82000.0));
    employees = g_list_prepend(employees, employee_new(103, "Carol Williams", 68000.0));
    employees = g_list_prepend(employees, employee_new(104, "David Brown", 91000.0));
    
    g_print("Total employees: %d\n", g_list_length(employees));
    
    // Sort by salary (ascending)
    employees = g_list_sort(employees, compare_by_salary);
    
    // Print sorted list
    g_print("\nEmployees sorted by salary:\n");
    for (GList *l = employees; l != NULL; l = l->next) {
        Employee *emp = (Employee*)l->data;
        g_print("ID: %d, Name: %s, Salary: $%.2f\n", 
                emp->id, emp->name, emp->salary);
    }
    
    // Find specific employee
    GList *found = g_list_find_custom(employees, GINT_TO_POINTER(102), find_by_id);
    if (found) {
        Employee *emp = (Employee*)found->data;
        g_print("\nFound employee: %s (ID: %d)\n", emp->name, emp->id);
    }
    
    // Remove employee with ID 103
    GList *to_remove = g_list_find_custom(employees, GINT_TO_POINTER(103), find_by_id);
    if (to_remove) {
        employee_free((Employee*)to_remove->data);
        employees = g_list_delete_link(employees, to_remove);
    }
    
    // Cleanup
    g_list_free_full(employees, (GDestroyNotify)employee_free);
}
```

#### Performance Analysis and Best Practices
```c
// Efficient list building (prepend is O(1), append is O(n))
GList *build_large_list_efficiently(int size) {
    GList *list = NULL;
    
    // BAD: O(n²) complexity
    // for (int i = 0; i < size; i++) {
    //     list = g_list_append(list, GINT_TO_POINTER(i));
    // }
    
    // GOOD: O(n) complexity, then reverse if order matters
    for (int i = 0; i < size; i++) {
        list = g_list_prepend(list, GINT_TO_POINTER(i));
    }
    
    // Reverse to maintain original order (still O(n) total)
    list = g_list_reverse(list);
    return list;
}

// Batch operations for better performance
void demonstrate_batch_operations() {
    GList *numbers = NULL;
    
    // Build list of 1000 numbers efficiently
    numbers = build_large_list_efficiently(1000);
    
    // Filter even numbers using custom function
    GList *evens = NULL;
    for (GList *l = numbers; l != NULL; l = l->next) {
        int value = GPOINTER_TO_INT(l->data);
        if (value % 2 == 0) {
            evens = g_list_prepend(evens, l->data);
        }
    }
    evens = g_list_reverse(evens);
    
    g_print("Original list length: %d\n", g_list_length(numbers));
    g_print("Even numbers count: %d\n", g_list_length(evens));
    
    // Cleanup
    g_list_free(numbers);
    g_list_free(evens);  // Don't free data, it's shared
}
```

### 2. GHashTable (Hash Tables) - Advanced Examples

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

### 3. GAsyncQueue (Thread-Safe Queues) - Advanced Examples

#### Producer-Consumer with Multiple Threads
```c
#include <glib.h>
#include <stdio.h>
#include <unistd.h>

// Task structure for work queue
typedef struct {
    int task_id;
    char *description;
    int processing_time;  // Simulated work time in seconds
    GDateTime *created_at;
} Task;

// Create task
Task* task_new(int id, const char *description, int processing_time) {
    Task *task = g_malloc(sizeof(Task));
    task->task_id = id;
    task->description = g_strdup(description);
    task->processing_time = processing_time;
    task->created_at = g_date_time_new_now_local();
    return task;
}

// Free task
void task_free(Task *task) {
    if (task) {
        g_free(task->description);
        g_date_time_unref(task->created_at);
        g_free(task);
    }
}

// Producer thread data
typedef struct {
    GAsyncQueue *queue;
    int tasks_to_produce;
    int producer_id;
    gboolean *shutdown_flag;
} ProducerData;

// Consumer thread data
typedef struct {
    GAsyncQueue *queue;
    int consumer_id;
    gboolean *shutdown_flag;
    GMutex *stats_mutex;
    int *tasks_processed;
} ConsumerData;

// Producer thread function
gpointer producer_thread(gpointer data) {
    ProducerData *pd = (ProducerData*)data;
    
    g_print("Producer %d: Starting, will produce %d tasks\n", 
            pd->producer_id, pd->tasks_to_produce);
    
    for (int i = 0; i < pd->tasks_to_produce && !*(pd->shutdown_flag); i++) {
        // Create task with random processing time
        int proc_time = g_random_int_range(1, 5);
        char *desc = g_strdup_printf("Task from Producer %d", pd->producer_id);
        Task *task = task_new(i + 1, desc, proc_time);
        g_free(desc);
        
        // Add to queue
        g_async_queue_push(pd->queue, task);
        g_print("Producer %d: Produced task %d (processing time: %d seconds)\n",
                pd->producer_id, task->task_id, proc_time);
        
        // Simulate production delay
        g_usleep(g_random_int_range(500000, 2000000));  // 0.5-2 seconds
    }
    
    g_print("Producer %d: Finished producing tasks\n", pd->producer_id);
    return NULL;
}

// Consumer thread function
gpointer consumer_thread(gpointer data) {
    ConsumerData *cd = (ConsumerData*)data;
    
    g_print("Consumer %d: Starting\n", cd->consumer_id);
    
    while (!*(cd->shutdown_flag)) {
        // Try to get task with timeout
        Task *task = g_async_queue_timeout_pop(cd->queue, 3000000);  // 3 second timeout
        
        if (task) {
            g_print("Consumer %d: Processing task %d - %s\n",
                    cd->consumer_id, task->task_id, task->description);
            
            // Simulate task processing
            g_usleep(task->processing_time * 1000000);  // Convert to microseconds
            
            // Update statistics
            g_mutex_lock(cd->stats_mutex);
            (*(cd->tasks_processed))++;
            g_mutex_unlock(cd->stats_mutex);
            
            g_print("Consumer %d: Completed task %d\n", cd->consumer_id, task->task_id);
            task_free(task);
        } else {
            g_print("Consumer %d: Timeout waiting for task\n", cd->consumer_id);
        }
    }
    
    g_print("Consumer %d: Shutting down\n", cd->consumer_id);
    return NULL;
}

// Advanced producer-consumer example
void demonstrate_advanced_producer_consumer() {
    // Create async queue
    GAsyncQueue *task_queue = g_async_queue_new_full((GDestroyNotify)task_free);
    
    // Shared data
    gboolean shutdown_flag = FALSE;
    int tasks_processed = 0;
    GMutex stats_mutex;
    g_mutex_init(&stats_mutex);
    
    // Create producer data
    const int num_producers = 2;
    const int num_consumers = 3;
    const int tasks_per_producer = 5;
    
    ProducerData producer_data[num_producers];
    ConsumerData consumer_data[num_consumers];
    
    // Initialize producer data
    for (int i = 0; i < num_producers; i++) {
        producer_data[i].queue = task_queue;
        producer_data[i].tasks_to_produce = tasks_per_producer;
        producer_data[i].producer_id = i + 1;
        producer_data[i].shutdown_flag = &shutdown_flag;
    }
    
    // Initialize consumer data
    for (int i = 0; i < num_consumers; i++) {
        consumer_data[i].queue = task_queue;
        consumer_data[i].consumer_id = i + 1;
        consumer_data[i].shutdown_flag = &shutdown_flag;
        consumer_data[i].stats_mutex = &stats_mutex;
        consumer_data[i].tasks_processed = &tasks_processed;
    }
    
    // Create threads
    GThread *producers[num_producers];
    GThread *consumers[num_consumers];
    
    g_print("Starting %d producers and %d consumers\n", num_producers, num_consumers);
    
    // Start producer threads
    for (int i = 0; i < num_producers; i++) {
        producers[i] = g_thread_new(NULL, producer_thread, &producer_data[i]);
    }
    
    // Start consumer threads
    for (int i = 0; i < num_consumers; i++) {
        consumers[i] = g_thread_new(NULL, consumer_thread, &consumer_data[i]);
    }
    
    // Wait for all producers to finish
    for (int i = 0; i < num_producers; i++) {
        g_thread_join(producers[i]);
    }
    
    g_print("All producers finished. Waiting for queue to empty...\n");
    
    // Wait for queue to empty
    while (g_async_queue_length(task_queue) > 0) {
        g_usleep(500000);  // 0.5 seconds
    }
    
    // Give consumers a bit more time, then shutdown
    g_usleep(2000000);  // 2 seconds
    shutdown_flag = TRUE;
    
    // Wait for all consumers to finish
    for (int i = 0; i < num_consumers; i++) {
        g_thread_join(consumers[i]);
    }
    
    g_print("\nFinal Statistics:\n");
    g_print("Total tasks produced: %d\n", num_producers * tasks_per_producer);
    g_print("Total tasks processed: %d\n", tasks_processed);
    g_print("Remaining tasks in queue: %d\n", g_async_queue_length(task_queue));
    
    // Cleanup
    g_mutex_clear(&stats_mutex);
    g_async_queue_unref(task_queue);
}
```

#### Load Balancing and Priority Queues
```c
// Priority task structure
typedef struct {
    Task *task;
    int priority;  // Higher number = higher priority
} PriorityTask;

PriorityTask* priority_task_new(Task *task, int priority) {
    PriorityTask *pt = g_malloc(sizeof(PriorityTask));
    pt->task = task;
    pt->priority = priority;
    return pt;
}

void priority_task_free(PriorityTask *pt) {
    if (pt) {
        task_free(pt->task);
        g_free(pt);
    }
}

// Load balancer using multiple queues
typedef struct {
    GAsyncQueue **queues;
    int num_queues;
    int current_queue;
    GMutex mutex;
} LoadBalancer;

LoadBalancer* load_balancer_new(int num_queues) {
    LoadBalancer *lb = g_malloc(sizeof(LoadBalancer));
    lb->num_queues = num_queues;
    lb->current_queue = 0;
    lb->queues = g_malloc(sizeof(GAsyncQueue*) * num_queues);
    
    for (int i = 0; i < num_queues; i++) {
        lb->queues[i] = g_async_queue_new_full((GDestroyNotify)task_free);
    }
    
    g_mutex_init(&lb->mutex);
    return lb;
}

void load_balancer_free(LoadBalancer *lb) {
    if (lb) {
        for (int i = 0; i < lb->num_queues; i++) {
            g_async_queue_unref(lb->queues[i]);
        }
        g_free(lb->queues);
        g_mutex_clear(&lb->mutex);
        g_free(lb);
    }
}

// Round-robin task distribution
void load_balancer_add_task(LoadBalancer *lb, Task *task) {
    g_mutex_lock(&lb->mutex);
    
    // Add to current queue
    g_async_queue_push(lb->queues[lb->current_queue], task);
    
    // Move to next queue for round-robin
    lb->current_queue = (lb->current_queue + 1) % lb->num_queues;
    
    g_mutex_unlock(&lb->mutex);
}

// Get task from least loaded queue
Task* load_balancer_get_task(LoadBalancer *lb) {
    int min_length = G_MAXINT;
    int best_queue = 0;
    
    // Find queue with minimum length
    for (int i = 0; i < lb->num_queues; i++) {
        int length = g_async_queue_length(lb->queues[i]);
        if (length < min_length) {
            min_length = length;
            best_queue = i;
        }
    }
    
    // Try to get task from best queue
    return g_async_queue_try_pop(lb->queues[best_queue]);
}

void demonstrate_load_balancing() {
    LoadBalancer *lb = load_balancer_new(3);
    
    // Add tasks to load balancer
    for (int i = 0; i < 10; i++) {
        char *desc = g_strdup_printf("Load balanced task %d", i + 1);
        Task *task = task_new(i + 1, desc, g_random_int_range(1, 4));
        g_free(desc);
        
        load_balancer_add_task(lb, task);
        g_print("Added task %d to load balancer\n", i + 1);
    }
    
    // Show queue distributions
    g_print("\nQueue distributions:\n");
    for (int i = 0; i < lb->num_queues; i++) {
        g_print("Queue %d: %d tasks\n", i, g_async_queue_length(lb->queues[i]));
    }
    
    // Process tasks from least loaded queues
    g_print("\nProcessing tasks:\n");
    Task *task;
    while ((task = load_balancer_get_task(lb)) != NULL) {
        g_print("Processing: %s\n", task->description);
        task_free(task);
    }
    
    load_balancer_free(lb);
}
```

### 4. GObject System - Advanced Examples

#### Custom Object with Inheritance
```c
#include <glib-object.h>

// Base class: Animal
#define TYPE_ANIMAL (animal_get_type())
G_DECLARE_DERIVABLE_TYPE(Animal, animal, , ANIMAL, GObject)

struct _AnimalClass {
    GObjectClass parent_class;
    
    // Virtual methods
    void (*make_sound)(Animal *self);
    void (*move)(Animal *self);
    
    // Padding for future expansion
    gpointer padding[8];
};

// Animal properties
enum {
    ANIMAL_PROP_0,
    ANIMAL_PROP_NAME,
    ANIMAL_PROP_AGE,
    ANIMAL_PROP_SPECIES,
    ANIMAL_N_PROPERTIES
};

static GParamSpec *animal_properties[ANIMAL_N_PROPERTIES] = { NULL, };

// Animal private structure
typedef struct {
    char *name;
    int age;
    char *species;
} AnimalPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(Animal, animal, G_TYPE_OBJECT)

// Animal implementation
static void animal_get_property(GObject *object, guint prop_id, 
                               GValue *value, GParamSpec *pspec) {
    Animal *self = ANIMAL(object);
    AnimalPrivate *priv = animal_get_instance_private(self);
    
    switch (prop_id) {
        case ANIMAL_PROP_NAME:
            g_value_set_string(value, priv->name);
            break;
        case ANIMAL_PROP_AGE:
            g_value_set_int(value, priv->age);
            break;
        case ANIMAL_PROP_SPECIES:
            g_value_set_string(value, priv->species);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void animal_set_property(GObject *object, guint prop_id,
                               const GValue *value, GParamSpec *pspec) {
    Animal *self = ANIMAL(object);
    AnimalPrivate *priv = animal_get_instance_private(self);
    
    switch (prop_id) {
        case ANIMAL_PROP_NAME:
            g_free(priv->name);
            priv->name = g_value_dup_string(value);
            break;
        case ANIMAL_PROP_AGE:
            priv->age = g_value_get_int(value);
            break;
        case ANIMAL_PROP_SPECIES:
            g_free(priv->species);
            priv->species = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void animal_finalize(GObject *object) {
    Animal *self = ANIMAL(object);
    AnimalPrivate *priv = animal_get_instance_private(self);
    
    g_free(priv->name);
    g_free(priv->species);
    
    G_OBJECT_CLASS(animal_parent_class)->finalize(object);
}

// Default virtual method implementations
static void animal_make_sound_default(Animal *self) {
    AnimalPrivate *priv = animal_get_instance_private(self);
    g_print("%s makes a generic animal sound\n", priv->name);
}

static void animal_move_default(Animal *self) {
    AnimalPrivate *priv = animal_get_instance_private(self);
    g_print("%s moves around\n", priv->name);
}

static void animal_class_init(AnimalClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = animal_get_property;
    object_class->set_property = animal_set_property;
    object_class->finalize = animal_finalize;
    
    // Set up virtual methods
    klass->make_sound = animal_make_sound_default;
    klass->move = animal_move_default;
    
    // Install properties
    animal_properties[ANIMAL_PROP_NAME] = 
        g_param_spec_string("name", "Name", "The animal's name",
                           NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    
    animal_properties[ANIMAL_PROP_AGE] = 
        g_param_spec_int("age", "Age", "The animal's age",
                        0, 100, 0, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    
    animal_properties[ANIMAL_PROP_SPECIES] = 
        g_param_spec_string("species", "Species", "The animal's species",
                           NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    
    g_object_class_install_properties(object_class, ANIMAL_N_PROPERTIES, animal_properties);
}

static void animal_init(Animal *self) {
    // Instance initialization
}

// Public API
Animal* animal_new(const char *name, int age, const char *species) {
    return g_object_new(TYPE_ANIMAL,
                       "name", name,
                       "age", age,
                       "species", species,
                       NULL);
}

void animal_make_sound(Animal *self) {
    g_return_if_fail(IS_ANIMAL(self));
    
    AnimalClass *klass = ANIMAL_GET_CLASS(self);
    if (klass->make_sound) {
        klass->make_sound(self);
    }
}

void animal_move(Animal *self) {
    g_return_if_fail(IS_ANIMAL(self));
    
    AnimalClass *klass = ANIMAL_GET_CLASS(self);
    if (klass->move) {
        klass->move(self);
    }
}

// Derived class: Dog
#define TYPE_DOG (dog_get_type())
G_DECLARE_FINAL_TYPE(Dog, dog, , DOG, Animal)

struct _Dog {
    Animal parent_instance;
};

G_DEFINE_TYPE(Dog, dog, TYPE_ANIMAL)

// Dog-specific virtual method overrides
static void dog_make_sound(Animal *self) {
    char *name;
    g_object_get(self, "name", &name, NULL);
    g_print("%s barks: Woof! Woof!\n", name);
    g_free(name);
}

static void dog_move(Animal *self) {
    char *name;
    g_object_get(self, "name", &name, NULL);
    g_print("%s runs around wagging its tail\n", name);
    g_free(name);
}

static void dog_class_init(DogClass *klass) {
    AnimalClass *animal_class = ANIMAL_CLASS(klass);
    
    // Override virtual methods
    animal_class->make_sound = dog_make_sound;
    animal_class->move = dog_move;
}

static void dog_init(Dog *self) {
    // Dog-specific initialization
}

// Public API
Dog* dog_new(const char *name, int age) {
    return g_object_new(TYPE_DOG,
                       "name", name,
                       "age", age,
                       "species", "Canis lupus",
                       NULL);
}

void demonstrate_gobject_inheritance() {
    // Create animals
    Animal *generic_animal = animal_new("Generic", 5, "Unknown");
    Dog *dog = dog_new("Buddy", 3);
    Animal *dog_as_animal = ANIMAL(dog);  // Upcast
    
    g_print("=== Polymorphism Demo ===\n");
    
    // Polymorphic calls
    animal_make_sound(generic_animal);  // Uses default implementation
    animal_make_sound(dog_as_animal);   // Uses Dog's override
    
    animal_move(generic_animal);        // Uses default implementation
    animal_move(dog_as_animal);         // Uses Dog's override
    
    g_print("\n=== Property System Demo ===\n");
    
    // Property access
    char *name, *species;
    int age;
    
    g_object_get(dog_as_animal,
                 "name", &name,
                 "age", &age,
                 "species", &species,
                 NULL);
    
    g_print("Dog properties - Name: %s, Age: %d, Species: %s\n", 
            name, age, species);
    
    g_free(name);
    g_free(species);
    
    // Change properties
    g_object_set(dog_as_animal, "age", 4, NULL);
    g_object_get(dog_as_animal, "age", &age, NULL);
    g_print("Updated age: %d\n", age);
    
    g_print("\n=== Type System Demo ===\n");
    
    // Type checking
    g_print("generic_animal is Animal: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(generic_animal, TYPE_ANIMAL) ? "YES" : "NO");
    g_print("dog is Animal: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(dog, TYPE_ANIMAL) ? "YES" : "NO");
    g_print("dog is Dog: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(dog, TYPE_DOG) ? "YES" : "NO");
    g_print("generic_animal is Dog: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(generic_animal, TYPE_DOG) ? "YES" : "NO");
    
    // Cleanup
    g_object_unref(generic_animal);
    g_object_unref(dog);
}
```

### 5. Signals and Properties - Advanced Examples

#### Complete Event-Driven Application
```c
#include <glib-object.h>

// Custom object with signals and properties
#define TYPE_TEMPERATURE_SENSOR (temperature_sensor_get_type())
G_DECLARE_FINAL_TYPE(TemperatureSensor, temperature_sensor, , TEMPERATURE_SENSOR, GObject)

struct _TemperatureSensor {
    GObject parent_instance;
};

// Properties
enum {
    TEMP_PROP_0,
    TEMP_PROP_TEMPERATURE,
    TEMP_PROP_UNIT,
    TEMP_PROP_THRESHOLD,
    TEMP_N_PROPERTIES
};

// Signals
enum {
    TEMP_SIGNAL_TEMPERATURE_CHANGED,
    TEMP_SIGNAL_THRESHOLD_EXCEEDED,
    TEMP_SIGNAL_SENSOR_ERROR,
    TEMP_N_SIGNALS
};

static GParamSpec *temp_properties[TEMP_N_PROPERTIES] = { NULL, };
static guint temp_signals[TEMP_N_SIGNALS] = { 0 };

// Private structure
typedef struct {
    double temperature;
    char *unit;
    double threshold;
    gboolean is_monitoring;
    guint monitor_source_id;
} TemperatureSensorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(TemperatureSensor, temperature_sensor, G_TYPE_OBJECT)

// Property implementation
static void temperature_sensor_get_property(GObject *object, guint prop_id,
                                           GValue *value, GParamSpec *pspec) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(object);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    switch (prop_id) {
        case TEMP_PROP_TEMPERATURE:
            g_value_set_double(value, priv->temperature);
            break;
        case TEMP_PROP_UNIT:
            g_value_set_string(value, priv->unit);
            break;
        case TEMP_PROP_THRESHOLD:
            g_value_set_double(value, priv->threshold);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void temperature_sensor_set_property(GObject *object, guint prop_id,
                                           const GValue *value, GParamSpec *pspec) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(object);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    switch (prop_id) {
        case TEMP_PROP_TEMPERATURE: {
            double old_temp = priv->temperature;
            priv->temperature = g_value_get_double(value);
            
            // Emit temperature changed signal
            g_signal_emit(self, temp_signals[TEMP_SIGNAL_TEMPERATURE_CHANGED], 0,
                         old_temp, priv->temperature);
            
            // Check threshold
            if (priv->temperature > priv->threshold) {
                g_signal_emit(self, temp_signals[TEMP_SIGNAL_THRESHOLD_EXCEEDED], 0,
                             priv->temperature, priv->threshold);
            }
            break;
        }
        case TEMP_PROP_UNIT:
            g_free(priv->unit);
            priv->unit = g_value_dup_string(value);
            break;
        case TEMP_PROP_THRESHOLD:
            priv->threshold = g_value_get_double(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void temperature_sensor_finalize(GObject *object) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(object);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    if (priv->monitor_source_id > 0) {
        g_source_remove(priv->monitor_source_id);
    }
    
    g_free(priv->unit);
    
    G_OBJECT_CLASS(temperature_sensor_parent_class)->finalize(object);
}

static void temperature_sensor_class_init(TemperatureSensorClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = temperature_sensor_get_property;
    object_class->set_property = temperature_sensor_set_property;
    object_class->finalize = temperature_sensor_finalize;
    
    // Install properties
    temp_properties[TEMP_PROP_TEMPERATURE] = 
        g_param_spec_double("temperature", "Temperature", "Current temperature reading",
                           -273.15, 1000.0, 20.0, 
                           G_PARAM_READWRITE | G_PARAM_NOTIFY);
    
    temp_properties[TEMP_PROP_UNIT] = 
        g_param_spec_string("unit", "Unit", "Temperature unit (C/F/K)",
                           "C", G_PARAM_READWRITE);
    
    temp_properties[TEMP_PROP_THRESHOLD] = 
        g_param_spec_double("threshold", "Threshold", "Temperature threshold for alerts",
                           -273.15, 1000.0, 30.0, 
                           G_PARAM_READWRITE);
    
    g_object_class_install_properties(object_class, TEMP_N_PROPERTIES, temp_properties);
    
    // Install signals
    temp_signals[TEMP_SIGNAL_TEMPERATURE_CHANGED] = 
        g_signal_newv("temperature-changed",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     NULL, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 2,
                     (GType[]){G_TYPE_DOUBLE, G_TYPE_DOUBLE});
    
    temp_signals[TEMP_SIGNAL_THRESHOLD_EXCEEDED] = 
        g_signal_newv("threshold-exceeded",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     NULL, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 2,
                     (GType[]){G_TYPE_DOUBLE, G_TYPE_DOUBLE});
    
    temp_signals[TEMP_SIGNAL_SENSOR_ERROR] = 
        g_signal_newv("sensor-error",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     NULL, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 1,
                     (GType[]){G_TYPE_STRING});
}

static void temperature_sensor_init(TemperatureSensor *self) {
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    priv->temperature = 20.0;
    priv->unit = g_strdup("C");
    priv->threshold = 30.0;
    priv->is_monitoring = FALSE;
    priv->monitor_source_id = 0;
}

// Public API
TemperatureSensor* temperature_sensor_new(void) {
    return g_object_new(TYPE_TEMPERATURE_SENSOR, NULL);
}

void temperature_sensor_set_temperature(TemperatureSensor *self, double temperature) {
    g_return_if_fail(IS_TEMPERATURE_SENSOR(self));
    g_object_set(self, "temperature", temperature, NULL);
}

double temperature_sensor_get_temperature(TemperatureSensor *self) {
    g_return_val_if_fail(IS_TEMPERATURE_SENSOR(self), 0.0);
    
    double temperature;
    g_object_get(self, "temperature", &temperature, NULL);
    return temperature;
}

// Simulated monitoring with random temperature changes
static gboolean monitor_temperature(gpointer user_data) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(user_data);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    // Simulate temperature reading with some variation
    double variation = g_random_double_range(-2.0, 2.0);
    double new_temp = priv->temperature + variation;
    
    // Clamp to reasonable range
    new_temp = CLAMP(new_temp, -10.0, 50.0);
    
    // Occasionally simulate sensor error
    if (g_random_double() < 0.05) {  // 5% chance
        g_signal_emit(self, temp_signals[TEMP_SIGNAL_SENSOR_ERROR], 0,
                     "Sensor communication timeout");
        return G_SOURCE_CONTINUE;
    }
    
    // Update temperature (will trigger signals)
    g_object_set(self, "temperature", new_temp, NULL);
    
    return G_SOURCE_CONTINUE;
}

void temperature_sensor_start_monitoring(TemperatureSensor *self) {
    g_return_if_fail(IS_TEMPERATURE_SENSOR(self));
    
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    if (!priv->is_monitoring) {
        priv->is_monitoring = TRUE;
        priv->monitor_source_id = g_timeout_add(1000, monitor_temperature, self);
        g_print("Temperature monitoring started\n");
    }
}

void temperature_sensor_stop_monitoring(TemperatureSensor *self) {
    g_return_if_fail(IS_TEMPERATURE_SENSOR(self));
    
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    if (priv->is_monitoring) {
        priv->is_monitoring = FALSE;
        if (priv->monitor_source_id > 0) {
            g_source_remove(priv->monitor_source_id);
            priv->monitor_source_id = 0;
        }
        g_print("Temperature monitoring stopped\n");
    }
}

// Signal handlers
static void on_temperature_changed(TemperatureSensor *sensor, 
                                  double old_temp, double new_temp, 
                                  gpointer user_data) {
    char *unit;
    g_object_get(sensor, "unit", &unit, NULL);
    
    g_print("📊 Temperature changed: %.1f°%s → %.1f°%s (Δ%.1f°%s)\n",
            old_temp, unit, new_temp, unit, new_temp - old_temp, unit);
    
    g_free(unit);
}

static void on_threshold_exceeded(TemperatureSensor *sensor,
                                 double temperature, double threshold,
                                 gpointer user_data) {
    char *unit;
    g_object_get(sensor, "unit", &unit, NULL);
    
    g_print("🔥 ALERT: Temperature %.1f°%s exceeds threshold %.1f°%s!\n",
            temperature, unit, threshold, unit);
    
    g_free(unit);
}

static void on_sensor_error(TemperatureSensor *sensor, 
                           const char *error_message,
                           gpointer user_data) {
    g_print("❌ Sensor Error: %s\n", error_message);
}

// Property change notification
static void on_property_notify(GObject *object, GParamSpec *pspec, gpointer user_data) {
    const char *property_name = g_param_spec_get_name(pspec);
    g_print("🔔 Property '%s' changed\n", property_name);
}

void demonstrate_signals_and_properties() {
    // Create temperature sensor
    TemperatureSensor *sensor = temperature_sensor_new();
    
    // Connect signals
    g_signal_connect(sensor, "temperature-changed", 
                    G_CALLBACK(on_temperature_changed), NULL);
    g_signal_connect(sensor, "threshold-exceeded", 
                    G_CALLBACK(on_threshold_exceeded), NULL);
    g_signal_connect(sensor, "sensor-error", 
                    G_CALLBACK(on_sensor_error), NULL);
    
    // Connect to property notifications
    g_signal_connect(sensor, "notify", 
                    G_CALLBACK(on_property_notify), NULL);
    
    g_print("=== Temperature Sensor Demo ===\n");
    
    // Set initial values
    g_object_set(sensor,
                 "temperature", 25.0,
                 "threshold", 28.0,
                 "unit", "C",
                 NULL);
    
    // Manual temperature changes
    g_print("\n--- Manual Temperature Changes ---\n");
    temperature_sensor_set_temperature(sensor, 26.5);
    temperature_sensor_set_temperature(sensor, 29.2);  // Should exceed threshold
    temperature_sensor_set_temperature(sensor, 27.8);
    
    // Change threshold
    g_print("\n--- Threshold Change ---\n");
    g_object_set(sensor, "threshold", 27.0, NULL);
    
    // Start monitoring
    g_print("\n--- Automatic Monitoring (5 seconds) ---\n");
    temperature_sensor_start_monitoring(sensor);
    
    // Run main loop for 5 seconds
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_timeout_add(5000, (GSourceFunc)g_main_loop_quit, loop);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
    
    // Stop monitoring
    temperature_sensor_stop_monitoring(sensor);
    
    // Cleanup
    g_object_unref(sensor);
}
```

These comprehensive code examples demonstrate advanced usage patterns for each GLib feature:

1. **GList**: Custom data structures, sorting, searching, and performance optimization
2. **GHashTable**: Multi-type storage, custom hash functions, and configuration management
3. **GAsyncQueue**: Producer-consumer patterns, load balancing, and priority queues
4. **GObject**: Complete inheritance hierarchy with virtual methods and polymorphism
5. **Signals & Properties**: Event-driven sensor simulation with reactive programming

Each example shows real-world applications that go beyond basic demonstrations, including proper memory management, error handling, and performance considerations.

## Architecture

The project is structured as a shared library (`libglib_features.so`) linked to a main executable (`app_test`):

```
├── src/
│   ├── test_double_linked_lists.{c,h}  # GList demonstrations
│   ├── test_hash_tables.{c,h}          # GHashTable demonstrations  
│   ├── test_async_queue.{c,h}          # GAsyncQueue demonstrations
│   ├── test_gobject_basics.{c,h}       # GObject OOP demonstrations
│   ├── test_signals_properties.{c,h}   # GObject signals/properties demonstrations
│   └── test_menu.c                     # Main interactive program
├── meson.build                         # Build configuration
├── Dockerfile                          # Container configuration
├── docker-build.sh                     # Container build script
└── README.md                           # This file
```

## Prerequisites

- **GLib 2.50+**: Core library for data structures and utilities
- **Meson**: Modern build system (optional)
- **GCC/Clang**: C compiler with C11 support
- **Linux/Unix**: Threading support (POSIX threads)
- **Docker**: For containerized deployment (optional)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libglib2.0-dev libgobject-2.0-dev meson build-essential
```

**Fedora/RHEL:**
```bash
sudo dnf install glib2-devel gobject-introspection-devel meson gcc
```

**Arch Linux:**
```bash
sudo pacman -S glib2 gobject-introspection meson gcc
```

**Docker:**
```bash
# Install Docker (Ubuntu/Debian)
sudo apt install docker.io
sudo systemctl start docker
sudo usermod -aG docker $USER
```

## Build and Run

### Method 1: Using Meson (Recommended)
```bash
git clone https://github.com/your-username/C-GLib-knowledge-base.git
cd C-GLib-knowledge-base

# Setup build directory
meson setup builddir

# Compile the project
meson compile -C builddir

# Run the interactive demo
./builddir/app_test
```

### Method 2: Using Docker (Containerized)
```bash
# Build the Docker image
./docker-build.sh

# Run the containerized demo
docker run -it glib-knowledge-base:latest

# Run specific demo (example: option 1)
echo '1' | docker run -i glib-knowledge-base:latest
```

### Method 3: Manual Build
```bash
# Build shared library
gcc -shared -fPIC -o libglib_features.so \
    src/test_double_linked_lists.c \
    src/test_hash_tables.c \
    src/test_async_queue.c \
    src/test_gobject_basics.c \
    src/test_signals_properties.c \
    `pkg-config --cflags --libs glib-2.0 gobject-2.0`

# Build main executable
gcc -o app_test src/test_menu.c \
    -L. -lglib_features \
    `pkg-config --cflags --libs glib-2.0 gobject-2.0`

# Run with library path
LD_LIBRARY_PATH=. ./app_test
```

## Using the Application

The program provides an interactive menu with the following options:

1. **Double Linked Lists Demo**: Explore GList operations with person data
2. **Hash Tables Demo**: Learn GHashTable with student database
3. **Async Queues Demo**: Experience multi-threading with task queues
4. **GObject Basics Demo**: Discover object-oriented programming in C
5. **Signals and Properties Demo**: Learn event-driven programming patterns
6. **Run All Demos**: Execute all demonstrations sequentially
7. **Show GLib Information**: Display GLib version and features
8. **Exit Program**: Clean exit

Each demonstration includes:
- **Automated Examples**: Pre-populated data showing core functionality
- **Interactive Sections**: User input to explore features hands-on
- **Educational Output**: Detailed explanations of operations
- **Memory Management**: Proper cleanup demonstrations

## Educational Assessment & Laboratory Exercises

### Suggested Laboratory Assignments

**Beginner Level (Data Structures)**:
1. Modify the linked list demo to implement a stack (LIFO) using GList
2. Create a queue (FIFO) implementation and compare performance with linked lists
3. Implement a binary search on a sorted linked list and measure performance

**Intermediate Level (Algorithms)**:
1. Implement different sorting algorithms (bubble, insertion, merge) and compare with GList's built-in sort
2. Create a hash table with different collision resolution strategies (chaining vs open addressing)
3. Analyze hash function quality by measuring collision rates with different data sets

**Advanced Level (Concurrent Programming)**:
1. Implement a thread pool using GAsyncQueue for task distribution
2. Create a bounded buffer problem solution with multiple producers and consumers
3. Implement a reader-writer lock using GLib's synchronization primitives

**Advanced Level (Object-Oriented Programming in C)**:
1. Design and implement a complete class hierarchy using GObject (Vehicle -> Car -> SportsCar)
2. Create a plugin system using GObject interfaces and dynamic loading
3. Implement the Model-View-Controller pattern using GObject signals and properties
4. Build a simple state machine using GObject and signals for state transitions

**Expert Level (Event-Driven Architecture)**:
1. Design a messaging system with multiple event types and priority handling
2. Implement an undo/redo system using the Command pattern with GObject
3. Create a reactive programming framework using GObject signals and property bindings
4. Build a distributed event system with serialization and network communication

### Assessment Questions

**Data Structures Understanding**:
- What are the trade-offs between linked lists and arrays for different operations?
- How does the choice of hash function affect hash table performance?
- When would you choose a linked list over a hash table for data storage?

**Algorithm Analysis**:
- Calculate the time complexity of searching for an element in an unsorted linked list
- Explain why hash tables provide O(1) average lookup time but O(n) worst-case time
- Analyze the space complexity of the different data structures demonstrated

**Concurrent Programming**:
- Explain how the producer-consumer pattern prevents race conditions
- What are the benefits and drawbacks of blocking vs non-blocking queue operations?
- How does GAsyncQueue ensure thread safety without explicit locking?

**Object-Oriented Programming**:
- How does GObject implement inheritance in C without native language support?
- What are the advantages and disadvantages of reference counting vs garbage collection?
- Explain the role of virtual function tables (vtables) in polymorphism implementation
- How does the GObject type system enable runtime type checking and introspection?

**Event-Driven Programming**:
- Compare and contrast the Observer pattern with traditional callback mechanisms
- How do signals provide loose coupling between objects in complex applications?
- What are the performance implications of signal emission vs direct method calls?
- Explain how property change notifications can be used to implement reactive UIs

## Testing and Validation

The demonstration includes comprehensive testing scenarios:

- **Memory Leak Detection**: All allocations are properly freed
- **Thread Safety**: Multiple producers and consumers
- **Error Handling**: Graceful handling of edge cases
- **Performance**: Demonstrates O(1) hash operations vs O(n) list operations

## Using This Project in Computer Science Coursework

### For Instructors

This project can be integrated into various computer science courses:

**CS1/CS2 (Introductory Programming)**:
- Demonstrate dynamic memory management and pointer concepts
- Show real-world applications of data structures
- Provide hands-on experience with professional C libraries

**Data Structures Course**:
- Compare theoretical concepts with practical implementations
- Analyze time and space complexity of operations
- Explore different data structure design trade-offs

**Algorithms Course**:
- Study sorting and searching algorithm implementations
- Analyze algorithmic complexity in practice
- Compare different algorithmic approaches

**Operating Systems Course**:
- Understand concurrent programming challenges
- Explore synchronization primitives and patterns
- Study producer-consumer problem implementations

**Software Engineering Course**:
- Examine API design and documentation practices
- Study memory management and resource cleanup
- Explore containerization and build systems

### For Students

**Study Approach**:
1. **Read the Code**: Start by understanding the data structure implementations
2. **Run Experiments**: Modify parameters and observe behavior changes  
3. **Measure Performance**: Add timing code to measure operation complexity
4. **Extend Functionality**: Implement additional features or algorithms
5. **Compare Implementations**: Write alternative implementations and compare

**Assignment Ideas**:
- Implement additional list operations (merge, split, rotate)
- Create custom hash functions and analyze their distribution properties
- Design producer-consumer scenarios with different workload patterns
- Write unit tests for all the implemented functions

## Contributing

Contributions are welcome. Areas for enhancement:

- Additional GLib data structures (GPtrArray, GTree, etc.)
- More complex threading examples
- Performance benchmarking
- Unit tests with GLib's testing framework
- Windows compatibility improvements

## Resources

- [IBM: Manage C data using the GLib collections](https://developer.ibm.com/tutorials/l-glib/)
- [Getting Started with GLib](https://remcokranenburg.com/2021/05/30/getting-started-with-glib.html)
- [Asynchronous operations in C with GObject](https://www.youtube.com/watch?v=rJS2TrkFIAs)
- [GLib Documentation](https://docs.gtk.org/glib/)
- [GLib Tutorial](https://developer.gnome.org/glib/stable/)
- [Meson Build System](https://mesonbuild.com/)
- [C Programming Best Practices](https://github.com/mcinglis/c-style)
