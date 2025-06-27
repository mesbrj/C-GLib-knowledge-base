## Features Demonstrated

### Signals and Properties (Event-Driven Programming)
**Computer Science Fundamentals**: [Observer Pattern](https://en.wikipedia.org/wiki/Observer_pattern) and [Event-Driven Programming](https://en.wikipedia.org/wiki/Event-driven_programming)

- **Signal System**: Observer pattern implementation with type safety - [Signal/Slot Pattern](https://en.wikipedia.org/wiki/Signals_and_slots)
- **Property System**: Automatic change notifications and validation - [Property Pattern](https://en.wikipedia.org/wiki/Property_(programming))
- **Interface Design**: Contract-based programming with interfaces - [Interface Segregation](https://en.wikipedia.org/wiki/Interface_segregation_principle)
- **Event Handling**: Asynchronous communication between objects - [Event Handling](https://en.wikipedia.org/wiki/Event_handling)
- **Loose Coupling**: Decoupled architecture with message passing - [Loose Coupling](https://en.wikipedia.org/wiki/Loose_coupling)

**Key Learning Outcomes**:
- Understanding event-driven architecture patterns
- Implementing observer pattern in C
- Designing reactive user interfaces
- Managing complex object interactions

## Comprehensive Code Examples and Usage

This section provides direct, practical code examples that demonstrate real-world usage patterns for each GLib feature, going beyond the basic demonstrations in the interactive program.

### Signals and Properties - Advanced Examples

#### Complete Event-Driven Application
```c
#include <glib-object.h>

// Custom object with signals and properties
#define TYPE_TEMPERATURE_SENSOR (temperature_sensor_get_type())
G_DECLARE_FINAL_TYPE(TemperatureSensor, temperature_sensor, , TEMPERATURE_SENSOR, GObject)

struct _TemperatureSensor {
    GObject parent_instance;
};

// Properties
enum {
    TEMP_PROP_0,
    TEMP_PROP_TEMPERATURE,
    TEMP_PROP_UNIT,
    TEMP_PROP_THRESHOLD,
    TEMP_N_PROPERTIES
};

// Signals
enum {
    TEMP_SIGNAL_TEMPERATURE_CHANGED,
    TEMP_SIGNAL_THRESHOLD_EXCEEDED,
    TEMP_SIGNAL_SENSOR_ERROR,
    TEMP_N_SIGNALS
};

static GParamSpec *temp_properties[TEMP_N_PROPERTIES] = { NULL, };
static guint temp_signals[TEMP_N_SIGNALS] = { 0 };

// Private structure
typedef struct {
    double temperature;
    char *unit;
    double threshold;
    gboolean is_monitoring;
    guint monitor_source_id;
} TemperatureSensorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(TemperatureSensor, temperature_sensor, G_TYPE_OBJECT)

// Property implementation
static void temperature_sensor_get_property(GObject *object, guint prop_id,
                                           GValue *value, GParamSpec *pspec) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(object);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    switch (prop_id) {
        case TEMP_PROP_TEMPERATURE:
            g_value_set_double(value, priv->temperature);
            break;
        case TEMP_PROP_UNIT:
            g_value_set_string(value, priv->unit);
            break;
        case TEMP_PROP_THRESHOLD:
            g_value_set_double(value, priv->threshold);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void temperature_sensor_set_property(GObject *object, guint prop_id,
                                           const GValue *value, GParamSpec *pspec) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(object);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    switch (prop_id) {
        case TEMP_PROP_TEMPERATURE: {
            double old_temp = priv->temperature;
            priv->temperature = g_value_get_double(value);
            
            // Emit temperature changed signal
            g_signal_emit(self, temp_signals[TEMP_SIGNAL_TEMPERATURE_CHANGED], 0,
                         old_temp, priv->temperature);
            
            // Check threshold
            if (priv->temperature > priv->threshold) {
                g_signal_emit(self, temp_signals[TEMP_SIGNAL_THRESHOLD_EXCEEDED], 0,
                             priv->temperature, priv->threshold);
            }
            break;
        }
        case TEMP_PROP_UNIT:
            g_free(priv->unit);
            priv->unit = g_value_dup_string(value);
            break;
        case TEMP_PROP_THRESHOLD:
            priv->threshold = g_value_get_double(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void temperature_sensor_finalize(GObject *object) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(object);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    if (priv->monitor_source_id > 0) {
        g_source_remove(priv->monitor_source_id);
    }
    
    g_free(priv->unit);
    
    G_OBJECT_CLASS(temperature_sensor_parent_class)->finalize(object);
}

static void temperature_sensor_class_init(TemperatureSensorClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = temperature_sensor_get_property;
    object_class->set_property = temperature_sensor_set_property;
    object_class->finalize = temperature_sensor_finalize;
    
    // Install properties
    temp_properties[TEMP_PROP_TEMPERATURE] = 
        g_param_spec_double("temperature", "Temperature", "Current temperature reading",
                           -273.15, 1000.0, 20.0, 
                           G_PARAM_READWRITE | G_PARAM_NOTIFY);
    
    temp_properties[TEMP_PROP_UNIT] = 
        g_param_spec_string("unit", "Unit", "Temperature unit (C/F/K)",
                           "C", G_PARAM_READWRITE);
    
    temp_properties[TEMP_PROP_THRESHOLD] = 
        g_param_spec_double("threshold", "Threshold", "Temperature threshold for alerts",
                           -273.15, 1000.0, 30.0, 
                           G_PARAM_READWRITE);
    
    g_object_class_install_properties(object_class, TEMP_N_PROPERTIES, temp_properties);
    
    // Install signals
    temp_signals[TEMP_SIGNAL_TEMPERATURE_CHANGED] = 
        g_signal_newv("temperature-changed",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     NULL, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 2,
                     (GType[]){G_TYPE_DOUBLE, G_TYPE_DOUBLE});
    
    temp_signals[TEMP_SIGNAL_THRESHOLD_EXCEEDED] = 
        g_signal_newv("threshold-exceeded",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     NULL, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 2,
                     (GType[]){G_TYPE_DOUBLE, G_TYPE_DOUBLE});
    
    temp_signals[TEMP_SIGNAL_SENSOR_ERROR] = 
        g_signal_newv("sensor-error",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     NULL, NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 1,
                     (GType[]){G_TYPE_STRING});
}

static void temperature_sensor_init(TemperatureSensor *self) {
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    priv->temperature = 20.0;
    priv->unit = g_strdup("C");
    priv->threshold = 30.0;
    priv->is_monitoring = FALSE;
    priv->monitor_source_id = 0;
}

// Public API
TemperatureSensor* temperature_sensor_new(void) {
    return g_object_new(TYPE_TEMPERATURE_SENSOR, NULL);
}

void temperature_sensor_set_temperature(TemperatureSensor *self, double temperature) {
    g_return_if_fail(IS_TEMPERATURE_SENSOR(self));
    g_object_set(self, "temperature", temperature, NULL);
}

double temperature_sensor_get_temperature(TemperatureSensor *self) {
    g_return_val_if_fail(IS_TEMPERATURE_SENSOR(self), 0.0);
    
    double temperature;
    g_object_get(self, "temperature", &temperature, NULL);
    return temperature;
}

// Simulated monitoring with random temperature changes
static gboolean monitor_temperature(gpointer user_data) {
    TemperatureSensor *self = TEMPERATURE_SENSOR(user_data);
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    // Simulate temperature reading with some variation
    double variation = g_random_double_range(-2.0, 2.0);
    double new_temp = priv->temperature + variation;
    
    // Clamp to reasonable range
    new_temp = CLAMP(new_temp, -10.0, 50.0);
    
    // Occasionally simulate sensor error
    if (g_random_double() < 0.05) {  // 5% chance
        g_signal_emit(self, temp_signals[TEMP_SIGNAL_SENSOR_ERROR], 0,
                     "Sensor communication timeout");
        return G_SOURCE_CONTINUE;
    }
    
    // Update temperature (will trigger signals)
    g_object_set(self, "temperature", new_temp, NULL);
    
    return G_SOURCE_CONTINUE;
}

void temperature_sensor_start_monitoring(TemperatureSensor *self) {
    g_return_if_fail(IS_TEMPERATURE_SENSOR(self));
    
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    if (!priv->is_monitoring) {
        priv->is_monitoring = TRUE;
        priv->monitor_source_id = g_timeout_add(1000, monitor_temperature, self);
        g_print("Temperature monitoring started\n");
    }
}

void temperature_sensor_stop_monitoring(TemperatureSensor *self) {
    g_return_if_fail(IS_TEMPERATURE_SENSOR(self));
    
    TemperatureSensorPrivate *priv = temperature_sensor_get_instance_private(self);
    
    if (priv->is_monitoring) {
        priv->is_monitoring = FALSE;
        if (priv->monitor_source_id > 0) {
            g_source_remove(priv->monitor_source_id);
            priv->monitor_source_id = 0;
        }
        g_print("Temperature monitoring stopped\n");
    }
}

// Signal handlers
static void on_temperature_changed(TemperatureSensor *sensor, 
                                  double old_temp, double new_temp, 
                                  gpointer user_data) {
    char *unit;
    g_object_get(sensor, "unit", &unit, NULL);
    
    g_print("📊 Temperature changed: %.1f°%s → %.1f°%s (Δ%.1f°%s)\n",
            old_temp, unit, new_temp, unit, new_temp - old_temp, unit);
    
    g_free(unit);
}

static void on_threshold_exceeded(TemperatureSensor *sensor,
                                 double temperature, double threshold,
                                 gpointer user_data) {
    char *unit;
    g_object_get(sensor, "unit", &unit, NULL);
    
    g_print("🔥 ALERT: Temperature %.1f°%s exceeds threshold %.1f°%s!\n",
            temperature, unit, threshold, unit);
    
    g_free(unit);
}

static void on_sensor_error(TemperatureSensor *sensor, 
                           const char *error_message,
                           gpointer user_data) {
    g_print("❌ Sensor Error: %s\n", error_message);
}

// Property change notification
static void on_property_notify(GObject *object, GParamSpec *pspec, gpointer user_data) {
    const char *property_name = g_param_spec_get_name(pspec);
    g_print("🔔 Property '%s' changed\n", property_name);
}

void demonstrate_signals_and_properties() {
    // Create temperature sensor
    TemperatureSensor *sensor = temperature_sensor_new();
    
    // Connect signals
    g_signal_connect(sensor, "temperature-changed", 
                    G_CALLBACK(on_temperature_changed), NULL);
    g_signal_connect(sensor, "threshold-exceeded", 
                    G_CALLBACK(on_threshold_exceeded), NULL);
    g_signal_connect(sensor, "sensor-error", 
                    G_CALLBACK(on_sensor_error), NULL);
    
    // Connect to property notifications
    g_signal_connect(sensor, "notify", 
                    G_CALLBACK(on_property_notify), NULL);
    
    g_print("=== Temperature Sensor Demo ===\n");
    
    // Set initial values
    g_object_set(sensor,
                 "temperature", 25.0,
                 "threshold", 28.0,
                 "unit", "C",
                 NULL);
    
    // Manual temperature changes
    g_print("\n--- Manual Temperature Changes ---\n");
    temperature_sensor_set_temperature(sensor, 26.5);
    temperature_sensor_set_temperature(sensor, 29.2);  // Should exceed threshold
    temperature_sensor_set_temperature(sensor, 27.8);
    
    // Change threshold
    g_print("\n--- Threshold Change ---\n");
    g_object_set(sensor, "threshold", 27.0, NULL);
    
    // Start monitoring
    g_print("\n--- Automatic Monitoring (5 seconds) ---\n");
    temperature_sensor_start_monitoring(sensor);
    
    // Run main loop for 5 seconds
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_timeout_add(5000, (GSourceFunc)g_main_loop_quit, loop);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
    
    // Stop monitoring
    temperature_sensor_stop_monitoring(sensor);
    
    // Cleanup
    g_object_unref(sensor);
}
```
