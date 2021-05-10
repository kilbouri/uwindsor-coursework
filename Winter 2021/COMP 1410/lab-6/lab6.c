/* ========================================
 * COMP-1410 Lab 6
 * ----------------------------------------
 * Name:                    Isaac Kilbourne
 * External Sources:        None
 * ========================================
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

 // Definition of structure for storing student information
struct student {
	int id;
	char* name;
};

struct student* create_student(int, char*);
void free_student(struct student*);
bool change_name(struct student*, char*);
bool check_student(struct student*, int, char*);

int main(void) {
	// =============== create_student() ===============

	struct student* s = create_student(123456789, "Richard");
	assert(check_student(s, 123456789, "Richard"));

	struct student* s1 = create_student(110043640, "Isaac");
	assert(check_student(s1, 110043640, "Isaac"));

	struct student* s2 = create_student(0, "Abbie");
	assert(check_student(s2, 0, "Abbie"));
	puts("[PASS] create_student()");

	// =============== change_name() ===============

	assert(change_name(s, "Dick"));
	assert(check_student(s, 123456789, "Dick"));

	assert(change_name(s1, "Randall"));
	assert(check_student(s1, 110043640, "Randall"));

	assert(change_name(s2, "Abs"));
	assert(check_student(s2, 0, "Abs"));
	puts("[PASS] change_name()");

	// =============== free_student() ===============

	free_student(s);
	free_student(s1);
	free_student(s2);
	puts("[PASS] free_student()");

}

/**
 * Creates a new student record with the given ID and name;
 * Allocates memory to store structure and name. Caller must free.
 *
 * Requires: name is a valid string
 */
struct student* create_student(int id, char* name) {
	struct student* new_student;
	new_student = (struct student*)malloc(sizeof(struct student));
	assert(new_student != NULL);

	// copy the string (which may be a literal) into a real memory location
	char* student_name = calloc(strlen(name) + 1, sizeof(char));
	assert(student_name != NULL);
	strcpy(student_name, name);

	new_student->id = id;
	new_student->name = student_name;

	return new_student;
}

/**
 * Frees the student at the pointer passed.
 *
 * Requires student point to a dynamically allocated student.
 */
void free_student(struct student* student) {
	free(student->name);
	free(student);
}

/**
 * Renames the student to have the name given. Caller must free.
 *
 * Returns: true if the name was changed, false otherwise.
 * Requires: student points to a valid student
 *           new_name is a valid string
 */
bool change_name(struct student* student, char* new_name) {
	int len = strlen(new_name) + 1;
	char* new = calloc(len, sizeof(char));

	if (new == NULL) return false;

	// clear the students old name then set it to the new one
	free(student->name);
	strcpy(new, new_name);
	student->name = new;

	return true;
}

/**
 * Utility for asserting student
 */
bool check_student(struct student* s, int expected_id, char* expected_name) {
	bool name = !strcmp(s->name, expected_name);
	bool id = s->id == expected_id;

	return name && id;
}
