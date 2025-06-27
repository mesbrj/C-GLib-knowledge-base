## Features Demonstrated

### GObject Basics (Object-Oriented Programming in C)
**Computer Science Fundamentals**: [Object-Oriented Programming](https://en.wikipedia.org/wiki/Object-oriented_programming)

- **Type System**: Runtime type information and introspection - [Type System Theory](https://en.wikipedia.org/wiki/Type_system)
- **Inheritance**: Single inheritance hierarchy with method overriding - [Inheritance in OOP](https://en.wikipedia.org/wiki/Inheritance_(object-oriented_programming))
- **Polymorphism**: Dynamic method dispatch and type casting - [Polymorphism](https://en.wikipedia.org/wiki/Polymorphism_(computer_science))
- **Memory Management**: Reference counting and automatic cleanup - [Memory Management](https://en.wikipedia.org/wiki/Memory_management)
- **Encapsulation**: Private data with public interfaces - [Encapsulation](https://en.wikipedia.org/wiki/Encapsulation_(computer_science))

**Key Learning Outcomes**:
- Understanding object-oriented design in C
- Implementing inheritance without native language support
- Managing object lifecycles and references
- Designing type-safe APIs in C

## Comprehensive Code Examples and Usage

This section provides direct, practical code examples that demonstrate real-world usage patterns for each GLib feature, going beyond the basic demonstrations in the interactive program.

### GObject System - Advanced Examples

#### Custom Object with Inheritance
```c
#include <glib-object.h>

// Base class: Animal
#define TYPE_ANIMAL (animal_get_type())
G_DECLARE_DERIVABLE_TYPE(Animal, animal, , ANIMAL, GObject)

struct _AnimalClass {
    GObjectClass parent_class;
    
    // Virtual methods
    void (*make_sound)(Animal *self);
    void (*move)(Animal *self);
    
    // Padding for future expansion
    gpointer padding[8];
};

// Animal properties
enum {
    ANIMAL_PROP_0,
    ANIMAL_PROP_NAME,
    ANIMAL_PROP_AGE,
    ANIMAL_PROP_SPECIES,
    ANIMAL_N_PROPERTIES
};

static GParamSpec *animal_properties[ANIMAL_N_PROPERTIES] = { NULL, };

// Animal private structure
typedef struct {
    char *name;
    int age;
    char *species;
} AnimalPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(Animal, animal, G_TYPE_OBJECT)

// Animal implementation
static void animal_get_property(GObject *object, guint prop_id, 
                               GValue *value, GParamSpec *pspec) {
    Animal *self = ANIMAL(object);
    AnimalPrivate *priv = animal_get_instance_private(self);
    
    switch (prop_id) {
        case ANIMAL_PROP_NAME:
            g_value_set_string(value, priv->name);
            break;
        case ANIMAL_PROP_AGE:
            g_value_set_int(value, priv->age);
            break;
        case ANIMAL_PROP_SPECIES:
            g_value_set_string(value, priv->species);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void animal_set_property(GObject *object, guint prop_id,
                               const GValue *value, GParamSpec *pspec) {
    Animal *self = ANIMAL(object);
    AnimalPrivate *priv = animal_get_instance_private(self);
    
    switch (prop_id) {
        case ANIMAL_PROP_NAME:
            g_free(priv->name);
            priv->name = g_value_dup_string(value);
            break;
        case ANIMAL_PROP_AGE:
            priv->age = g_value_get_int(value);
            break;
        case ANIMAL_PROP_SPECIES:
            g_free(priv->species);
            priv->species = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

static void animal_finalize(GObject *object) {
    Animal *self = ANIMAL(object);
    AnimalPrivate *priv = animal_get_instance_private(self);
    
    g_free(priv->name);
    g_free(priv->species);
    
    G_OBJECT_CLASS(animal_parent_class)->finalize(object);
}

// Default virtual method implementations
static void animal_make_sound_default(Animal *self) {
    AnimalPrivate *priv = animal_get_instance_private(self);
    g_print("%s makes a generic animal sound\n", priv->name);
}

static void animal_move_default(Animal *self) {
    AnimalPrivate *priv = animal_get_instance_private(self);
    g_print("%s moves around\n", priv->name);
}

static void animal_class_init(AnimalClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = animal_get_property;
    object_class->set_property = animal_set_property;
    object_class->finalize = animal_finalize;
    
    // Set up virtual methods
    klass->make_sound = animal_make_sound_default;
    klass->move = animal_move_default;
    
    // Install properties
    animal_properties[ANIMAL_PROP_NAME] = 
        g_param_spec_string("name", "Name", "The animal's name",
                           NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    
    animal_properties[ANIMAL_PROP_AGE] = 
        g_param_spec_int("age", "Age", "The animal's age",
                        0, 100, 0, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    
    animal_properties[ANIMAL_PROP_SPECIES] = 
        g_param_spec_string("species", "Species", "The animal's species",
                           NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    
    g_object_class_install_properties(object_class, ANIMAL_N_PROPERTIES, animal_properties);
}

static void animal_init(Animal *self) {
    // Instance initialization
}

// Public API
Animal* animal_new(const char *name, int age, const char *species) {
    return g_object_new(TYPE_ANIMAL,
                       "name", name,
                       "age", age,
                       "species", species,
                       NULL);
}

void animal_make_sound(Animal *self) {
    g_return_if_fail(IS_ANIMAL(self));
    
    AnimalClass *klass = ANIMAL_GET_CLASS(self);
    if (klass->make_sound) {
        klass->make_sound(self);
    }
}

void animal_move(Animal *self) {
    g_return_if_fail(IS_ANIMAL(self));
    
    AnimalClass *klass = ANIMAL_GET_CLASS(self);
    if (klass->move) {
        klass->move(self);
    }
}

// Derived class: Dog
#define TYPE_DOG (dog_get_type())
G_DECLARE_FINAL_TYPE(Dog, dog, , DOG, Animal)

struct _Dog {
    Animal parent_instance;
};

G_DEFINE_TYPE(Dog, dog, TYPE_ANIMAL)

// Dog-specific virtual method overrides
static void dog_make_sound(Animal *self) {
    char *name;
    g_object_get(self, "name", &name, NULL);
    g_print("%s barks: Woof! Woof!\n", name);
    g_free(name);
}

static void dog_move(Animal *self) {
    char *name;
    g_object_get(self, "name", &name, NULL);
    g_print("%s runs around wagging its tail\n", name);
    g_free(name);
}

static void dog_class_init(DogClass *klass) {
    AnimalClass *animal_class = ANIMAL_CLASS(klass);
    
    // Override virtual methods
    animal_class->make_sound = dog_make_sound;
    animal_class->move = dog_move;
}

static void dog_init(Dog *self) {
    // Dog-specific initialization
}

// Public API
Dog* dog_new(const char *name, int age) {
    return g_object_new(TYPE_DOG,
                       "name", name,
                       "age", age,
                       "species", "Canis lupus",
                       NULL);
}

void demonstrate_gobject_inheritance() {
    // Create animals
    Animal *generic_animal = animal_new("Generic", 5, "Unknown");
    Dog *dog = dog_new("Buddy", 3);
    Animal *dog_as_animal = ANIMAL(dog);  // Upcast
    
    g_print("=== Polymorphism Demo ===\n");
    
    // Polymorphic calls
    animal_make_sound(generic_animal);  // Uses default implementation
    animal_make_sound(dog_as_animal);   // Uses Dog's override
    
    animal_move(generic_animal);        // Uses default implementation
    animal_move(dog_as_animal);         // Uses Dog's override
    
    g_print("\n=== Property System Demo ===\n");
    
    // Property access
    char *name, *species;
    int age;
    
    g_object_get(dog_as_animal,
                 "name", &name,
                 "age", &age,
                 "species", &species,
                 NULL);
    
    g_print("Dog properties - Name: %s, Age: %d, Species: %s\n", 
            name, age, species);
    
    g_free(name);
    g_free(species);
    
    // Change properties
    g_object_set(dog_as_animal, "age", 4, NULL);
    g_object_get(dog_as_animal, "age", &age, NULL);
    g_print("Updated age: %d\n", age);
    
    g_print("\n=== Type System Demo ===\n");
    
    // Type checking
    g_print("generic_animal is Animal: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(generic_animal, TYPE_ANIMAL) ? "YES" : "NO");
    g_print("dog is Animal: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(dog, TYPE_ANIMAL) ? "YES" : "NO");
    g_print("dog is Dog: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(dog, TYPE_DOG) ? "YES" : "NO");
    g_print("generic_animal is Dog: %s\n", 
            G_TYPE_CHECK_INSTANCE_TYPE(generic_animal, TYPE_DOG) ? "YES" : "NO");
    
    // Cleanup
    g_object_unref(generic_animal);
    g_object_unref(dog);
}
```
