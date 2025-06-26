#ifndef TEST_HASH_TABLES_H
#define TEST_HASH_TABLES_H

#include <glib.h>

/**
 * Structure to represent student information for hash tables demo
 */
typedef struct {
    char *name;
    int student_id;
    double gpa;
    char *major;
} HashStudent;

/**
 * Initialize and run hash tables demonstration
 */
void test_hash_tables(void);

/**
 * Create a new student
 */
HashStudent* hash_student_new(const char *name, int student_id, double gpa, const char *major);

/**
 * Free student memory
 */
void hash_student_free(HashStudent *student);

/**
 * Print student information
 */
void hash_student_print(HashStudent *student);

/**
 * Hash table operations
 */
void hash_table_add_student(GHashTable *table, const char *key, HashStudent *student);
void hash_table_print_all(GHashTable *table);

#endif /* TEST_HASH_TABLES_H */