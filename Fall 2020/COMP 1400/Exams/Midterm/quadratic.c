// Author: Isaac Kilbourne
// Name: Quadratic.c
// Date: Nov 14, 2020
#include <stdio.h>

// Write a program that computes the value of a quadratic equation.
// Your program should ask the user for the coefficients, a constant,
// and the x value to evaluate the function at.
// Also, if the value of x is greater than 40,000, notify the user
// that overflow may occur in the result.

int main(void) {

	// get input
	int a, b, c, x;

	printf("Please enter four integer numbers for a, b, c, and x:");
	scanf("%d %d %d %d", &a, &b, &c, &x);

	printf ("Q(x) = (%d)x^2 + (%d)x + (%d)\n", a, b, c);
	
	// overflow check
	if (x > 40000) {
		puts("Possible overflow.");
		return 1;
	}

	// computation
	int q = a * x * x; 	// ax^2
	q += b * x; 		// + bx
	q += c; 			// + c
	printf ("Q(%d) = %d\n", x, q);

	return 0;
}