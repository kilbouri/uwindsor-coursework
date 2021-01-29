// Author: Isaac Kilbourne
// Name: B - Factorial
// Date: Nov 15, 2020

#include <stdio.h>

unsigned int fact(unsigned int n);
unsigned int inverseFactorial(unsigned int factorial);

int main(void) {

	unsigned int testFacs[] = {2, 3, 4, 5, 10, 15};
	for (int i = 0; i < 6; i++) {
		printf ("%d! = %u\n", testFacs[i], fact(testFacs[i]));
		printf ("%u = %d\n", fact(testFacs[i]), inverseFactorial(fact(testFacs[i])));
	}
	puts ("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

	unsigned int inFact = inverseFactorial(-1);
	printf ("Largest correctly computed factorial: %u! = %u\n", inFact, fact(inFact));
}

/**
 * Computes the factorial for a given unsigned integer
 */
unsigned int fact(unsigned int n) {
	if (n <= 1)
		return 1;
	return n * fact(n-1);
}

/**
 * Returns the largest integer whose factorial is less than or equal to
 * the provided factorial
 */
unsigned int inverseFactorial(unsigned int factorial) {
	unsigned int minFact = 1;
	unsigned long minFactValue = 1; // the evaluated factorial of minFact

	while ((minFactValue *= ++minFact) < factorial);
	
	return minFact-1;
}