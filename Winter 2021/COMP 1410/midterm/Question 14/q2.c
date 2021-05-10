/**
 * Author: Isaac Kilbourne
 * File Name: q2.c
 * Description: solution to Winter 20201 COMP1410 midterm question 14
 * Date/Time: 12:46pm, Friday February 12, 2021
 */

#include <stdio.h>
#include <assert.h>

void row_sums(int n, int m, int matrix[][10], int sums[]);
void arr_print(int len, int* arr);

int main(void) {
	int test_arr[][10] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	int sums[3] = { 0 };
	row_sums(3, 3, test_arr, sums);

	// pretty print stuff, don't worry about it lol
	arr_print(3, test_arr[0]);
	printf("\n");
	
	arr_print(3, test_arr[1]);
	printf("  ->  ");
	arr_print(3, sums);
	printf("\n");

	arr_print(3, test_arr[2]);
	printf("\n");
}

/**
 * First implementation: Uses a nested for loop to iterate over the
 * matrix between n and m.
 * Note: m is the number of columns, and n is the number of rows.
 */
void row_sums(int n, int m, int matrix[][10], int sums[]) {
	for (int row = 0; row < n; row++) {
		sums[row] = 0; // ensure each row's sum starts at 0
		for (int col = 0; col < m; col++) {
			sums[row] += matrix[row][col];
		}
	}
}

/**
 * Helper function for pretty-printing a 1-D array to the console
 */
void arr_print(int len, int* arr) {
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%d ", *(arr + i));
	}
	printf("\b]"); // replaces the last space with a closing bracket
}

/**
 * My implementation of row_sums() simply uses a basic 2D
 * array traversal algorithm, in row-major form, to place
 * the row's sum into the sums array.
 * 
 * The arr_print() function prints an openning square bracket,
 * then each index of the array followed by a space. Once all
 * indices have been printed, the backspace character followed
 * by a square bracket overwrites the extra space caused by the
 * index print loop to be replaced with a closing square bracket.
 * 
 * Example: {1, 2, 3} (_ indicates whitespace)
 * [
 * [1_
 * [1_2_
 * [1_2_3_
 * [1_2_3]
 */