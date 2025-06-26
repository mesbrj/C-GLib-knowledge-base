#include "test_hash_tables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

HashStudent* hash_student_new(const char *name, int student_id, double gpa, const char *major) {
    HashStudent *student = g_malloc(sizeof(HashStudent));
    student->name = g_strdup(name);
    student->student_id = student_id;
    student->gpa = gpa;
    student->major = g_strdup(major);
    return student;
}

void hash_student_free(HashStudent *student) {
    if (student) {
        g_free(student->name);
        g_free(student->major);
        g_free(student);
    }
}

void hash_student_print(HashStudent *student) {
    if (student) {
        printf("  ID: %d, Name: %s, GPA: %.2f, Major: %s\n", 
               student->student_id, student->name, student->gpa, student->major);
    }
}

void hash_table_add_student(GHashTable *table, const char *key, HashStudent *student) {
    g_hash_table_insert(table, g_strdup(key), student);
}

// Helper function to print hash table contents
void print_hash_entry(gpointer key, gpointer value, gpointer user_data) {
    const char *student_key = (const char*)key;
    HashStudent *student = (HashStudent*)value;
    int *count = (int*)user_data;
    
    printf("%d. Key: '%s' -> ", ++(*count), student_key);
    hash_student_print(student);
}

void hash_table_print_all(GHashTable *table) {
    printf("\n--- Hash Table Contents ---\n");
    if (g_hash_table_size(table) == 0) {
        printf("  Hash table is empty.\n");
        return;
    }
    
    int count = 0;
    g_hash_table_foreach(table, print_hash_entry, &count);
    printf("Total entries: %d\n", g_hash_table_size(table));
}

// Helper function to collect high GPA students
void collect_high_gpa_students(gpointer key, gpointer value, gpointer user_data) {
    HashStudent *student = (HashStudent*)value;
    GList **high_gpa_list = (GList**)user_data;
    
    if (student->gpa >= 3.5) {
        *high_gpa_list = g_list_append(*high_gpa_list, student);
    }
}

// Helper function to find students by major
void find_students_by_major(gpointer key, gpointer value, gpointer user_data) {
    HashStudent *student = (HashStudent*)value;
    const char *target_major = ((const char**)user_data)[0];
    GList **major_list = (GList**)((const char**)user_data)[1];
    
    if (g_strcmp0(student->major, target_major) == 0) {
        *major_list = g_list_append(*major_list, student);
    }
}

