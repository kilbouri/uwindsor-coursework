/* ===========================================================================
COMP-1410 Lab 1: Iteration and Recursion
==============================================================================
Student name: Isaac Kilbourne

Cite any other sources of outside help
(e.g., websites, other students):
None, that's why my code is so ugly 🤣
=========================================================================== */

#include <stdio.h>
#include <assert.h>

int digit_sum_iterative(int);
int digit_sum_recursive(int);

int main(void) {
	assert(!digit_sum_iterative(0)); 				// test case: iterative 0
	assert(!digit_sum_iterative(-5));				// test case: iterative with negative
	assert(!digit_sum_iterative(1000000000)); 	// test case: iterative 1e9
	assert(digit_sum_iterative(5) == 5); 			// test case: iterative 9999
	assert(digit_sum_iterative(1234) == 10);		// test case: iterative 1234
	puts("[PASS] digit_sum_iterative(n)");

	assert(!digit_sum_recursive(0)); 				// test case: recursive 0
	assert(!digit_sum_recursive(-5));				// test case: recursive with negative
	assert(!digit_sum_recursive(1000000000)); 	// test case: recursive 1e9
	assert(digit_sum_recursive(5) == 5); 			// test case: recursive 9999
	assert(digit_sum_recursive(1234) == 10);		// test case: recursive 1234
	puts("[PASS] digit_sum_recursive(n)");
}

/**
 * Iterative implementation of digit_sum(n), which returns the decimal sum of
 * the digits in n. Requires 0 <= n < 1e9
 */
int digit_sum_iterative(int n) {
	if (n <= 0 || n > 999999999) return 0;

	int sum = 0;
	for (; n > 0; n /= 10)
		sum += n % 10;

	return sum;
}

/**
 * Recursive implementation of digit_sum(n), which returns the decimal sum of
 * the digits in n. Requires 0 <= n <= 1e9
 */
int digit_sum_recursive(int n) {
	if (n <= 0 || n > 999999999) return 0;
	return n % 10 + digit_sum_recursive(n / 10);
}