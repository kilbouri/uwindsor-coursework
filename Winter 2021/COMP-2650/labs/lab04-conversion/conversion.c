#include <stdio.h>
#include <math.h>

#define MAX 8

/**
 * Converts a byte to a decimal number
 */
int to_decimal_num(int byte[]) {
	int decimalConversion = 0;
	for (int i = MAX - 1; i >= 0; i--) {
		decimalConversion += byte[i] * pow(2, MAX - 1 - i);
	}
	return decimalConversion;
}

/**
 * Prints a byte in binary (no conversion occurs)
 */
void to_binary(int byte[]) {
	for (int i = 0; i < MAX; i++)
		printf("%d", byte[i]);
}

/**
 * Prints a byte in octal format.
 */
void to_octal(int byte[]) {
	char octal[MAX + 1] = { 0 };

	int decimal = to_decimal_num(byte);
	for (int i = MAX - 1; i >= 0; i--) {
		octal[i] = '0' + decimal % 8;
		decimal /= 8;
	}
	printf("0o%s", octal);
}

/**
 * Prints a byte in decimal format.
 */
void to_decimal(int byte[]) {
	printf("%d", to_decimal_num(byte));
}

/**
 * Prints a byte in hexadecimal format.
 */
void to_hexadecimal(int byte[]) {
	char hex[MAX+1] = { 0 }; // extra space to guarantee a string termination

	int decimal = to_decimal_num(byte);
	for (int i = MAX - 1; i >= 0; i--) {
		int rem = decimal % 16;
		hex[i] = (rem < 10) ? '0' + rem : 'A' + rem - 10;
		decimal /= 16;
	}
	printf("0x%s", hex);
}