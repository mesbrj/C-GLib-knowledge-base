#ifndef ASYNC_QUEUE_H
#define ASYNC_QUEUE_H

#include <glib.h>

/**
 * Structure to represent a task for async queue demo
 */
typedef struct {
    int task_id;
    char *description;
    int priority;
    gboolean completed;
} QueueTask;

/**
 * Initialize and run async queue demonstration
 */
void test_async_queue(void);

/**
 * Create a new task
 */
QueueTask* queue_task_new(int task_id, const char *description, int priority);

/**
 * Free task memory
 */
void queue_task_free(QueueTask *task);

/**
 * Print task information
 */
void queue_task_print(QueueTask *task);

/**
 * Producer function - adds tasks to queue
 */
gpointer producer_function(gpointer data);

/**
 * Consumer function - processes tasks from queue
 */
gpointer consumer_function(gpointer data);

/**
 * Thread data structure
 */
typedef struct {
    GAsyncQueue *queue;
    int num_tasks;
    gboolean stop_flag;
} ThreadData;

#endif /* ASYNC_QUEUE_H */