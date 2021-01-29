#include <stdio.h>

int main(void) {

	// allocate 2 numbers in memory
	int a = 0;
	int b = 0;

	printf ("Input two numbers (the second non-zero):\n");

	// read a and b
	scanf (" %d", &a);

	do {
		// division by 0 is impossible, so prevent the user from inputting 0.
		scanf(" %d", &b);
	} while (b == 0);

	int quotient = a / b;
	int remainder = a % b;

	printf ("The result of %d / %d = %d r. %d\n", a, b, quotient, remainder);

	return 0;
	
}