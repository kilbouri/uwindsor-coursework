// Author: Isaac Kilbourne
// Name: C - Binary Conversion
// Date: Nov 15, 2020
#include <stdio.h>
#include <math.h>

#define INT_SIZE_BITS (int) sizeof(int) * 8

long decimalToBinary(int decimal);
int binaryToDecimal(long binary);

int main(void) {

	int nums[] = {1, 2, 10, 1001, 90250};
	for (int i = 0; i < 5; i++) {
		printf("% *d \tin binary: \t%0*ld\n", 6, nums[i], INT_SIZE_BITS, decimalToBinary(nums[i]));
	}
}

long decimalToBinary(int decimal) {
	int place = 0;
	long binary = 0;

	for (; decimal > 0; decimal /= 2) {
		/**
		 * Has to be casted to a long long before use because pow() returns
		 * a double. In the case of 90251, the double that is returned for the 
		 * final power (10^16) has some sort of decimal or imprecision that causes
		 * 1 * the result to be 2. So, without casting, if the decimal argument is
		 * 90251, and probably a bunch of others but I cannot be assed to find them,
		 * then the last digit of the binary result will be 2. I'm not kidding. Try it yourself.
		 * 
		 * Yes, I have something not unlike PTSD from trying to resolve this bug that
		 * was stumbled upon by a random test for the past 2-ish hours at the time I am ranting
		 * this comment into my program.
		 * TL;DR: long long >>>>>>>>>>>>> double
		 */
		long long power = pow(10, place++);
		binary += (decimal % 2) * power;
	}
	return binary;
}

// wrote this without realizing the question didn't want it. Oh well.
int binaryToDecimal(long binary) {
	int sum = 0;
	int place = 0;
	
	for (; binary > 0; binary /= 10)
		sum += pow(2, place++) * (binary % 10);
	
	return sum;
}