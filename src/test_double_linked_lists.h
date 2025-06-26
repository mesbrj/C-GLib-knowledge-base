#ifndef TEST_DOUBLE_LINKED_LISTS_H
#define TEST_DOUBLE_LINKED_LISTS_H

#include <glib.h>

/**
 * Structure to represent a person for double linked lists demo
 */
typedef struct {
    char *name;
    int age;
    char *city;
} ListPerson;

/**
 * Initialize and run double linked lists demonstration
 */
void test_double_linked_lists(void);

/**
 * Create a new person
 */
ListPerson* list_person_new(const char *name, int age, const char *city);

/**
 * Free person memory
 */
void list_person_free(ListPerson *person);

/**
 * Print person information
 */
void list_person_print(ListPerson *person);

/**
 * Print all persons in the list
 */
void list_print_all(GList *list);

#endif /* TEST_DOUBLE_LINKED_LISTS_H */