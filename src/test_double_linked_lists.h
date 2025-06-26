#ifndef TEST_DOUBLE_LINKED_LISTS_H
#define TEST_DOUBLE_LINKED_LISTS_H

#include <glib.h>

/**
 * Structure to represent a person
 */
typedef struct {
    char *name;
    int age;
    char *city;
} Person;

/**
 * Initialize and run double linked lists demonstration
 */
void test_double_linked_lists(void);

/**
 * Create a new person
 */
Person* person_new(const char *name, int age, const char *city);

/**
 * Free person memory
 */
void person_free(Person *person);

/**
 * Print person information
 */
void person_print(Person *person);

/**
 * Print all persons in the list
 */
void list_print_all(GList *list);

#endif /* TEST_DOUBLE_LINKED_LISTS_H */