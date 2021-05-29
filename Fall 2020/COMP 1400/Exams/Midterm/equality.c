// Author: Isaac Kilbourne
// Name: Equality.c
// Date: Nov 14, 2020
#include <stdio.h>
#include <math.h>

// Given two numbers, decide whether they are "equal" or not, under the following
// rules for equality:
//     - same number of digits
//     - digits sum to the same number
// Repeat until the user enters 0 for "no".

// This question did not explicitly instruct how to handle negative signs. 
// I will consider them as making the first digit negative.
int main(void) {

	int operand1, operand2;
	int retry;

	while (retry) {

		// get two integers
		printf ("Input two integers: ");
		scanf ("%d %d", &operand1, &operand2);

		int absOperand1, absOperand2;

		// absolute both numbers
		absOperand1 = (operand1 < 0) ? -operand1 : operand1;
		absOperand2 = (operand2 < 0) ? -operand2 : operand2;

		// this loop just serves as a way for me to skip 
		// to the end if a condition is not met
		while (1) {
			// comparison stage 1: digits
			int len1, len2;

			len1 = floor(log10(absOperand1)) + 1;
			len2 = floor(log10(absOperand2)) + 1;
			if (len1 != len2) {
				printf ("%d and %d have different lengths.\n", operand1, operand2);
				break;
			}

			// comparison stage 2: sums
			int sum1 = 0, sum2 = 0;
			for (int i = absOperand1; i > 0; i /= 10) {
				if (operand1 != absOperand1 && i % 10 == i)
					sum1 -= i % 10;
				else
					sum1 += i % 10;
			}
			for (int i = absOperand2; i > 0; i /= 10) {
				if (operand2 != absOperand2 && i % 10 == i)
					sum2 -= i % 10;
				else
					sum2 += i % 10;
			}

			if (sum1 == sum2) {
				printf ("%d and %d are equal.\n", operand1, operand2);
			} else {
				printf ("%d and %d have different sums.\n", operand1, operand2);
			}
			break;
		}

		// ask if we should run through the loop again
		printf ("Do you want to try again? (yes: 1, no: 0)");
		scanf (" %d", &retry);

	}

	puts ("Goodbye!");

}