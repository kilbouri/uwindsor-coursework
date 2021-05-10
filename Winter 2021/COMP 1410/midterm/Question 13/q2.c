/**
 * Author: Isaac Kilbourne
 * File Name: q2.c
 * Description: solution to Winter 20201 COMP1410 midterm question 13
 * Date/Time: 12:19pm, Friday February 12, 2021
 */

#include <stdio.h>
#include <assert.h>

int count_ones(int n);

int main(void) {
	assert(count_ones(-111) == 3);
	assert(count_ones(1231) == 2);
	assert(count_ones(1) == 1);
	assert(count_ones(234567890) == 0);
	puts("[PASS] count_ones()");
}

/**
 * Counts the 1s in a provided number n. If
 * n < 0, the absolute value will be used
 * instead.
 */
int count_ones(int n) {
	// oneliner for abs()
	n = (n < 0) ? -n : n;

	// base case
	if (n == 0) return 0;

	// recursive case
	return count_ones(n / 10) + (n % 10 == 1);
}

/**
 * My implentation works by first taking the absolute value of the input,
 * as the modulo operator doesn't correctly take the last digit when
 * the operand is negative.
 * 
 * Then, if n is 0 it simply returns 0, there are no ones in the number 0;
 * Finally, the recursive case returns the number of 1s in n/10, plus one
 * if and only if the last digit in this call was a 1 as well.
 */