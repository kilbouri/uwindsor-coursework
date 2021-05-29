// Author: Isaac Kilbourne
// Name: Sequence.c
// Date: Nov 14, 2020

#include <stdio.h>

// Write a program which calculates the sum of the first N terms of the
// inverse factorial series (1/1! + 1/2! + 1/3! + ...).
// Your program should output each term that it is summing. Restrict N to
// be between 1 and 7 inclusive.
// Your program should repeat until the user selects 0 for "no".

int main(void) {

	int retry = 1, input = 0;
	double seq;

	while (retry) {

		// input
		input = 0;
		printf ("Input an integer between 1 and 7 inclusive:");
		scanf (" %d", &input);
		while (getchar() != '\n'); // clear buffer to prevent non-numeric input from causing infinite loops

		// validation
		if (input <= 0 || input >= 8) {
			puts ("Invalid input.");
			continue;
		}

		// summation
		seq = 0;
		for (int i = 2; i <= input+1; i++) {
			if (i != 2)
				printf (" + ");
			printf ("(1 / ");

			// factorial
			int fac = 1;
			for (int x = 1; x <= i; ++x) {
				fac *= x;
			}
			seq += (double) 1 / fac;
			printf ("%g)", seq);
		}
		printf (" = %lg\n", seq);

		printf ("Do you want to try again? (yes: non-0, no: 0)");
		scanf (" %d", &retry);
	}
	puts ("Goodbye!");

}