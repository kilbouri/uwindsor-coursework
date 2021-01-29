#include <stdio.h>
#include <math.h>

int isPrime(unsigned int natural) {
	/* Computing primeness only requires checking if any integers
	 * in the range [2, sqrt(n)] are factors of the number.
	 */

	int rootNatural = ceil(sqrt(natural));

	for (unsigned int factor = 2; factor <= rootNatural; factor ++) {

		/* If the remainder of dividing by the factor is 0, the
		 * factor is a factor of the number and therefore the 
		 * number is not a prime
		 */
		if (natural % factor == 0) {
			return 0;
		}
	}
	return (natural > 1) ? 1 : 0;
}
int main(void) {

	printf("Please enter a natural number:" );
	unsigned int natural = 0;
	scanf("%u", &natural);

	printf ("%u %s a prime number.\n", natural, (isPrime(natural)) ? "is" : "isn't");
}