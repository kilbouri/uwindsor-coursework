#include <stdio.h>

int main(void) {

	long isbn = 0; // long instead of int to avoid overflow with 12 digit numbers
	printf ("Please input the first 12 digits of your ISBN-13 to calculate the check digit:\n");
	scanf ("%12ld", &isbn);

	long tempISBN = isbn; // operate on a clone of the isbn to save the value for later
	int checksum = 0; // stores the weighted average of the 12-digit ISBN
	for (int i = 0; i < 12; i++) {

		if (i % 2)
		    checksum += tempISBN % 10;
		else			
            // if i is even, add 3 times the last digit
			checksum += 3 * (tempISBN % 10);
		tempISBN /= 10; // "remove" the last digit	
	}

	// if the checksum is a perfect multiple of 10, 
	// the check digit will erroniously be recorded as 10.
	int checkDigit = (10 - (checksum % 10)) % 10;
	// I fix this by taking mod 10 on the result.

	printf ("\nThe check digit for the ISBN-13 %ld is %d.\n", isbn, checkDigit);

}