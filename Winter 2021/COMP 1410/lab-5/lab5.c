/* ========================================
 * COMP-1410 Lab 5
 * ----------------------------------------
 * Name:                    Isaac Kilbourne
 * External Sources:        None
 * ========================================
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

struct student {
	int id;
	char name[20];
};

bool find_id(int, struct student[], int, char*);
int find_name(char*, struct student[], int, int[]);
void change_name(struct student*, char*);
bool arr_cmp(int[], int[], int);

int main(void) {
	struct student students[] = {
		{   1234567, "Alice" },
		{   1234568, "Alice" },
		{ 110043640, "Isaac" },
		{   3141593, "Bob"   },
		{         0, ""      }
	};

	char found[20];
	assert(find_id(1234567, students, 5, found));
	assert(!strcmp(found, "Alice"));
	assert(find_id(0, students, 5, found));
	assert(!strcmp(found, ""));
	assert(!find_id(1234569, students, 5, found));
	assert(!strcmp(found, "")); // string should NOT have changed
	puts("[PASS] find_id()");

	int ids[2];
	assert(find_name("Alice", students, 5, ids));
	assert(arr_cmp(ids, (int[]) { 1234567, 1234568 }, 2));
	assert(!find_name("Bill", students, 5, ids));
	assert(arr_cmp(ids, (int[]) { 1234567, 1234568 }, 2)); // ids should NOT have changed
	puts("[PASS] find_name()");

	change_name(students, "Gary The Snail");
	assert(!strcmp(students[0].name, "Gary The Snail"));
	change_name(students + 1, "Please give me 100 on this lab");
	assert(!strcmp(students[1].name, "Please give me 100 "));
	puts("[PASS] change_name()");
}

/**
 * Searches for a student with the given ID in the provided array of students.
 * Returns true if such a studen is found, and found_name is updated to hold the
 * students name. Otherwise returns false.
 *
 * Requires: arr has length n, students in arr have unique ids, found_name points
 *           to enough memory (at least 20 * sizeof(char)) to hold the name
 */
bool find_id(int id, struct student arr[], int len, char* found_name) {
	for (struct student* curr = arr; curr < (arr + len); curr++) {
		if (curr->id == id) {
			found_name = strncpy(found_name, curr->name, 19);
			return true;
		}
	}
	return false;
}

/**
 * Searches for student(s) with the given name in arr, returns the number of students
 * found and the array ids is updated to contain the id numbers of those students.
 *
 * Requires: arr has length n, students in arr have unique ids, ids points to enough
 *           memory to hold the found student ids.
 */
int find_name(char* name, struct student arr[], int n, int ids[]) {
	int n_found = 0;
	for (struct student* curr = arr; curr < (arr + n); curr++)
		if (!strcmp(name, curr->name))
			ids[n_found++] = curr->id;

	return n_found;
}

/**
 * Renames the student s to have the name given in new_name
 *
 * Requires: s points to a valid student that can be modified
 */
void change_name(struct student* s, char* new_name) {
	// strncpy makes 19+ character names 19 characters so they don't 
	// overflow the allocated memory
	strncpy(s->name, new_name, 19);
}

/**
 * Compares two integer arrays of length n
 */
bool arr_cmp(int a[], int b[], int n) {
	for (int* curr = a; curr < (a + n); curr++)
		if (*curr != b[curr - a]) return false;
	return true;
}
