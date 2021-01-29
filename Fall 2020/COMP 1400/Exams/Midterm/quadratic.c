// Author: Isaac Kilbourne
// Name: Quadratic.c
// Date: Nov 14, 2020
#include <stdio.h>

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