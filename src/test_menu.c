#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

// Include our test modules
#include "test_double_linked_lists.h"
#include "test_hash_tables.h"
#include "test_async_queue.h"

// Function prototypes
void show_main_menu(void);
void show_welcome_message(void);
void show_glib_info(void);
int get_user_choice(void);
void clear_input_buffer(void);
void pause_for_user(void);

int main(int argc, char *argv[]) {
    printf("GLib Knowledge Base Demo Program\n");
    printf("================================\n\n");
    
    show_welcome_message();
    show_glib_info();
    
    int choice;
    gboolean running = TRUE;
    
    while (running) {
        show_main_menu();
        choice = get_user_choice();
        
        // Clear screen (works on most terminals)
        system("clear || cls");
        
        switch (choice) {
            case 1:
                test_double_linked_lists();
                pause_for_user();
                break;
                
            case 2:
                test_hash_tables();
                pause_for_user();
                break;
                
            case 3:
                test_async_queue();
                pause_for_user();
                break;
                
            case 4:
                printf("\n=== All GLib Features Demo ===\n");
                printf("Running all demonstrations in sequence...\n\n");
                
                test_double_linked_lists();
                printf("\n==================================================\n");
                
                test_hash_tables();
                printf("\n==================================================\n");
                
                test_async_queue();
                
                printf("\n=== All Demos Completed ===\n");
                pause_for_user();
                break;
                
            case 5:
                show_glib_info();
                pause_for_user();
                break;
                
            case 6:
                printf("\nThank you for using the GLib Knowledge Base Demo!\n");
                printf("Visit https://docs.gtk.org/glib/ for more information about GLib.\n");
                running = FALSE;
                break;
                
            default:
                printf("\nInvalid choice! Please select a number between 1 and 6.\n");
                pause_for_user();
                break;
        }
    }
    
    return 0;
}

void show_welcome_message(void) {
    printf("Welcome to the comprehensive GLib demonstration program!\n");
    printf("This program showcases three powerful features of GLib:\n\n");
    
    printf("1. Double Linked Lists (GList)\n");
    printf("   - Dynamic data structures for storing ordered collections\n");
    printf("   - Easy insertion, deletion, and traversal operations\n");
    printf("   - Built-in sorting and searching capabilities\n\n");
    
    printf("2. Hash Tables (GHashTable)\n");
    printf("   - Fast key-value storage with O(1) average lookup time\n");
    printf("   - Automatic memory management with custom destructors\n");
    printf("   - Flexible iteration and filtering operations\n\n");
    
    printf("3. Async Queues (GAsyncQueue)\n");
    printf("   - Thread-safe queues for inter-thread communication\n");
    printf("   - Producer-consumer patterns with blocking/non-blocking operations\n");
    printf("   - Timeout support for robust concurrent programming\n\n");
    
    pause_for_user();
}

void show_glib_info(void) {
    printf("\n=== GLib Information ===\n");
    printf("GLib Version: %d.%d.%d\n", 
           glib_major_version, glib_minor_version, glib_micro_version);
    printf("Compiled against GLib: %d.%d.%d\n",
           GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);
    
    printf("\nAbout GLib:\n");
    printf("GLib is a low-level core library that forms the basis for projects\n");
    printf("such as GTK and GNOME. It provides data structure handling for C,\n");
    printf("portability wrappers, and interfaces for functionality such as\n");
    printf("event loops, threads, dynamic loading, and an object system.\n\n");
    
    printf("Key Features demonstrated in this program:\n");
    printf("• Memory management with automatic cleanup\n");
    printf("• Thread-safe data structures\n");
    printf("• Rich set of data manipulation functions\n");
    printf("• Cross-platform compatibility\n");
    printf("• Extensive documentation and community support\n");
}

void show_main_menu(void) {
    printf("\n==================================================\n");
    printf("           GLIB FEATURES DEMONSTRATION MENU\n");
    printf("==================================================\n");
    printf("1. Double Linked Lists Demo (GList)\n");
    printf("2. Hash Tables Demo (GHashTable)\n");
    printf("3. Async Queues Demo (GAsyncQueue)\n");
    printf("4. Run All Demos\n");
    printf("5. Show GLib Information\n");
    printf("6. Exit Program\n");
    printf("==================================================\n");
    printf("Please select an option (1-6): ");
}

int get_user_choice(void) {
    int choice;
    char input[10];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        if (sscanf(input, "%d", &choice) == 1) {
            return choice;
        }
    }
    
    return -1;  // Invalid input
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_for_user(void) {
    printf("\nPress Enter to continue...");
    getchar();
}