#include "test_async_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for sleep

Task* task_new(int task_id, const char *description, int priority) {
    Task *task = g_malloc(sizeof(Task));
    task->task_id = task_id;
    task->description = g_strdup(description);
    task->priority = priority;
    task->completed = FALSE;
    return task;
}

void task_free(Task *task) {
    if (task) {
        g_free(task->description);
        g_free(task);
    }
}

void task_print(Task *task) {
    if (task) {
        printf("  Task #%d: %s (Priority: %d, Status: %s)\n", 
               task->task_id, task->description, task->priority,
               task->completed ? "Completed" : "Pending");
    }
}

gpointer producer_function(gpointer data) {
    ThreadData *thread_data = (ThreadData*)data;
    GAsyncQueue *queue = thread_data->queue;
    int num_tasks = thread_data->num_tasks;
    
    printf("[Producer] Starting to produce %d tasks...\n", num_tasks);
    
    // Sample task descriptions
    const char *task_descriptions[] = {
        "Process user registration",
        "Send welcome email",
        "Update database records",
        "Generate monthly report",
        "Backup system files",
        "Validate user input",
        "Calculate statistics",
        "Clean temporary files",
        "Synchronize data",
        "Optimize database queries"
    };
    
    int num_descriptions = sizeof(task_descriptions) / sizeof(task_descriptions[0]);
    
    for (int i = 0; i < num_tasks; i++) {
        // Create a task with varying priority
        int priority = (i % 3) + 1;  // Priority 1-3
        const char *desc = task_descriptions[i % num_descriptions];
        
        Task *task = task_new(i + 1, desc, priority);
        
        printf("[Producer] Creating task: ");
        task_print(task);
        
        // Add task to queue
        g_async_queue_push(queue, task);
        
        // Simulate work time
        g_usleep(500000);  // 0.5 seconds
    }
    
    // Send termination signal (use a special task instead of NULL)
    Task *termination_task = task_new(-1, "TERMINATE", 0);
    g_async_queue_push(queue, termination_task);
    printf("[Producer] Finished producing tasks.\n");
    
    return NULL;
}

gpointer consumer_function(gpointer data) {
    ThreadData *thread_data = (ThreadData*)data;
    GAsyncQueue *queue = thread_data->queue;
    int processed_count = 0;
    
    printf("[Consumer] Starting to consume tasks...\n");
    
    while (TRUE) {
        // Pop task from queue (blocks if queue is empty)
        Task *task = (Task*)g_async_queue_pop(queue);
        
        // Check for termination signal
        if (task->task_id == -1) {
            printf("[Consumer] Received termination signal.\n");
            task_free(task);
            break;
        }
        
        printf("[Consumer] Processing task: ");
        task_print(task);
        
        // Simulate processing time (higher priority = faster processing)
        int processing_time = (4 - task->priority) * 1000000;  // 1-3 seconds
        g_usleep(processing_time);
        
        // Mark task as completed
        task->completed = TRUE;
        printf("[Consumer] Completed task: ");
        task_print(task);
        
        processed_count++;
        
        // Clean up task
        task_free(task);
    }
    
    printf("[Consumer] Finished processing %d tasks.\n", processed_count);
    return NULL;
}

// Timeout consumer that demonstrates timed operations
gpointer timeout_consumer_function(gpointer data) {
    ThreadData *thread_data = (ThreadData*)data;
    GAsyncQueue *queue = thread_data->queue;
    int timeout_count = 0;
    int processed_count = 0;
    
    printf("[Timeout Consumer] Starting with 2-second timeout...\n");
    
    while (!thread_data->stop_flag) {
        // Try to pop with timeout (2 seconds)
        Task *task = (Task*)g_async_queue_timeout_pop(queue, 2000000);  // 2 seconds in microseconds
        
        if (task == NULL) {
            timeout_count++;
            printf("[Timeout Consumer] Timeout #%d - no tasks available\n", timeout_count);
            
            if (timeout_count >= 3) {
                printf("[Timeout Consumer] Too many timeouts, stopping.\n");
                break;
            }
            continue;
        }
        
        // Reset timeout counter on successful pop
        timeout_count = 0;
        
        // Check for termination
        if (task->task_id == -1) {
            task_free(task);
            break;
        }
        
        printf("[Timeout Consumer] Processing task: ");
        task_print(task);
        
        // Quick processing
        g_usleep(500000);  // 0.5 seconds
        task->completed = TRUE;
        processed_count++;
        
        task_free(task);
    }
    
    printf("[Timeout Consumer] Processed %d tasks before timeout.\n", processed_count);
    return NULL;
}

