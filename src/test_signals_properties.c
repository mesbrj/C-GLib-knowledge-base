#include "test_signals_properties.h"
#include <stdio.h>
#include <string.h>

/* =============================================================================
 * IComparable Interface Implementation
 * ============================================================================= */

G_DEFINE_INTERFACE(Comparable, comparable, G_TYPE_OBJECT)

static void comparable_default_init(ComparableInterface *iface) {
    /* Interface initialization - define default implementations if needed */
    (void)iface; /* Suppress unused parameter warning */
}

gint comparable_compare(Comparable *self, Comparable *other) {
    g_return_val_if_fail(IS_COMPARABLE(self), 0);
    g_return_val_if_fail(IS_COMPARABLE(other), 0);
    
    ComparableInterface *iface = COMPARABLE_GET_IFACE(self);
    g_return_val_if_fail(iface->compare != NULL, 0);
    
    return iface->compare(self, other);
}

gboolean comparable_equals(Comparable *self, Comparable *other) {
    g_return_val_if_fail(IS_COMPARABLE(self), FALSE);
    g_return_val_if_fail(IS_COMPARABLE(other), FALSE);
    
    ComparableInterface *iface = COMPARABLE_GET_IFACE(self);
    if (iface->equals) {
        return iface->equals(self, other);
    }
    
    /* Default implementation using compare */
    return comparable_compare(self, other) == 0;
}

/* =============================================================================
 * BankAccount Class Implementation - Signal System Demonstration
 * ============================================================================= */

struct _BankAccount {
    GObject parent_instance;
    gchar *account_number;
    gchar *owner_name;
    gdouble balance;
    gdouble credit_limit;
    gboolean is_frozen;
};

/* Property enumeration */
enum {
    BANK_ACCOUNT_PROP_0,
    BANK_ACCOUNT_PROP_ACCOUNT_NUMBER,
    BANK_ACCOUNT_PROP_OWNER_NAME,
    BANK_ACCOUNT_PROP_BALANCE,
    BANK_ACCOUNT_PROP_CREDIT_LIMIT,
    BANK_ACCOUNT_PROP_IS_FROZEN,
    BANK_ACCOUNT_N_PROPERTIES
};

/* Signal enumeration */
enum {
    BANK_ACCOUNT_SIGNAL_DEPOSIT,
    BANK_ACCOUNT_SIGNAL_WITHDRAWAL,
    BANK_ACCOUNT_SIGNAL_TRANSFER_IN,
    BANK_ACCOUNT_SIGNAL_TRANSFER_OUT,
    BANK_ACCOUNT_SIGNAL_LOW_BALANCE,
    BANK_ACCOUNT_SIGNAL_ACCOUNT_FROZEN,
    BANK_ACCOUNT_SIGNAL_ACCOUNT_UNFROZEN,
    BANK_ACCOUNT_N_SIGNALS
};

static GParamSpec *bank_account_properties[BANK_ACCOUNT_N_PROPERTIES] = { NULL, };
static guint bank_account_signals[BANK_ACCOUNT_N_SIGNALS] = { 0, };

G_DEFINE_TYPE(BankAccount, bank_account, G_TYPE_OBJECT)

