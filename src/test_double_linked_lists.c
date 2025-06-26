#include "test_double_linked_lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person* person_new(const char *name, int age, const char *city) {
    Person *person = g_malloc(sizeof(Person));
    person->name = g_strdup(name);
    person->age = age;
    person->city = g_strdup(city);
    return person;
}

void person_free(Person *person) {
    if (person) {
        g_free(person->name);
        g_free(person->city);
        g_free(person);
    }
}

void person_print(Person *person) {
    if (person) {
        printf("  Name: %s, Age: %d, City: %s\n", 
               person->name, person->age, person->city);
    }
}

void list_print_all(GList *list) {
    printf("\n--- Current List Contents ---\n");
    if (!list) {
        printf("  List is empty.\n");
        return;
    }
    
    int count = 1;
    for (GList *l = list; l != NULL; l = l->next) {
        printf("%d. ", count++);
        person_print((Person*)l->data);
    }
    printf("Total items: %d\n", g_list_length(list));
}

// Comparison function for sorting
gint compare_persons_by_age(gconstpointer a, gconstpointer b) {
    const Person *person_a = (const Person*)a;
    const Person *person_b = (const Person*)b;
    return person_a->age - person_b->age;
}

// Find function
gint find_person_by_name(gconstpointer a, gconstpointer b) {
    const Person *person = (const Person*)a;
    const char *name = (const char*)b;
    return g_strcmp0(person->name, name);
}

void test_double_linked_lists(void) {
    printf("\n=== GLib Double Linked Lists Demo ===\n");
    
    GList *list = NULL;
    
    // Create some sample persons
    Person *p1 = person_new("Alice Johnson", 28, "New York");
    Person *p2 = person_new("Bob Smith", 35, "Los Angeles");
    Person *p3 = person_new("Charlie Brown", 22, "Chicago");
    Person *p4 = person_new("Diana Prince", 31, "Miami");
    
    printf("\n1. Adding persons to the list...\n");
    
    // Add to list (append)
    list = g_list_append(list, p1);
    list = g_list_append(list, p2);
    list = g_list_prepend(list, p3);  // Add to beginning
    list = g_list_insert(list, p4, 2);  // Insert at position 2
    
    list_print_all(list);
    
    printf("\n2. List operations:\n");
    printf("First person: ");
    person_print((Person*)g_list_first(list)->data);
    printf("Last person: ");
    person_print((Person*)g_list_last(list)->data);
    printf("Person at index 1: ");
    person_print((Person*)g_list_nth_data(list, 1));
    
    printf("\n3. Searching for 'Bob Smith'...\n");
    GList *found = g_list_find_custom(list, "Bob Smith", find_person_by_name);
    if (found) {
        printf("Found: ");
        person_print((Person*)found->data);
        printf("Position in list: %d\n", g_list_position(list, found));
    }
    
    printf("\n4. Sorting list by age...\n");
    list = g_list_sort(list, compare_persons_by_age);
    list_print_all(list);
    
    printf("\n5. Reversing the list...\n");
    list = g_list_reverse(list);
    list_print_all(list);
    
    printf("\n6. Removing person at index 1...\n");
    GList *to_remove = g_list_nth(list, 1);
    if (to_remove) {
        Person *person_to_free = (Person*)to_remove->data;
        list = g_list_remove(list, person_to_free);
        person_free(person_to_free);
    }
    list_print_all(list);
    
    printf("\n7. Interactive part - Add your own person:\n");
    char name[100], city[100];
    int age;
    
    printf("Enter name: ");
    if (fgets(name, sizeof(name), stdin)) {
        // Remove newline
        name[strcspn(name, "\n")] = 0;
        
        printf("Enter age: ");
        if (scanf("%d", &age) == 1) {
            // Clear input buffer
            while (getchar() != '\n');
            
            printf("Enter city: ");
            if (fgets(city, sizeof(city), stdin)) {
                city[strcspn(city, "\n")] = 0;
                
                Person *new_person = person_new(name, age, city);
                list = g_list_append(list, new_person);
                
                printf("\nUpdated list:\n");
                list_print_all(list);
            }
        }
    }
    
    // Cleanup
    printf("\n8. Cleaning up memory...\n");
    g_list_free_full(list, (GDestroyNotify)person_free);
    printf("Memory cleaned up successfully!\n");
}