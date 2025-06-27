## Features Demonstrated

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

## Comprehensive Code Examples and Usage

This section provides direct, practical code examples that demonstrate real-world usage patterns for each GLib feature, going beyond the basic demonstrations in the interactive program.

### GAsyncQueue (Thread-Safe Queues) - Advanced Examples

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
