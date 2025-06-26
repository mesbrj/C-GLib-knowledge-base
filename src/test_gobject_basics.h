#ifndef TEST_GOBJECT_BASICS_H
#define TEST_GOBJECT_BASICS_H

#include <glib-object.h>

G_BEGIN_DECLS

/* =============================================================================
 * Educational GObject Demonstration
 * 
 * This module demonstrates fundamental GObject concepts:
 * - Object-oriented programming in C
 * - Inheritance and polymorphism
 * - Type system and runtime type checking
 * - Reference counting and memory management
 * ============================================================================= */

/* =============================================================================
 * Person Class - Base class demonstrating basic GObject concepts
 * ============================================================================= */

#define TYPE_PERSON (person_get_type())
#define PERSON(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_PERSON, Person))
#define IS_PERSON(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_PERSON))
G_DECLARE_FINAL_TYPE(Person, person, , PERSON, GObject)

/* Person public API */
Person* person_new(const gchar *name, gint age, const gchar *email);
Person* person_new_with_properties(const gchar *name, gint age, const gchar *email);

/* Methods demonstrating virtual function patterns */
void person_introduce(Person *self);
gchar* person_get_description(Person *self);
gboolean person_is_adult(Person *self);

/* Property accessors - demonstrate encapsulation */
const gchar* person_get_name(Person *self);
void person_set_name(Person *self, const gchar *name);
gint person_get_age(Person *self);
void person_set_age(Person *self, gint age);

/* =============================================================================
 * Student Class - Derived class demonstrating inheritance
 * ============================================================================= */

#define TYPE_STUDENT (student_get_type())
#define STUDENT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_STUDENT, Student))
#define IS_STUDENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_STUDENT))
G_DECLARE_FINAL_TYPE(Student, student, , STUDENT, Person)

/* Student public API */
Student* student_new(const gchar *name, gint age, const gchar *email, 
                     gint student_id, const gchar *major);

/* Extended methods demonstrating method overriding */
void student_introduce(Student *self);  /* Overrides person_introduce */
gchar* student_get_description(Student *self);  /* Overrides person_get_description */

/* Student-specific methods */
void student_add_grade(Student *self, gint grade);
gdouble student_calculate_gpa(Student *self);
gboolean student_is_honor_student(Student *self);
void student_print_transcript(Student *self);

/* =============================================================================
 * Employee Class - Another derived class demonstrating polymorphism
 * ============================================================================= */

#define TYPE_EMPLOYEE (employee_get_type())
#define EMPLOYEE(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_EMPLOYEE, Employee))
#define IS_EMPLOYEE(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_EMPLOYEE))
G_DECLARE_FINAL_TYPE(Employee, employee, , EMPLOYEE, Person)

/* Employee public API */
Employee* employee_new(const gchar *name, gint age, const gchar *email,
                       gint employee_id, const gchar *department, gdouble salary);

/* Polymorphic methods */
void employee_introduce(Employee *self);
gchar* employee_get_description(Employee *self);

/* Employee-specific methods */
gdouble employee_get_annual_salary(Employee *self);
gint employee_get_years_of_service(Employee *self);
gboolean employee_is_senior(Employee *self);

/* =============================================================================
 * Utility Functions for Educational Demonstrations
 * ============================================================================= */

/**
 * Demonstrates runtime type checking and polymorphism
 */
void demonstrate_polymorphism(GPtrArray *people);

/**
 * Shows reference counting and memory management
 */
void demonstrate_reference_counting(void);

/**
 * Demonstrates type checking and casting
 */
void demonstrate_type_system(void);

/**
 * Main demonstration function
 */
void test_gobject_basics(void);

G_END_DECLS

#endif /* TEST_GOBJECT_BASICS_H */
