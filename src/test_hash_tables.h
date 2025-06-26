#ifndef TEST_HASH_TABLES_H
#define TEST_HASH_TABLES_H

#include <glib.h>

/**
 * Structure to represent student information
 */
typedef struct {
    char *name;
    int student_id;
    double gpa;
    char *major;
} Student;

/**
 * Initialize and run hash tables demonstration
 */
void test_hash_tables(void);

/**
 * Create a new student
 */
Student* student_new(const char *name, int student_id, double gpa, const char *major);

/**
 * Free student memory
 */
void student_free(Student *student);

/**
 * Print student information
 */
void student_print(Student *student);

/**
 * Hash table operations
 */
void hash_table_add_student(GHashTable *table, const char *key, Student *student);
void hash_table_print_all(GHashTable *table);

#endif /* TEST_HASH_TABLES_H */