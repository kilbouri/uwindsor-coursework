// Author: Isaac Kilbourne
// Name: q1.c
// Date: Dec 12, 2020
/** You can run this code online at https://repl.it/@voidvenom/Question-1 **/

#include <stdio.h>

// Write a C program that displays your name and then reads 10 integer numbers from the user and stores
// them in an array of size 30. Then the program displays the multiplication of the non-zero even numbers
// which are in the odd index positions of the array.

int main(void) {

	puts("My name is: Isaac Kilbourne\
	    \n***************************");

	int nums[30] = {0};
	printf("Please enter an %d integers separated by commas:\n", 10);
	
	for (int i = 0; i < 10; i++) {
		scanf(" %d,", &nums[i]);
	}

	puts("***************************");

	// compute and print output
	int product = 1;
	for (int i = 1; i < 10; i += 2) {
		if (nums[i] && !(nums[i] % 2))
			product *= nums[i];
	}

	printf("The result is: %d\n", product);

	puts("***************************");

}