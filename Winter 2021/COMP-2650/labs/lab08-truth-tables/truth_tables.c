#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/fast_math.h"
#include "lib/input.h"
#include "lib/console_colouring.h"
#include "truth_tables.h"

/**
 * Increments the binary number represented by the passed array.
 * Assumes the array represents an unsigned  binary number of
 * length len.
 */
void func_increment(int len, short number[]) {
	int car = 1;
	for (len -= 1; len >= 0; len--) {
		number[len] = number[len] + car;
		car = number[len] > 1;
		number[len] %= 2;

		if (!car) return;
	}
}

/**
 * Constructs the left side of a truth table and stores
 * the result in the the short array. Assumes the array
 * is large enough to store all 2^var_cnt * var_cnt numbers.
 *
 * To access, use the formula:
 * v
 */
void build_left_side(int var_cnt, short out[]) {
	long n_rows = fast_pow_2_l(var_cnt);

	short num[var_cnt];
	memset(num, 0, sizeof(short) * var_cnt);

	for (int i = 0; i < n_rows; i++) {
		memcpy(out + i * var_cnt, num, sizeof(short) * var_cnt);
		func_increment(var_cnt, num);
	}
}

/**
 * Gets the desired output of a function and returns its values
 * in the short array. Assumes the array is large enough to store
 * all 2^var_cnt * func_cnt numbers.
 *
 * To access, use the formula:
 * func_cnt*row + val
 * where row is the row of the truth table and val is the function you're after
 */
void build_right_side(int var_cnt, int func_cnt, short out[]) {
	long n_rows = fast_pow_2_l(var_cnt);
	for (int x = 0; x < func_cnt; x++) { // function
		for (long i = 0; i < n_rows; i++) { // variable
			printf(RED "Output for row %ld of F%d: " RESET, i, x);
			out[(i * func_cnt) + x] = get_short(0, 1);
		}
	}
}
