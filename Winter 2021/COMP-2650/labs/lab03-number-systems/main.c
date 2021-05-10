#include <stdio.h>

int get_int(int, int);
void read_byte(const char[], int[]);
void byte_print(int[]);
void func_and(int[], int[], int[]);
void func_or(int[], int[], int[]);
void func_not(int[], int[]);
void func_1s_comp(int[], int[]);
void func_2s_comp(int[], int[]);
void func_2s_comp_star(int[], int[]);

int main(void) {
	puts("Please select a command:\n"
		"\t0) Exit\n"
		"\t1) AND\n"
		"\t2) OR\n"
		"\t3) NOT\n"
		"\t4) 1’s complement\n"
		"\t5) 2’s complement\n"
		"\t6) 2’s complement*\n");

	int option = get_int(0, 6);
	if (!option) return 0; // exit

	int byteA[8] = { 0 };
	int byteB[8] = { 0 };
	int resul[8] = { 0 };

	// input switch
	switch (option) {
		case 1:
		case 2:
			read_byte("Please enter the first byte:", byteA);
			read_byte("Please enter the second byte:", byteB);
			break;

		default:
			read_byte("Please enter a byte:", byteA);
			break;
	}

	// operation switch
	switch (option) {
		case 1:
			func_and(byteA, byteB, resul);
			break;
		case 2:
			func_or(byteA, byteB, resul);
			break;
		case 3:
			func_not(byteA, resul);
			break;
		case 4:
			func_1s_comp(byteA, resul);
			break;
		case 5:
			func_2s_comp(byteA, resul);
			break;
		case 6:
			func_2s_comp_star(byteA, resul);
			break;
	}

	// output switch
	switch (option) {
		case 1:
		case 2:
			byte_print(byteA);
			printf((option - 1) ? " OR " : " AND ");
			byte_print(byteB);
			printf(" = ");
			byte_print(resul);
			puts("");
			break;

		case 3:
		case 4:
		case 5:
		case 6: {
			char* ops[] = {
				"NOT",
				"1\'S COMPLEMENT of",
				"2\'S COMPLEMENT of",
				"2\'S COMPLEMENT* of"
			};
			printf("%s ", ops[option - 3]);
			byte_print(byteA);
			printf(" = ");
			byte_print(resul);
			puts("");
			break;
		}
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
 * Reads 8 bits into the out array. Unspecified Behaviour may occur if
 * there are less than 8 slots in the out array.
 */
void read_byte(const char prompt[], int out[]) {
	puts(prompt);

	for (int i = 0; i < 8; i++) {
		printf("%d: ", i + 1); // offset by one because readability counts
		out[i] = get_int(0, 1);
	}
}

/**
 * Prints a byte's integers sequentially ({1, 0, 1, 0} -> 1010). Unspecified
 * Behaviour may occur if there are less than 8 slots in the byte array.
 */
void byte_print(int byte[]) {
	for (int i = 0; i < 8; i++)
		printf("%d", byte[i]);
}

/**
 * Takes two bytes (length-8 int arrays of 0s or 1s) and applies
 * the bitwise AND operation on them. Stores the result in out.
 * Unspecified Behaviour may occur if there are less than 8 slots
 * in any of the arrays.
 */
void func_and(int a[], int b[], int out[]) {
	for (int i = 0; i < 8; i++)
		out[i] = a[i] && b[i];
}

/**
 * Takes two bytes and applies the bitwise OR operation on them. Stores
 * the result in out. Unspecified Behaviour may occur if there are less
 * than 8 slots in any of the arrays.
 */
void func_or(int a[], int b[], int out[]) {
	for (int i = 0; i < 8; i++)
		out[i] = a[i] || b[i];
}

/**
 * Takes a byte and applies the logical NOT operation on it. Stores the
 * result in out. Unspecified Behaviour may occur if there are less than
 * 8 slots in either array.
 */
void func_not(int a[], int out[]) {
	for (int i = 0; i < 8; i++)
		out[i] = !a[i];
}

/**
 * Takes a byte and stores the 1's complement in the out array. Unspecified
 * Behaviour may occur if there are less than 8 slots in either array.
 */
void func_1s_comp(int a[], int out[]) {
	func_not(a, out);
}

/**
 * Takes a byte and stores the 2's complement in the out array. Unspecified
 * Behaviour may occur if there are less than 8 slots in either array.
 */
void func_2s_comp(int a[], int out[]) {
	func_1s_comp(a, out);

	int carry = 1;
	for (int i = 7; i >= 0; i--) {
		out[i] += carry;
		carry = !(out[i] %= 2); // sets the carry

		if (!carry) break; // stop when there is nothing to carry
	}
}

/**
 * Uses an alternate algorithm to calculate the 2's complement of a provided byte.
 * Stores the result in out. Unspecifed behaviour may occur if there are less
 * than 8 slots in either array.
 */
void func_2s_comp_star(int a[], int out[]) {
	int not = 0;
	for (int i = 7; 0 <= i; i--) {
		out[i] = not ? !a[i] : a[i];
		not = not || a[i]; // will flip to 1 once a 1 is encountered
	}
}