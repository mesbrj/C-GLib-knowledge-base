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

## Comprehensive Code Examples and Usage

This section provides direct, practical code examples that demonstrate real-world usage patterns for each GLib feature, going beyond the basic demonstrations in the interactive program.

### GList (Doubly Linked Lists) - Advanced Examples

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