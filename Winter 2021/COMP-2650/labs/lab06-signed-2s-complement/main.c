/**
 * GCC Compile and Run command:
 * gcc -Wall main.c conversion.c complement.c logic.c -lm -o main && ./main
 */

#include <stdio.h>
#include <assert.h>

#define MAX 8

#include "conversion.h"
#include "arithmetic.h"

int get_int(int, int);
void read_bits(const char*, int[]);
void byte_print(int[], char[]);

/* Terminal coloring */
#ifndef __unix__
#define SUCCESS ""
#define ERROR   ""				// Standard ANSI color codes don't work, so
#define OPTION  ""				// just define empty strings.
#define RESET   ""

#else
#define SUCCESS	"\033[0;32m"	// green for outputs
#define ERROR	"\033[1;31m"	// red for invalid inputs
#define OPTION  "\033[0;36m"	// blue for options	
#define RESET	"\033[0m"		// RESET to default
#endif

int main(void) {
	while (1) {
		// main menu
		puts("Enter the command number:");
		puts(OPTION "  0) Exit" RESET);
		puts(OPTION "  1) Addition in Signed 2s" RESET);
		puts(OPTION "  2) Subtraction in Signed 2s" RESET);
		int selected = get_int(0, 2);
		if (!selected) return 0;

		int first[MAX];
		int second[MAX];
		int result[MAX];

		read_bits("Enter the first binary number:", first);
		read_bits("Enter the second binary number:", second);

		int overflowed;
		switch (selected) {
			case 1:
				overflowed = func_signed_2s_addition(first, second, result);
				break;
			case 2:
				overflowed = func_signed_2s_subtraction(first, second, result);
				break;
		}

		puts("Enter the output base:");
		puts(OPTION "  1) Binary" RESET);
		puts(OPTION "  2) Octal" RESET);
		puts(OPTION "  3) Decimal" RESET);
		puts(OPTION "  4) Hexadecimal" RESET);
		int base = get_int(1, 4);

		if (overflowed) printf(ERROR "(Under/Over)flow has occurred in the calculation!\n" RESET);

		printf(SUCCESS "Result: ");
		switch (base) {
			case 1:
				to_binary(result);
				break;
			case 2:
				to_octal(result, 1);
				break;
			case 3:
				to_decimal(result, 1);
				break;
			case 4:
				to_hexadecimal(result, 1);
				break;
		}
		puts(RESET "\n======================");
	}
}

/**
 * Gets an integer in the range [START, END].
 */
int get_int(int START, int END) {
	int input;
	while (1) {
		scanf("%d", &input);
		while (getchar() != '\n'); // clears STD_IN

		if (START <= input && input <= END) return input;

		printf("Invalid, please try again: ");
	}
}

/**
 * Reads [MAX] bits into the out array. Unspecified Behaviour may occur
 * if there are less than [MAX] slots in the out array.
 */
void read_bits(const char prompt[], int out[]) {
	puts(prompt);

	for (int i = 0; i < MAX; i++) {
		printf("%d: ", i + 1); // offset by one because readability counts
		out[i] = get_int(0, 1);
	}
}