/* ===========================================================================
COMP-1410 Lab 2
==============================================================================
Student name: Isaac Kilbourne

Cite any other sources of outside help
(e.g., websites, other students):

None!
=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

bool order(int*, int*);
void swap_pointers(int**, int**);

int main(void) {

	int a = 5, b = 5;
	assert(!order(&a, &b));	//
	assert(a == 5);			// test case: a = b
	assert(b == 5);			//

	a = 0, b = 5;
	assert(!order(&a, &b));	//
	assert(a == 0);			// test case: no swap needed
	assert(b == 5);			//

	a = 5, b = 0;
	assert(order(&a, &b));	// 
	assert(a == 0);			// test case: swap needed
	assert(b == 5);			// 
	puts("[PASS] order(int*, int*)");

	int* ptr_first = &a;
	int* ptr_second = &b;
	swap_pointers(&ptr_first, &ptr_second);	//
	assert(ptr_second == &a);				//
	assert(ptr_first == &b);				// test case: swap two pointers
	assert(*ptr_second == a);				//
	assert(*ptr_first == b);				//
	puts("[PASS] swap_pointers(int**, int**)");
}

/**
 * order(a, b) sorts the values pointed to by a and b. 
 * returns whether or not the values were swapped. 
 */
bool order(int* a, int* b) {
	if (*b < *a) {
		// high-efficiency value swap
		*a += *b;
		*b = *a - *b;
		*a = *a - *b;
		
		return true;
	}
	return false;
}

/**
 * Swaps the addresses stored in a and b.
 */
void swap_pointers(int** a, int** b) {
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}