void test_async_queue(void) {
    printf("\n=== GLib Async Queue Demo ===\n");
    
    // Create async queue
    GAsyncQueue *queue = g_async_queue_new();
    
    printf("\n1. Basic async queue operations:\n");
    
    // Create some tasks manually
    Task *task1 = task_new(101, "Initialize system", 1);
    Task *task2 = task_new(102, "Load configuration", 2);
    Task *task3 = task_new(103, "Start services", 3);
    
    printf("Adding tasks to queue...\n");
    g_async_queue_push(queue, task1);
    g_async_queue_push(queue, task2);
    g_async_queue_push(queue, task3);
    
    printf("Queue length: %d\n", g_async_queue_length(queue));
    
    // Try to pop without blocking
    Task *popped_task = (Task*)g_async_queue_try_pop(queue);
    if (popped_task) {
        printf("Popped task: ");
        task_print(popped_task);
        task_free(popped_task);
    }
    
    printf("Queue length after pop: %d\n", g_async_queue_length(queue));
    
    // Clear remaining tasks
    while (g_async_queue_length(queue) > 0) {
        Task *task = (Task*)g_async_queue_try_pop(queue);
        if (task) {
            task_free(task);
        }
    }
    
    printf("\n2. Producer-Consumer pattern with threads:\n");
    
    // Setup thread data
    ThreadData thread_data = {
        .queue = queue,
        .num_tasks = 5,
        .stop_flag = FALSE
    };
    
    // Create producer and consumer threads
    GThread *producer_thread = g_thread_new("producer", producer_function, &thread_data);
    GThread *consumer_thread = g_thread_new("consumer", consumer_function, &thread_data);
    
    // Wait for threads to complete
    g_thread_join(producer_thread);
    g_thread_join(consumer_thread);
    
    printf("\n3. Multiple consumers demo:\n");
    
    // Reset for multiple consumers
    thread_data.num_tasks = 8;
    thread_data.stop_flag = FALSE;
    
    // Create one producer and two consumers
    GThread *producer2 = g_thread_new("producer2", producer_function, &thread_data);
    GThread *consumer1 = g_thread_new("consumer1", consumer_function, &thread_data);
    GThread *consumer2 = g_thread_new("consumer2", consumer_function, &thread_data);
    
    // Wait for producer to finish
    g_thread_join(producer2);
    
    // Send termination signals for both consumers
    Task *term1 = task_new(-1, "TERMINATE", 0);
    Task *term2 = task_new(-1, "TERMINATE", 0);
    g_async_queue_push(queue, term1);
    g_async_queue_push(queue, term2);
    
    // Wait for consumers to finish
    g_thread_join(consumer1);
    g_thread_join(consumer2);
    
    printf("\n4. Timeout operations demo:\n");
    
    // Add a few tasks for timeout demo
    Task *timeout_task1 = task_new(201, "Timeout test task 1", 2);
    Task *timeout_task2 = task_new(202, "Timeout test task 2", 1);
    
    g_async_queue_push(queue, timeout_task1);
    g_async_queue_push(queue, timeout_task2);
    
    thread_data.stop_flag = FALSE;
    GThread *timeout_consumer = g_thread_new("timeout_consumer", 
                                            timeout_consumer_function, &thread_data);
    
    // Let it run for a while
    g_usleep(8000000);  // 8 seconds
    thread_data.stop_flag = TRUE;
    
    g_thread_join(timeout_consumer);
    
    printf("\n5. Interactive part - Add priority tasks:\n");
    printf("You can add up to 3 tasks. Press Enter with empty description to stop.\n");
    
    int task_counter = 1000;
    for (int i = 0; i < 3; i++) {
        char description[200];
        int priority;
        
        printf("Enter task description (or press Enter to stop): ");
        if (fgets(description, sizeof(description), stdin)) {
            description[strcspn(description, "\n")] = 0;
            
            if (strlen(description) == 0) {
                break;
            }
            
            printf("Enter priority (1-3, where 1 is highest): ");
            if (scanf("%d", &priority) == 1) {
                // Clear input buffer
                while (getchar() != '\n');
                
                if (priority < 1 || priority > 3) {
                    priority = 2;  // Default priority
                }
                
                Task *user_task = task_new(++task_counter, description, priority);
                g_async_queue_push(queue, user_task);
                
                printf("Added task: ");
                task_print(user_task);
                printf("Current queue length: %d\n", g_async_queue_length(queue));
            }
        }
    }
    
    // Process any remaining tasks
    if (g_async_queue_length(queue) > 0) {
        printf("\nProcessing remaining tasks...\n");
        while (g_async_queue_length(queue) > 0) {
            Task *task = (Task*)g_async_queue_try_pop(queue);
            if (task) {
                printf("Processing: ");
                task_print(task);
                g_usleep(1000000);  // 1 second
                task->completed = TRUE;
                printf("Completed: ");
                task_print(task);
                task_free(task);
            }
        }
    }
    
    // Cleanup
    printf("\n6. Cleaning up async queue...\n");
    g_async_queue_unref(queue);
    printf("Async queue cleaned up successfully!\n");
}