static void bank_account_get_property(GObject *object, guint property_id,
                                     GValue *value, GParamSpec *pspec) {
    BankAccount *self = BANK_ACCOUNT(object);
    
    switch (property_id) {
        case BANK_ACCOUNT_PROP_ACCOUNT_NUMBER:
            g_value_set_string(value, self->account_number);
            break;
        case BANK_ACCOUNT_PROP_OWNER_NAME:
            g_value_set_string(value, self->owner_name);
            break;
        case BANK_ACCOUNT_PROP_BALANCE:
            g_value_set_double(value, self->balance);
            break;
        case BANK_ACCOUNT_PROP_CREDIT_LIMIT:
            g_value_set_double(value, self->credit_limit);
            break;
        case BANK_ACCOUNT_PROP_IS_FROZEN:
            g_value_set_boolean(value, self->is_frozen);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void bank_account_set_property(GObject *object, guint property_id,
                                     const GValue *value, GParamSpec *pspec) {
    BankAccount *self = BANK_ACCOUNT(object);
    
    switch (property_id) {
        case BANK_ACCOUNT_PROP_ACCOUNT_NUMBER:
            g_free(self->account_number);
            self->account_number = g_value_dup_string(value);
            break;
        case BANK_ACCOUNT_PROP_OWNER_NAME:
            g_free(self->owner_name);
            self->owner_name = g_value_dup_string(value);
            break;
        case BANK_ACCOUNT_PROP_BALANCE:
            self->balance = g_value_get_double(value);
            break;
        case BANK_ACCOUNT_PROP_CREDIT_LIMIT:
            self->credit_limit = g_value_get_double(value);
            break;
        case BANK_ACCOUNT_PROP_IS_FROZEN:
            self->is_frozen = g_value_get_boolean(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void bank_account_finalize(GObject *object) {
    BankAccount *self = BANK_ACCOUNT(object);
    
    printf("[Memory] Finalizing BankAccount: %s\n", self->account_number);
    
    g_free(self->account_number);
    g_free(self->owner_name);
    
    G_OBJECT_CLASS(bank_account_parent_class)->finalize(object);
}

static void bank_account_class_init(BankAccountClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = bank_account_get_property;
    object_class->set_property = bank_account_set_property;
    object_class->finalize = bank_account_finalize;
    
    /* Properties */
    bank_account_properties[BANK_ACCOUNT_PROP_ACCOUNT_NUMBER] = 
        g_param_spec_string("account-number", "Account Number", "Bank account number",
                           NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    bank_account_properties[BANK_ACCOUNT_PROP_OWNER_NAME] = 
        g_param_spec_string("owner-name", "Owner Name", "Account owner's name",
                           NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    bank_account_properties[BANK_ACCOUNT_PROP_BALANCE] = 
        g_param_spec_double("balance", "Balance", "Current account balance",
                           -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, 
                           G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);
    
    bank_account_properties[BANK_ACCOUNT_PROP_CREDIT_LIMIT] = 
        g_param_spec_double("credit-limit", "Credit Limit", "Account credit limit",
                           0.0, G_MAXDOUBLE, 0.0, 
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    bank_account_properties[BANK_ACCOUNT_PROP_IS_FROZEN] = 
        g_param_spec_boolean("is-frozen", "Is Frozen", "Whether the account is frozen",
                            FALSE, G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);
    
    g_object_class_install_properties(object_class, BANK_ACCOUNT_N_PROPERTIES, bank_account_properties);
    
    /* Signals */
    bank_account_signals[BANK_ACCOUNT_SIGNAL_DEPOSIT] = 
        g_signal_new("deposit",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 3,
                     G_TYPE_DOUBLE,    /* amount */
                     G_TYPE_STRING,    /* description */
                     G_TYPE_DOUBLE);   /* new balance */
    
    bank_account_signals[BANK_ACCOUNT_SIGNAL_WITHDRAWAL] = 
        g_signal_new("withdrawal",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 3,
                     G_TYPE_DOUBLE,    /* amount */
                     G_TYPE_STRING,    /* description */
                     G_TYPE_DOUBLE);   /* new balance */
    
    bank_account_signals[BANK_ACCOUNT_SIGNAL_LOW_BALANCE] = 
        g_signal_new("low-balance",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 1,
                     G_TYPE_DOUBLE);   /* current balance */
    
    bank_account_signals[BANK_ACCOUNT_SIGNAL_ACCOUNT_FROZEN] = 
        g_signal_new("account-frozen",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);
    
    bank_account_signals[BANK_ACCOUNT_SIGNAL_ACCOUNT_UNFROZEN] = 
        g_signal_new("account-unfrozen",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);
}

static void bank_account_init(BankAccount *self) {
    self->account_number = NULL;
    self->owner_name = NULL;
    self->balance = 0.0;
    self->credit_limit = 0.0;
    self->is_frozen = FALSE;
    
    printf("[Object] BankAccount instance created\n");
}

BankAccount* bank_account_new(const gchar *account_number, const gchar *owner_name, gdouble initial_balance) {
    BankAccount *account = g_object_new(TYPE_BANK_ACCOUNT,
                                       "account-number", account_number,
                                       "owner-name", owner_name,
                                       NULL);
    
    account->balance = initial_balance;
    return account;
}

gboolean bank_account_deposit(BankAccount *self, gdouble amount, const gchar *description) {
    g_return_val_if_fail(IS_BANK_ACCOUNT(self), FALSE);
    g_return_val_if_fail(amount > 0, FALSE);
    
    if (self->is_frozen) {
        printf("Transaction denied: Account is frozen\n");
        return FALSE;
    }
    
    self->balance += amount;
    
    /* Emit deposit signal */
    g_signal_emit(self, bank_account_signals[BANK_ACCOUNT_SIGNAL_DEPOSIT], 0,
                  amount, description ? description : "Deposit", self->balance);
    
    /* Notify property change */
    g_object_notify_by_pspec(G_OBJECT(self), bank_account_properties[BANK_ACCOUNT_PROP_BALANCE]);
    
    return TRUE;
}

gboolean bank_account_withdraw(BankAccount *self, gdouble amount, const gchar *description) {
    g_return_val_if_fail(IS_BANK_ACCOUNT(self), FALSE);
    g_return_val_if_fail(amount > 0, FALSE);
    
    if (self->is_frozen) {
        printf("Transaction denied: Account is frozen\n");
        return FALSE;
    }
    
    /* Check if withdrawal is allowed (balance + credit limit) */
    if (self->balance + self->credit_limit < amount) {
        printf("Transaction denied: Insufficient funds\n");
        return FALSE;
    }
    
    self->balance -= amount;
    
    /* Emit withdrawal signal */
    g_signal_emit(self, bank_account_signals[BANK_ACCOUNT_SIGNAL_WITHDRAWAL], 0,
                  amount, description ? description : "Withdrawal", self->balance);
    
    /* Check for low balance */
    if (self->balance < 100.0) {
        g_signal_emit(self, bank_account_signals[BANK_ACCOUNT_SIGNAL_LOW_BALANCE], 0, self->balance);
    }
    
    /* Notify property change */
    g_object_notify_by_pspec(G_OBJECT(self), bank_account_properties[BANK_ACCOUNT_PROP_BALANCE]);
    
    return TRUE;
}

void bank_account_freeze(BankAccount *self) {
    g_return_if_fail(IS_BANK_ACCOUNT(self));
    
    if (!self->is_frozen) {
        self->is_frozen = TRUE;
        g_signal_emit(self, bank_account_signals[BANK_ACCOUNT_SIGNAL_ACCOUNT_FROZEN], 0);
        g_object_notify_by_pspec(G_OBJECT(self), bank_account_properties[BANK_ACCOUNT_PROP_IS_FROZEN]);
    }
}

void bank_account_unfreeze(BankAccount *self) {
    g_return_if_fail(IS_BANK_ACCOUNT(self));
    
    if (self->is_frozen) {
        self->is_frozen = FALSE;
        g_signal_emit(self, bank_account_signals[BANK_ACCOUNT_SIGNAL_ACCOUNT_UNFROZEN], 0);
        g_object_notify_by_pspec(G_OBJECT(self), bank_account_properties[BANK_ACCOUNT_PROP_IS_FROZEN]);
    }
}

gdouble bank_account_get_balance(BankAccount *self) {
    g_return_val_if_fail(IS_BANK_ACCOUNT(self), 0.0);
    return self->balance;
}

const gchar* bank_account_get_account_number(BankAccount *self) {
    g_return_val_if_fail(IS_BANK_ACCOUNT(self), NULL);
    return self->account_number;
}

gboolean bank_account_is_frozen(BankAccount *self) {
    g_return_val_if_fail(IS_BANK_ACCOUNT(self), FALSE);
    return self->is_frozen;
}

/* =============================================================================
 * Counter Class Implementation - Property Notifications
 * ============================================================================= */

struct _Counter {
    GObject parent_instance;
    gint value;
    gint minimum;
    gint maximum;
    gint step;
    gchar *name;
};

enum {
    COUNTER_PROP_0,
    COUNTER_PROP_VALUE,
    COUNTER_PROP_MINIMUM,
    COUNTER_PROP_MAXIMUM,
    COUNTER_PROP_STEP,
    COUNTER_PROP_NAME,
    COUNTER_N_PROPERTIES
};

enum {
    COUNTER_SIGNAL_VALUE_CHANGED,
    COUNTER_SIGNAL_LIMIT_REACHED,
    COUNTER_SIGNAL_RESET,
    COUNTER_N_SIGNALS
};

static GParamSpec *counter_properties[COUNTER_N_PROPERTIES] = { NULL, };
static guint counter_signals[COUNTER_N_SIGNALS] = { 0, };

G_DEFINE_TYPE(Counter, counter, G_TYPE_OBJECT)

static void counter_get_property(GObject *object, guint property_id,
                                GValue *value, GParamSpec *pspec) {
    Counter *self = COUNTER(object);
    
    switch (property_id) {
        case COUNTER_PROP_VALUE:
            g_value_set_int(value, self->value);
            break;
        case COUNTER_PROP_MINIMUM:
            g_value_set_int(value, self->minimum);
            break;
        case COUNTER_PROP_MAXIMUM:
            g_value_set_int(value, self->maximum);
            break;
        case COUNTER_PROP_STEP:
            g_value_set_int(value, self->step);
            break;
        case COUNTER_PROP_NAME:
            g_value_set_string(value, self->name);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void counter_set_property(GObject *object, guint property_id,
                                const GValue *value, GParamSpec *pspec) {
    Counter *self = COUNTER(object);
    
    switch (property_id) {
        case COUNTER_PROP_VALUE:
            counter_set_value(self, g_value_get_int(value));
            break;
        case COUNTER_PROP_MINIMUM:
            self->minimum = g_value_get_int(value);
            break;
        case COUNTER_PROP_MAXIMUM:
            self->maximum = g_value_get_int(value);
            break;
        case COUNTER_PROP_STEP:
            self->step = g_value_get_int(value);
            break;
        case COUNTER_PROP_NAME:
            g_free(self->name);
            self->name = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void counter_finalize(GObject *object) {
    Counter *self = COUNTER(object);
    g_free(self->name);
    G_OBJECT_CLASS(counter_parent_class)->finalize(object);
}

static void counter_class_init(CounterClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = counter_get_property;
    object_class->set_property = counter_set_property;
    object_class->finalize = counter_finalize;
    
    /* Properties with change notifications */
    counter_properties[COUNTER_PROP_VALUE] = 
        g_param_spec_int("value", "Value", "Current counter value",
                        G_MININT, G_MAXINT, 0, 
                        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    counter_properties[COUNTER_PROP_NAME] = 
        g_param_spec_string("name", "Name", "Counter name",
                           NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    g_object_class_install_properties(object_class, COUNTER_N_PROPERTIES, counter_properties);
    
    /* Signals */
    counter_signals[COUNTER_SIGNAL_VALUE_CHANGED] = 
        g_signal_new("value-changed",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 2,
                     G_TYPE_INT,    /* old value */
                     G_TYPE_INT);   /* new value */
    
    counter_signals[COUNTER_SIGNAL_LIMIT_REACHED] = 
        g_signal_new("limit-reached",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 2,
                     G_TYPE_INT,        /* limit value */
                     G_TYPE_BOOLEAN);   /* is maximum? */
}

static void counter_init(Counter *self) {
    self->value = 0;
    self->minimum = G_MININT;
    self->maximum = G_MAXINT;
    self->step = 1;
    self->name = NULL;
}

Counter* counter_new(const gchar *name, gint initial_value, gint min, gint max, gint step) {
    return g_object_new(TYPE_COUNTER,
                       "name", name,
                       "value", initial_value,
                       "minimum", min,
                       "maximum", max,
                       "step", step,
                       NULL);
}

gboolean counter_set_value(Counter *self, gint value) {
    g_return_val_if_fail(IS_COUNTER(self), FALSE);
    
    if (value < self->minimum || value > self->maximum) {
        return FALSE;
    }
    
    gint old_value = self->value;
    self->value = value;
    
    g_signal_emit(self, counter_signals[COUNTER_SIGNAL_VALUE_CHANGED], 0, old_value, value);
    
    return TRUE;
}

gboolean counter_increment(Counter *self) {
    g_return_val_if_fail(IS_COUNTER(self), FALSE);
    
    if (self->value + self->step > self->maximum) {
        g_signal_emit(self, counter_signals[COUNTER_SIGNAL_LIMIT_REACHED], 0, self->maximum, TRUE);
        return FALSE;
    }
    
    return counter_set_value(self, self->value + self->step);
}

gboolean counter_decrement(Counter *self) {
    g_return_val_if_fail(IS_COUNTER(self), FALSE);
    
    if (self->value - self->step < self->minimum) {
        g_signal_emit(self, counter_signals[COUNTER_SIGNAL_LIMIT_REACHED], 0, self->minimum, FALSE);
        return FALSE;
    }
    
    return counter_set_value(self, self->value - self->step);
}

void counter_reset(Counter *self) {
    g_return_if_fail(IS_COUNTER(self));
    counter_set_value(self, 0);
    g_signal_emit(self, counter_signals[COUNTER_SIGNAL_RESET], 0);
}

gint counter_get_value(Counter *self) {
    g_return_val_if_fail(IS_COUNTER(self), 0);
    return self->value;
}

const gchar* counter_get_name(Counter *self) {
    g_return_val_if_fail(IS_COUNTER(self), NULL);
    return self->name;
}

/* =============================================================================
 * Event Logger Implementation
 * ============================================================================= */

struct _EventLogger {
    GObject parent_instance;
    gchar *log_name;
    FILE *log_file;
};

G_DEFINE_TYPE(EventLogger, event_logger, G_TYPE_OBJECT)

static void event_logger_finalize(GObject *object) {
    EventLogger *self = EVENT_LOGGER(object);
    
    g_free(self->log_name);
    if (self->log_file && self->log_file != stdout) {
        fclose(self->log_file);
    }
    
    G_OBJECT_CLASS(event_logger_parent_class)->finalize(object);
}

static void event_logger_class_init(EventLoggerClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = event_logger_finalize;
}

static void event_logger_init(EventLogger *self) {
    self->log_name = NULL;
    self->log_file = stdout;  /* Default to stdout */
}

EventLogger* event_logger_new(const gchar *log_name) {
    EventLogger *logger = g_object_new(TYPE_EVENT_LOGGER, NULL);
    logger->log_name = g_strdup(log_name);
    return logger;
}

/* Signal handlers for bank account */
static void on_bank_deposit(BankAccount *account, gdouble amount, const gchar *description, 
                           gdouble new_balance, EventLogger *logger) {
    fprintf(logger->log_file, "[%s] DEPOSIT: $%.2f - %s (New Balance: $%.2f) [Account: %s]\n",
            logger->log_name, amount, description, new_balance, 
            bank_account_get_account_number(account));
}

static void on_bank_withdrawal(BankAccount *account, gdouble amount, const gchar *description,
                              gdouble new_balance, EventLogger *logger) {
    fprintf(logger->log_file, "[%s] WITHDRAWAL: $%.2f - %s (New Balance: $%.2f) [Account: %s]\n",
            logger->log_name, amount, description, new_balance,
            bank_account_get_account_number(account));
}

static void on_low_balance(BankAccount *account, gdouble balance, EventLogger *logger) {
    fprintf(logger->log_file, "[%s] WARNING: Low balance $%.2f [Account: %s]\n",
            logger->log_name, balance, bank_account_get_account_number(account));
}

void event_logger_connect_to_bank_account(EventLogger *self, BankAccount *account) {
    g_signal_connect(account, "deposit", G_CALLBACK(on_bank_deposit), self);
    g_signal_connect(account, "withdrawal", G_CALLBACK(on_bank_withdrawal), self);
    g_signal_connect(account, "low-balance", G_CALLBACK(on_low_balance), self);
}

/* Signal handlers for counter */
static void on_counter_value_changed(Counter *counter, gint old_value, gint new_value, EventLogger *logger) {
    fprintf(logger->log_file, "[%s] COUNTER '%s': %d -> %d\n",
            logger->log_name, counter_get_name(counter), old_value, new_value);
}

void event_logger_connect_to_counter(EventLogger *self, Counter *counter) {
    g_signal_connect(counter, "value-changed", G_CALLBACK(on_counter_value_changed), self);
}

/* =============================================================================
 * Educational Demonstration Functions
 * ============================================================================= */

void demonstrate_signal_system(void) {
    printf("\n=== Signal System Demonstration ===\n");
    printf("Demonstrating Observer pattern with GObject signals\n\n");
    
    /* Create bank account and logger */
    BankAccount *account = bank_account_new("12345-67890", "Alice Johnson", 1000.0);
    EventLogger *logger = event_logger_new("BankLogger");
    
    /* Connect signals */
    event_logger_connect_to_bank_account(logger, account);
    
    printf("Initial balance: $%.2f\n", bank_account_get_balance(account));
    
    /* Perform transactions - signals will be emitted */
    printf("\nPerforming transactions:\n");
    bank_account_deposit(account, 250.0, "Salary deposit");
    bank_account_withdraw(account, 75.0, "ATM withdrawal");
    bank_account_withdraw(account, 1100.0, "Large purchase");  /* Should trigger low balance */
    
    /* Cleanup */
    g_object_unref(account);
    g_object_unref(logger);
}

void demonstrate_property_notifications(void) {
    printf("\n=== Property Notification Demonstration ===\n");
    printf("Demonstrating automatic property change notifications\n\n");
    
    Counter *counter = counter_new("TestCounter", 0, 0, 10, 1);
    EventLogger *logger = event_logger_new("CounterLogger");
    
    /* Connect to property change notifications */
    event_logger_connect_to_counter(logger, counter);
    
    /* Property change listener */
    g_signal_connect(counter, "notify::value", 
                     G_CALLBACK(g_print), "Property 'value' changed!\n");
    
    printf("Initial counter value: %d\n", counter_get_value(counter));
    
    /* Increment/decrement operations */
    printf("\nCounter operations:\n");
    for (int i = 0; i < 12; i++) {  /* Will hit maximum limit */
        if (!counter_increment(counter)) {
            printf("Hit maximum limit!\n");
            break;
        }
    }
    
    counter_reset(counter);
    
    g_object_unref(counter);
    g_object_unref(logger);
}

void demonstrate_event_driven_programming(void) {
    printf("\n=== Event-Driven Programming Demonstration ===\n");
    printf("Demonstrating complex event handling patterns\n\n");
    
    /* Create multiple accounts and a centralized logger */
    BankAccount *account1 = bank_account_new("111-111", "John Doe", 500.0);
    BankAccount *account2 = bank_account_new("222-222", "Jane Smith", 1500.0);
    EventLogger *central_logger = event_logger_new("CentralBank");
    
    /* Connect all accounts to central logger */
    event_logger_connect_to_bank_account(central_logger, account1);
    event_logger_connect_to_bank_account(central_logger, account2);
    
    /* Simulate banking operations */
    printf("Simulating banking operations:\n");
    bank_account_deposit(account1, 200.0, "Direct deposit");
    bank_account_withdraw(account2, 300.0, "Bill payment");
    
    /* Freeze account and try transaction */
    printf("\nFreezing account and attempting transaction:\n");
    bank_account_freeze(account1);
    bank_account_withdraw(account1, 50.0, "ATM attempt");  /* Should fail */
    bank_account_unfreeze(account1);
    bank_account_withdraw(account1, 50.0, "ATM success");  /* Should succeed */
    
    /* Cleanup */
    g_object_unref(account1);
    g_object_unref(account2);
    g_object_unref(central_logger);
}

void test_signals_properties(void) {
    printf("\n=== GObject Signals and Properties Educational Demonstration ===\n");
    printf("Learning Objectives:\n");
    printf("- Signal system (Observer pattern implementation)\n");
    printf("- Property system with change notifications\n");
    printf("- Event-driven programming patterns\n");
    printf("- Interface implementation\n\n");
    
    /* Run demonstrations */
    demonstrate_signal_system();
    demonstrate_property_notifications();
    demonstrate_event_driven_programming();
    
    printf("\nSignals and Properties demonstration completed!\n");
}
