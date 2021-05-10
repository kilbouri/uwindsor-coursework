/**
 * GCC Compile and Run command:
 * gcc -Wall main.c conversion.c complement.c logic.c -lm -o main && ./main
 */

#include <stdio.h>

#define MAX 8

#include "logic.h"
#include "complement.h"
#include "conversion.h"

int get_int(int, int);
void read_bits(const char*, int[]);
void byte_print(int[], char[]);

int main(void) {

	while (1) {
		// main menu
		puts("Enter the command number:");
		puts("  0) Exit");
		puts("  1) AND");
		puts("  2) OR");
		puts("  3) NOT");
		puts("  4) 1’s complement");
		puts("  5) 2’s complement");
		puts("  6) 2’s complement*");
		int selected = get_int(0, 6);
		if (!selected) return 0;

		int first[MAX];
		int second[MAX];
		int result[MAX];

		// input switch
		switch (selected) {
			case 1:
			case 2:
				read_bits("Enter the first binary number:", first);
				read_bits("Enter the second binary number:", second);
				break;

			default:
				read_bits("Enter a binary number:", first);
				break;
		}

		// operation switch
		switch (selected) {
			case 1:
				func_and(first, second, result);
				break;
			case 2:
				func_or(first, second, result);
				break;
			case 3:
				func_not(first, result);
				break;
			case 4:
				func_1s_comp(first, result);
				break;
			case 5:
				func_2s_comp(first, result);
				break;
			case 6:
				func_2s_comp_star(first, result);
				break;
		}

		puts("Enter the output base:");
		puts("  1) Binary");
		puts("  2) Octal");
		puts("  3) Decimal");
		puts("  4) Hexadecimal");
		int base = get_int(1, 4);

		printf("Result: ");
		switch (base) {
			case 1:
				to_binary(result);
				break;
			case 2:
				to_octal(result);
				break;
			case 3:
				to_decimal(result);
				break;
			case 4:
				to_hexadecimal(result);
				break;
		}
		puts("\n======================");
	}
}

/**
 * Gets an integer in the range [START, END].
 */
int get_int(int START, int END) {
	int input;
	while (1) {
		scanf("%d", &input);

		if (START <= input && input <= END) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
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