void test_hash_tables(void) {
    printf("\n=== GLib Hash Tables Demo ===\n");
    
    // Create hash table with string keys and custom value destructor
    GHashTable *student_table = g_hash_table_new_full(
        g_str_hash,           // hash function for string keys
        g_str_equal,          // key comparison function
        g_free,               // key destructor
        (GDestroyNotify)hash_student_free  // value destructor
    );
    
    printf("\n1. Creating student database...\n");
    
    // Add students to hash table
    HashStudent *s1 = hash_student_new("Emma Wilson", 1001, 3.8, "Computer Science");
    HashStudent *s2 = hash_student_new("Liam Johnson", 1002, 3.2, "Mathematics");
    HashStudent *s3 = hash_student_new("Sophia Davis", 1003, 3.9, "Physics");
    HashStudent *s4 = hash_student_new("Noah Brown", 1004, 2.8, "Computer Science");
    HashStudent *s5 = hash_student_new("Olivia Miller", 1005, 3.6, "Chemistry");
    
    hash_table_add_student(student_table, "emma.wilson", s1);
    hash_table_add_student(student_table, "liam.johnson", s2);
    hash_table_add_student(student_table, "sophia.davis", s3);
    hash_table_add_student(student_table, "noah.brown", s4);
    hash_table_add_student(student_table, "olivia.miller", s5);
    
    hash_table_print_all(student_table);
    
    printf("\n2. Hash table lookup operations:\n");
    
    // Lookup by key
    const char *lookup_key = "sophia.davis";
    HashStudent *found_student = g_hash_table_lookup(student_table, lookup_key);
    if (found_student) {
        printf("Found student with key '%s': ", lookup_key);
        hash_student_print(found_student);
    }
    
    // Check if key exists
    const char *check_key = "john.doe";
    if (g_hash_table_contains(student_table, check_key)) {
        printf("Key '%s' exists in table\n", check_key);
    } else {
        printf("Key '%s' does not exist in table\n", check_key);
    }
    
    printf("\n3. Advanced operations:\n");
    
    // Find all students with high GPA (>= 3.5)
    GList *high_gpa_students = NULL;
    g_hash_table_foreach(student_table, collect_high_gpa_students, &high_gpa_students);
    
    printf("Students with GPA >= 3.5:\n");
    for (GList *l = high_gpa_students; l != NULL; l = l->next) {
        printf("  ");
        hash_student_print((HashStudent*)l->data);
    }
    g_list_free(high_gpa_students);
    
    // Find students by major
    const char *target_major = "Computer Science";
    GList *cs_students = NULL;
    gpointer user_data[2] = { (gpointer)target_major, (gpointer)&cs_students };
    g_hash_table_foreach(student_table, find_students_by_major, user_data);
    
    printf("\nStudents majoring in %s:\n", target_major);
    for (GList *l = cs_students; l != NULL; l = l->next) {
        printf("  ");
        hash_student_print((HashStudent*)l->data);
    }
    g_list_free(cs_students);
    
    printf("\n4. Hash table statistics:\n");
    printf("Number of entries: %d\n", g_hash_table_size(student_table));
    
    // Get all keys
    GList *keys = g_hash_table_get_keys(student_table);
    printf("All keys: ");
    for (GList *l = keys; l != NULL; l = l->next) {
        printf("'%s'", (char*)l->data);
        if (l->next) printf(", ");
    }
    printf("\n");
    g_list_free(keys);
    
    printf("\n5. Interactive part - Add a new student:\n");
    
    // Check if stdin is available for interactive input
    if (isatty(STDIN_FILENO)) {
        char username[100], name[100], major[100];
        int student_id;
        double gpa;
        
        printf("Enter username (key): ");
        if (fgets(username, sizeof(username), stdin)) {
            username[strcspn(username, "\n")] = 0;
            
            printf("Enter student name: ");
            if (fgets(name, sizeof(name), stdin)) {
                name[strcspn(name, "\n")] = 0;
                
                printf("Enter student ID: ");
                if (scanf("%d", &student_id) == 1) {
                    printf("Enter GPA: ");
                    if (scanf("%lf", &gpa) == 1) {
                        // Clear input buffer
                        while (getchar() != '\n');
                        
                        printf("Enter major: ");
                        if (fgets(major, sizeof(major), stdin)) {
                            major[strcspn(major, "\n")] = 0;
                            
                            HashStudent *new_student = hash_student_new(name, student_id, gpa, major);
                            hash_table_add_student(student_table, username, new_student);
                            
                            printf("\nUpdated hash table:\n");
                            hash_table_print_all(student_table);
                        }
                    }
                }
            }
        }
    } else {
        printf("(Skipping interactive input - not running in terminal)\n");
        printf("Adding sample student instead...\n");
        HashStudent *new_student = hash_student_new("Demo Student", 9999, 3.5, "Demo Major");
        hash_table_add_student(student_table, "demo.student", new_student);
        
        printf("\nUpdated hash table:\n");
        hash_table_print_all(student_table);
    }
    
    printf("\n6. Removing a student:\n");
    const char *remove_key = "noah.brown";
    if (g_hash_table_remove(student_table, remove_key)) {
        printf("Successfully removed student with key '%s'\n", remove_key);
    } else {
        printf("Failed to remove student with key '%s'\n", remove_key);
    }
    
    hash_table_print_all(student_table);
    
    // Cleanup (automatic due to g_hash_table_new_full)
    printf("\n7. Cleaning up hash table...\n");
    g_hash_table_destroy(student_table);
    printf("Hash table cleaned up successfully!\n");
}