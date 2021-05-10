/* ========================================
 * COMP-1410 Lab 4
 * ----------------------------------------
 * Student name:            Isaac Kilbourne
 * External Sources:        None
 * ========================================
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

char* select_min(char[]);
void str_sort(char[]);

#define STR_TEST_COUNT 5

int main(void) {

	assert('A' == *select_min("abcABC"));   // The function should return 'A' as capital letters
	assert('A' == *select_min("ABCabc"));   // are stored before lowercase letters in ASCII.
	assert('\0' == *select_min(""));        // Empty strings should give back the null character
	puts("[PASS] select_min()");

	// shorter (and more expandable) to assemble the test strings into an array of test and expected values.
	// testStrings[a][b][c] -> a = test #, b = 0 (input) or 1 (test), c = specific character index
	char testStrings[STR_TEST_COUNT][2][7] = {
		{"ethics", "cehist"},
		{"ABCdef", "ABCdef"},
		{"fedBAC", "ABCdef"},
		{"expand", "adenpx"},
		{"", ""}
	};

	for (int i = 0; i < STR_TEST_COUNT; i++) {
		str_sort(testStrings[i][0]); // sort the i'th test string
		assert(!strcmp(testStrings[i][0], testStrings[i][1])); // compare sorted and expected values
	}
	puts("[PASS] str_sort()");
}

/**
 * Returns the pointer to the character with the lowest ASCII value in the string.
 * Requires: str be null-terminated.
 */
char* select_min(char str[]) {
	char* current = str;    // keeps track of the position in the string
	char* lowest = current; // keeps track of the pointer of lowest ASCII value

	// traverses the string, setting lowest to the address with lowest value
	for (; *current != '\0'; current++)
		if (*current < *lowest)
			lowest = current;

	return lowest;
}

/**
 * Sorts the characters in a string into ascending order by ASCII value. 
 * Uses O(n^2) time and O(n) selections. Gross.
 * Requires: str points to a null-terminated string which can be modified.
 */
void str_sort(char str[]) {
	char* unsorted = str; // keeps track of the first unsorted value in the string
	for (; *unsorted != '\0'; unsorted++) {
		char* lowest = select_min(unsorted);

		char tmp = *lowest; // char is too small to do in-place swapping for most inputs
		*lowest = *unsorted;
		*unsorted = tmp;
	}
}