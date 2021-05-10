/* ===========================================================================
COMP-1410 Lab 3
==============================================================================
Student name: Isaac Kilbourne

Cite any other sources of outside help
(e.g., websites, other students):
None
=========================================================================== */

#include <stdio.h>
#include <assert.h>

void matrix_add(const int, const int[][3], const int[][3], int[][3]);
int matrix_equals(const int, int[][3], int[][3]);
void negate_column(const int, const int, int[][3]);
void negate_row(const int, const int, int*);

int main(void) {
	int a[3][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8} };
	int b[3][3] = { {0, -1, -2}, {-3, -4, -5}, {-6, -7, -8} };
	int c[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	int d[3][3] = { {0, 1, 2}, {-3, -4, -5}, {6, 7, 8} };
	int e[3][3] = { {0, -1, 2}, {-3, 4, -5}, {6, -7, 8} };
	int o[3][3] = { {0} }; // the same as c

	assert(!matrix_equals(3, a, b));	// test case: unequal matrices
	assert(matrix_equals(3, c, o));		// test case: equal matrices
	puts("[PASS] matrix_equals()");

	matrix_add(3, a, b, o);
	assert(matrix_equals(3, o, c));		// test case: a + b == c

	matrix_add(3, a, c, o);
	assert(matrix_equals(3, o, a));		// test case: a + c == a
	puts("[PASS] matrix_add()");

	// e is d with the center column negated
	negate_column(3, 1, e);
	assert(matrix_equals(3, d, e));
	puts("[PASS] negate_column()");

	// b is d with the first and third rows negated
	negate_row(3, 0, *b);
	negate_row(3, 2, *b);
	assert(matrix_equals(3, b, d));
	puts("[PASS] negate_row()");

}

/**
 * Computes the sum of two n x 3 matrices A and B, storing the result in C.
 * Undefined behaviour may occur if any input is smaller than n x 3.
 * Requires 0 < n
 */
void matrix_add(const int n, const int A[][3], const int B[][3], int C[][3]) {
	for (int row = 0; row < n; row++)
		for (int col = 0; col < 3; col++)
			C[row][col] = A[row][col] + B[row][col];
}

/**
 * Determines whether the n x 3 matrices A and B are equal.
 * Undefined behaviour may occur if A or B are not n x 3.
 * Requires: 0 < n
 */
int matrix_equals(const int n, int A[][3], int B[][3]) {
	for (int row = 0; row < n; row++)
		for (int col = 0; col < 3; col++)
			if (A[row][col] != B[row][col])
				return 0;

	return 1;
}

/**
 * Negates the values in the c'th column of A.
 * Requires 0 < n and 0 <= c < 3
 */
void negate_column(const int n, const int c, int A[][3]) {
	for (int r = 0; r < n; r++)
		A[r][c] *= -1;
}

/**
 * Negates the values in the r'th row of A.
 * Requires 0 < n and 0 <= r < n
 * 			A points to the (0, 0) element of an n x 3 matrix
 */
void negate_row(const int n, const int r, int* A) {
	for (int c = 0; c < 3; c++)
		A[(r * 3) + c] *= -1;
}