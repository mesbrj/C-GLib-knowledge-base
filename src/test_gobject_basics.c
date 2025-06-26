#include "test_gobject_basics.h"
#include <stdio.h>
#include <string.h>

/* =============================================================================
 * Person Class Implementation
 * ============================================================================= */

struct _Person {
    GObject parent_instance;
    gchar *name;
    gint age;
    gchar *email;
};

/* Property enumeration for Person class */
enum {
    PERSON_PROP_0,
    PERSON_PROP_NAME,
    PERSON_PROP_AGE,
    PERSON_PROP_EMAIL,
    PERSON_N_PROPERTIES
};

static GParamSpec *person_properties[PERSON_N_PROPERTIES] = { NULL, };

/* Define the Person type - this creates the class structure */
G_DEFINE_TYPE(Person, person, G_TYPE_OBJECT)

/* Property getter */
static void person_get_property(GObject *object, guint property_id,
                               GValue *value, GParamSpec *pspec) {
    Person *self = (Person*)object;
    
    switch (property_id) {
        case PERSON_PROP_NAME:
            g_value_set_string(value, self->name);
            break;
        case PERSON_PROP_AGE:
            g_value_set_int(value, self->age);
            break;
        case PERSON_PROP_EMAIL:
            g_value_set_string(value, self->email);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

/* Property setter */
static void person_set_property(GObject *object, guint property_id,
                               const GValue *value, GParamSpec *pspec) {
    Person *self = (Person*)object;
    
    switch (property_id) {
        case PERSON_PROP_NAME:
            g_free(self->name);
            self->name = g_value_dup_string(value);
            break;
        case PERSON_PROP_AGE:
            self->age = g_value_get_int(value);
            break;
        case PERSON_PROP_EMAIL:
            g_free(self->email);
            self->email = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

/* Destructor - called when reference count reaches zero */
static void person_finalize(GObject *object) {
    Person *self = (Person*)object;
    
    printf("[Memory] Finalizing Person: %s\n", self->name ? self->name : "Unknown");
    
    g_free(self->name);
    g_free(self->email);
    
    /* Chain up to parent class */
    G_OBJECT_CLASS(person_parent_class)->finalize(object);
}

/* Class initialization - sets up the class structure */
static void person_class_init(PersonClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    /* Set up virtual methods */
    object_class->get_property = person_get_property;
    object_class->set_property = person_set_property;
    object_class->finalize = person_finalize;
    
    /* Define properties with validation */
    person_properties[PERSON_PROP_NAME] = 
        g_param_spec_string("name", "Name", "Person's full name",
                           NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    person_properties[PERSON_PROP_AGE] = 
        g_param_spec_int("age", "Age", "Person's age in years",
                        0, 150, 0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    person_properties[PERSON_PROP_EMAIL] = 
        g_param_spec_string("email", "Email", "Person's email address",
                           NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    /* Install properties */
    g_object_class_install_properties(object_class, PERSON_N_PROPERTIES, person_properties);
}

/* Instance initialization - sets up the object instance */
static void person_init(Person *self) {
    /* Initialize instance variables */
    self->name = NULL;
    self->age = 0;
    self->email = NULL;
    
    printf("[Object] Person instance created\n");
}

/* Public constructor */
Person* person_new(const gchar *name, gint age, const gchar *email) {
    Person *person = g_object_new(TYPE_PERSON, NULL);
    
    /* Set properties directly */
    person->name = g_strdup(name);
    person->age = age;
    person->email = g_strdup(email);
    
    return person;
}

/* Constructor using property system */
Person* person_new_with_properties(const gchar *name, gint age, const gchar *email) {
    return g_object_new(TYPE_PERSON,
                       "name", name,
                       "age", age,
                       "email", email,
                       NULL);
}

/* Virtual method - can be overridden by subclasses */
void person_introduce(Person *self) {
    g_return_if_fail(IS_PERSON(self));
    printf("Hello, I'm %s, %d years old.\n", 
           self->name ? self->name : "Unknown", self->age);
}

gchar* person_get_description(Person *self) {
    g_return_val_if_fail(IS_PERSON(self), NULL);
    return g_strdup_printf("Person: %s (%d years old, %s)", 
                          self->name ? self->name : "Unknown",
                          self->age,
                          self->email ? self->email : "no email");
}

gboolean person_is_adult(Person *self) {
    g_return_val_if_fail(IS_PERSON(self), FALSE);
    return self->age >= 18;
}

/* Property accessors */
const gchar* person_get_name(Person *self) {
    g_return_val_if_fail(IS_PERSON(self), NULL);
    return self->name;
}

void person_set_name(Person *self, const gchar *name) {
    g_return_if_fail(IS_PERSON(self));
    g_object_set(self, "name", name, NULL);
}

gint person_get_age(Person *self) {
    g_return_val_if_fail(IS_PERSON(self), 0);
    return self->age;
}

void person_set_age(Person *self, gint age) {
    g_return_if_fail(IS_PERSON(self));
    g_object_set(self, "age", age, NULL);
}

/* =============================================================================
 * Student Class Implementation - Demonstrates Inheritance
 * ============================================================================= */

struct _Student {
    Person parent_instance;
    gint student_id;
    gdouble gpa;
    gchar *major;
    GArray *grades;
};

/* Student properties */
enum {
    STUDENT_PROP_0,
    STUDENT_PROP_STUDENT_ID,
    STUDENT_PROP_GPA,
    STUDENT_PROP_MAJOR,
    STUDENT_N_PROPERTIES
};

static GParamSpec *student_properties[STUDENT_N_PROPERTIES] = { NULL, };

G_DEFINE_TYPE(Student, student, TYPE_PERSON)

static void student_get_property(GObject *object, guint property_id,
                                GValue *value, GParamSpec *pspec) {
    Student *self = (Student*)object;
    
    switch (property_id) {
        case STUDENT_PROP_STUDENT_ID:
            g_value_set_int(value, self->student_id);
            break;
        case STUDENT_PROP_GPA:
            g_value_set_double(value, self->gpa);
            break;
        case STUDENT_PROP_MAJOR:
            g_value_set_string(value, self->major);
            break;
        default:
            /* Chain up to parent for inherited properties */
            G_OBJECT_CLASS(student_parent_class)->get_property(object, property_id, value, pspec);
            break;
    }
}

static void student_set_property(GObject *object, guint property_id,
                                const GValue *value, GParamSpec *pspec) {
    Student *self = (Student*)object;
    
    switch (property_id) {
        case STUDENT_PROP_STUDENT_ID:
            self->student_id = g_value_get_int(value);
            break;
        case STUDENT_PROP_GPA:
            self->gpa = g_value_get_double(value);
            break;
        case STUDENT_PROP_MAJOR:
            g_free(self->major);
            self->major = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_CLASS(student_parent_class)->set_property(object, property_id, value, pspec);
            break;
    }
}

static void student_finalize(GObject *object) {
    Student *self = (Student*)object;
    
    printf("[Memory] Finalizing Student ID: %d\n", self->student_id);
    
    g_free(self->major);
    if (self->grades) {
        g_array_free(self->grades, TRUE);
    }
    
    /* Chain up to parent */
    G_OBJECT_CLASS(student_parent_class)->finalize(object);
}

static void student_class_init(StudentClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    
    object_class->get_property = student_get_property;
    object_class->set_property = student_set_property;
    object_class->finalize = student_finalize;
    
    /* Student-specific properties */
    student_properties[STUDENT_PROP_STUDENT_ID] = 
        g_param_spec_int("student-id", "Student ID", "Unique student identifier",
                        1, G_MAXINT, 1, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    student_properties[STUDENT_PROP_GPA] = 
        g_param_spec_double("gpa", "GPA", "Grade Point Average",
                           0.0, 4.0, 0.0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    student_properties[STUDENT_PROP_MAJOR] = 
        g_param_spec_string("major", "Major", "Academic major/field of study",
                           NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    
    g_object_class_install_properties(object_class, STUDENT_N_PROPERTIES, student_properties);
}

static void student_init(Student *self) {
    self->student_id = 0;
    self->gpa = 0.0;
    self->major = NULL;
    self->grades = g_array_new(FALSE, FALSE, sizeof(gint));
    
    printf("[Object] Student instance created\n");
}

Student* student_new(const gchar *name, gint age, const gchar *email, 
                     gint student_id, const gchar *major) {
    return g_object_new(TYPE_STUDENT,
                       "name", name,
                       "age", age,
                       "email", email,
                       "student-id", student_id,
                       "major", major,
                       NULL);
}

/* Method overriding - demonstrates polymorphism */
void student_introduce(Student *self) {
    g_return_if_fail(IS_STUDENT(self));
    
    /* Get parent properties */
    Person *person = PERSON(self);
    printf("Hi, I'm %s, a %d-year-old %s student (ID: %d, GPA: %.2f).\n",
           person_get_name(person), person_get_age(person),
           self->major ? self->major : "undeclared",
           self->student_id, self->gpa);
}

gchar* student_get_description(Student *self) {
    g_return_val_if_fail(IS_STUDENT(self), NULL);
    
    Person *person = PERSON(self);
    return g_strdup_printf("Student: %s (ID: %d, Major: %s, GPA: %.2f)",
                          person_get_name(person), self->student_id,
                          self->major ? self->major : "Undeclared", self->gpa);
}

void student_add_grade(Student *self, gint grade) {
    g_return_if_fail(IS_STUDENT(self));
    g_return_if_fail(grade >= 0 && grade <= 100);
    
    g_array_append_val(self->grades, grade);
    
    /* Recalculate GPA */
    self->gpa = student_calculate_gpa(self);
}

gdouble student_calculate_gpa(Student *self) {
    g_return_val_if_fail(IS_STUDENT(self), 0.0);
    
    if (self->grades->len == 0) {
        return 0.0;
    }
    
    gint total = 0;
    for (guint i = 0; i < self->grades->len; i++) {
        total += g_array_index(self->grades, gint, i);
    }
    
    return (gdouble)total / self->grades->len / 25.0; /* Convert to 4.0 scale */
}

gboolean student_is_honor_student(Student *self) {
    g_return_val_if_fail(IS_STUDENT(self), FALSE);
    return self->gpa >= 3.5;
}

void student_print_transcript(Student *self) {
    g_return_if_fail(IS_STUDENT(self));
    
    printf("\n--- Transcript for Student ID: %d ---\n", self->student_id);
    printf("Grades: ");
    for (guint i = 0; i < self->grades->len; i++) {
        printf("%d ", g_array_index(self->grades, gint, i));
    }
    printf("\nGPA: %.2f (%s)\n", self->gpa, 
           student_is_honor_student(self) ? "Honor Student" : "Regular Standing");
    printf("------------------------------------\n");
}

/* =============================================================================
 * Employee Class Implementation - Parallel Inheritance
 * ============================================================================= */

struct _Employee {
    Person parent_instance;
    gint employee_id;
    gchar *department;
    gdouble salary;
    GDateTime *hire_date;
};

G_DEFINE_TYPE(Employee, employee, TYPE_PERSON)

static void employee_finalize(GObject *object) {
    Employee *self = (Employee*)object;
    
    printf("[Memory] Finalizing Employee ID: %d\n", self->employee_id);
    
    g_free(self->department);
    if (self->hire_date) {
        g_date_time_unref(self->hire_date);
    }
    
    G_OBJECT_CLASS(employee_parent_class)->finalize(object);
}

static void employee_class_init(EmployeeClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = employee_finalize;
}

static void employee_init(Employee *self) {
    self->employee_id = 0;
    self->department = NULL;
    self->salary = 0.0;
    self->hire_date = g_date_time_new_now_local();
    
    printf("[Object] Employee instance created\n");
}

Employee* employee_new(const gchar *name, gint age, const gchar *email,
                       gint employee_id, const gchar *department, gdouble salary) {
    Employee *employee = g_object_new(TYPE_EMPLOYEE,
                                     "name", name,
                                     "age", age,
                                     "email", email,
                                     NULL);
    
    employee->employee_id = employee_id;
    employee->department = g_strdup(department);
    employee->salary = salary;
    
    return employee;
}

void employee_introduce(Employee *self) {
    g_return_if_fail(IS_EMPLOYEE(self));
    
    Person *person = PERSON(self);
    printf("Hello, I'm %s from the %s department (Employee ID: %d).\n",
           person_get_name(person), 
           self->department ? self->department : "Unknown",
           self->employee_id);
}

gchar* employee_get_description(Employee *self) {
    g_return_val_if_fail(IS_EMPLOYEE(self), NULL);
    
    Person *person = PERSON(self);
    return g_strdup_printf("Employee: %s (ID: %d, Dept: %s, Salary: $%.2f)",
                          person_get_name(person), self->employee_id,
                          self->department ? self->department : "Unknown",
                          self->salary);
}

gdouble employee_get_annual_salary(Employee *self) {
    g_return_val_if_fail(IS_EMPLOYEE(self), 0.0);
    return self->salary;
}

gint employee_get_years_of_service(Employee *self) {
    g_return_val_if_fail(IS_EMPLOYEE(self), 0);
    
    if (!self->hire_date) {
        return 0;
    }
    
    GDateTime *now = g_date_time_new_now_local();
    GTimeSpan diff = g_date_time_difference(now, self->hire_date);
    gint years = (gint)(diff / G_TIME_SPAN_DAY / 365);
    
    g_date_time_unref(now);
    return years;
}

gboolean employee_is_senior(Employee *self) {
    g_return_val_if_fail(IS_EMPLOYEE(self), FALSE);
    return employee_get_years_of_service(self) >= 5;
}

/* =============================================================================
 * Educational Demonstration Functions
 * ============================================================================= */

void demonstrate_polymorphism(GPtrArray *people) {
    printf("\n=== Polymorphism Demonstration ===\n");
    
    for (guint i = 0; i < people->len; i++) {
        GObject *obj = g_ptr_array_index(people, i);
        
        printf("\n%d. Object Type: %s\n", i + 1, G_OBJECT_TYPE_NAME(obj));
        
        /* Runtime type checking and polymorphic behavior */
        if (IS_STUDENT(obj)) {
            Student *student = STUDENT(obj);
            student_introduce(student);
            gchar *desc = student_get_description(student);
            printf("   Description: %s\n", desc);
            g_free(desc);
        } else if (IS_EMPLOYEE(obj)) {
            Employee *employee = EMPLOYEE(obj);
            employee_introduce(employee);
            gchar *desc = employee_get_description(employee);
            printf("   Description: %s\n", desc);
            g_free(desc);
        } else if (IS_PERSON(obj)) {
            Person *person = PERSON(obj);
            person_introduce(person);
            gchar *desc = person_get_description(person);
            printf("   Description: %s\n", desc);
            g_free(desc);
        }
    }
}

void demonstrate_reference_counting(void) {
    printf("\n=== Reference Counting Demonstration ===\n");
    
    /* Create an object */
    Person *person = person_new("Reference Test", 25, "test@example.com");
    printf("Initial reference count: %u\n", G_OBJECT(person)->ref_count);
    
    /* Add reference */
    g_object_ref(person);
    printf("After g_object_ref(): %u\n", G_OBJECT(person)->ref_count);
    
    /* Add another reference */
    Person *person_ref2 = person;
    g_object_ref(person_ref2);
    printf("After second ref: %u\n", G_OBJECT(person)->ref_count);
    
    /* Release references */
    g_object_unref(person_ref2);
    printf("After first unref: %u\n", G_OBJECT(person)->ref_count);
    
    g_object_unref(person);
    printf("After second unref: %u\n", G_OBJECT(person)->ref_count);
    
    /* Final unref will trigger finalize */
    printf("Calling final unref (should trigger finalize):\n");
    g_object_unref(person);
}

void demonstrate_type_system(void) {
    printf("\n=== Type System Demonstration ===\n");
    
    Student *student = student_new("Alice Johnson", 20, "alice@university.edu", 12345, "Computer Science");
    
    /* Type information */
    printf("Object type name: %s\n", G_OBJECT_TYPE_NAME(student));
    printf("Object type ID: %lu\n", G_OBJECT_TYPE(student));
    
    /* Type checking */
    printf("Is Student? %s\n", IS_STUDENT(student) ? "Yes" : "No");
    printf("Is Person? %s\n", IS_PERSON(student) ? "Yes" : "No");
    printf("Is GObject? %s\n", G_IS_OBJECT(student) ? "Yes" : "No");
    
    /* Safe casting */
    Person *as_person = PERSON(student);
    printf("Cast to Person successful: %s\n", as_person ? "Yes" : "No");
    
    /* Property system demonstration */
    printf("\nProperty System:\n");
    gchar *name;
    gint age;
    gint student_id;
    
    g_object_get(student,
                 "name", &name,
                 "age", &age,
                 "student-id", &student_id,
                 NULL);
    
    printf("Properties via g_object_get: %s, %d years, ID: %d\n", name, age, student_id);
    g_free(name);
    
    /* Modify properties */
    g_object_set(student, "gpa", 3.8, NULL);
    printf("GPA set to 3.8 via property system\n");
    
    g_object_unref(student);
}

void test_gobject_basics(void) {
    printf("\n=== GObject Educational Demonstration ===\n");
    printf("Learning Objectives:\n");
    printf("- Object-oriented programming in C\n");
    printf("- Inheritance and polymorphism\n");
    printf("- Reference counting and memory management\n");
    printf("- Runtime type information and introspection\n\n");
    
    /* Create various objects */
    printf("1. Creating objects with inheritance hierarchy:\n");
    Person *person = person_new("John Doe", 35, "john@example.com");
    Student *student = student_new("Alice Smith", 20, "alice@university.edu", 12345, "Computer Science");
    Employee *employee = employee_new("Bob Johnson", 30, "bob@company.com", 67890, "Engineering", 75000.0);
    
    /* Add some grades to student */
    student_add_grade(student, 85);
    student_add_grade(student, 92);
    student_add_grade(student, 78);
    student_add_grade(student, 88);
    
    /* Create array for polymorphism demo */
    GPtrArray *people = g_ptr_array_new();
    g_ptr_array_add(people, person);
    g_ptr_array_add(people, student);
    g_ptr_array_add(people, employee);
    
    /* Run demonstrations */
    demonstrate_polymorphism(people);
    demonstrate_type_system();
    demonstrate_reference_counting();
    
    /* Student-specific operations */
    printf("\n=== Student-Specific Operations ===\n");
    student_print_transcript(student);
    
    /* Employee-specific operations */
    printf("\n=== Employee-Specific Operations ===\n");
    printf("Annual salary: $%.2f\n", employee_get_annual_salary(employee));
    printf("Years of service: %d\n", employee_get_years_of_service(employee));
    printf("Senior employee: %s\n", employee_is_senior(employee) ? "Yes" : "No");
    
    /* Cleanup */
    printf("\n=== Cleanup (Reference counting in action) ===\n");
    g_ptr_array_free(people, TRUE);
    g_object_unref(person);
    g_object_unref(student);
    g_object_unref(employee);
    
    printf("\nGObject demonstration completed!\n");
}
