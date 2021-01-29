// Author: Isaac Kilbourne
// Name: q2.c
// Date: Dec 12, 2020
/** You can run this code online at https://repl.it/@voidvenom/Question-2 **/

#include <stdio.h>

// Write a C function, diff, that receives an integer number and returns the difference between the product
// of its digits and the average of its digits. Then, write a C program that gets an integer number, n, from a
// user and calls the function diff, if n > 10. The program then prints the result of running the function. 

float diff(int num);

int main(void) {

	int n = 0;
	printf("Please enter a number: ");
	
	scanf(" %d", &n);
	if (n > 10)
		printf("The result is %.2f", diff(n));
	else 
		puts("Too small!");

}

float diff(int num) {
	float avg = 0;
	int product = 1, digitCount = 0, digit;

	while (num) {
		digit = num % 10;
		
		digitCount++;
		avg += digit;
		product *= digit;

		num /= 10;
	}
	avg /= digitCount;
	return product - avg;
}