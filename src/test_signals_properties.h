#ifndef TEST_SIGNALS_PROPERTIES_H
#define TEST_SIGNALS_PROPERTIES_H

#include <glib-object.h>

G_BEGIN_DECLS

/* =============================================================================
 * Signal and Property System Educational Demonstration
 * 
 * This module demonstrates advanced GObject concepts:
 * - Signal system (Observer pattern)
 * - Property system with change notifications
 * - Custom interfaces
 * - Event-driven programming patterns
 * ============================================================================= */

/* =============================================================================
 * IComparable Interface - Demonstrates interface implementation
 * ============================================================================= */

#define TYPE_COMPARABLE (comparable_get_type())
#define COMPARABLE(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_COMPARABLE, Comparable))
#define IS_COMPARABLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_COMPARABLE))
#define COMPARABLE_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE((obj), TYPE_COMPARABLE, ComparableInterface))
G_DECLARE_INTERFACE(Comparable, comparable, , COMPARABLE, GObject)

/**
 * Interface definition for comparable objects
 */
struct _ComparableInterface {
    GTypeInterface parent_interface;
    
    /* Virtual methods */
    gint (*compare)(Comparable *self, Comparable *other);
    gboolean (*equals)(Comparable *self, Comparable *other);
};

/* Interface methods */
gint comparable_compare(Comparable *self, Comparable *other);
gboolean comparable_equals(Comparable *self, Comparable *other);

/* =============================================================================
 * BankAccount Class - Demonstrates signals and property notifications
 * ============================================================================= */

#define TYPE_BANK_ACCOUNT (bank_account_get_type())
#define BANK_ACCOUNT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_BANK_ACCOUNT, BankAccount))
#define IS_BANK_ACCOUNT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_BANK_ACCOUNT))
G_DECLARE_FINAL_TYPE(BankAccount, bank_account, , BANK_ACCOUNT, GObject)

/* BankAccount public API */
BankAccount* bank_account_new(const gchar *account_number, const gchar *owner_name, gdouble initial_balance);

/* Transaction methods that emit signals */
gboolean bank_account_deposit(BankAccount *self, gdouble amount, const gchar *description);
gboolean bank_account_withdraw(BankAccount *self, gdouble amount, const gchar *description);
gboolean bank_account_transfer(BankAccount *from, BankAccount *to, gdouble amount, const gchar *description);

/* Account management */
void bank_account_freeze(BankAccount *self);
void bank_account_unfreeze(BankAccount *self);
void bank_account_set_credit_limit(BankAccount *self, gdouble limit);

/* Property accessors */
gdouble bank_account_get_balance(BankAccount *self);
const gchar* bank_account_get_account_number(BankAccount *self);
gboolean bank_account_is_frozen(BankAccount *self);

/* =============================================================================
 * Counter Class - Demonstrates property change notifications
 * ============================================================================= */

#define TYPE_COUNTER (counter_get_type())
#define COUNTER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_COUNTER, Counter))
#define IS_COUNTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_COUNTER))
G_DECLARE_FINAL_TYPE(Counter, counter, , COUNTER, GObject)

/* Counter public API */
Counter* counter_new(const gchar *name, gint initial_value, gint min, gint max, gint step);

/* Counter operations */
gboolean counter_increment(Counter *self);
gboolean counter_decrement(Counter *self);
gboolean counter_set_value(Counter *self, gint value);
void counter_reset(Counter *self);

/* Property accessors */
gint counter_get_value(Counter *self);
const gchar* counter_get_name(Counter *self);

/* =============================================================================
 * TaskManager Class - Demonstrates complex signal patterns
 * ============================================================================= */

#define TYPE_TASK_MANAGER (task_manager_get_type())
#define TASK_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_TASK_MANAGER, TaskManager))
#define IS_TASK_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_TASK_MANAGER))
G_DECLARE_FINAL_TYPE(TaskManager, task_manager, , TASK_MANAGER, GObject)

/**
 * SignalTask structure for the task manager (renamed to avoid conflicts)
 */
typedef struct {
    gint id;
    gchar *title;
    gchar *description;
    gint priority;  /* 1 = high, 2 = medium, 3 = low */
    gboolean completed;
    GDateTime *created_at;
    GDateTime *completed_at;
} SignalTask;

/* SignalTask helper functions */
SignalTask* signal_task_new(gint id, const gchar *title, const gchar *description, gint priority);
void signal_task_free(SignalTask *task);

/* TaskManager public API */
TaskManager* task_manager_new(const gchar *name);

/* Task operations */
gint task_manager_add_task(TaskManager *self, const gchar *title, const gchar *description, gint priority);
gboolean task_manager_complete_task(TaskManager *self, gint task_id);
gboolean task_manager_remove_task(TaskManager *self, gint task_id);
SignalTask* task_manager_get_task(TaskManager *self, gint task_id);

/* Task queries */
GPtrArray* task_manager_get_tasks_by_priority(TaskManager *self, gint priority);
GPtrArray* task_manager_get_pending_tasks(TaskManager *self);
GPtrArray* task_manager_get_completed_tasks(TaskManager *self);

/* Statistics */
gint task_manager_get_total_tasks(TaskManager *self);
gint task_manager_get_completed_count(TaskManager *self);
gdouble task_manager_get_completion_percentage(TaskManager *self);

/* =============================================================================
 * Event Listener Classes - Demonstrate signal handlers
 * ============================================================================= */

/**
 * Logger class - logs all events
 */
#define TYPE_EVENT_LOGGER (event_logger_get_type())
#define EVENT_LOGGER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_EVENT_LOGGER, EventLogger))
#define IS_EVENT_LOGGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_EVENT_LOGGER))
G_DECLARE_FINAL_TYPE(EventLogger, event_logger, , EVENT_LOGGER, GObject)

EventLogger* event_logger_new(const gchar *log_name);
void event_logger_connect_to_bank_account(EventLogger *self, BankAccount *account);
void event_logger_connect_to_counter(EventLogger *self, Counter *counter);
void event_logger_connect_to_task_manager(EventLogger *self, TaskManager *manager);

/**
 * Notifier class - provides user notifications
 */
#define TYPE_NOTIFICATION_SYSTEM (notification_system_get_type())
#define NOTIFICATION_SYSTEM(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_NOTIFICATION_SYSTEM, NotificationSystem))
#define IS_NOTIFICATION_SYSTEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_NOTIFICATION_SYSTEM))
G_DECLARE_FINAL_TYPE(NotificationSystem, notification_system, , NOTIFICATION_SYSTEM, GObject)

NotificationSystem* notification_system_new(void);
void notification_system_connect_to_bank_account(NotificationSystem *self, BankAccount *account);
void notification_system_connect_to_task_manager(NotificationSystem *self, TaskManager *manager);

/* =============================================================================
 * Utility Functions for Educational Demonstrations
 * ============================================================================= */

/**
 * Demonstrates signal emission and handling
 */
void demonstrate_signal_system(void);

/**
 * Shows property change notifications
 */
void demonstrate_property_notifications(void);

/**
 * Demonstrates interface implementation
 */
void demonstrate_interfaces(void);

/**
 * Shows event-driven programming patterns
 */
void demonstrate_event_driven_programming(void);

/**
 * Main demonstration function
 */
void test_signals_properties(void);

G_END_DECLS

#endif /* TEST_SIGNALS_PROPERTIES_H */
