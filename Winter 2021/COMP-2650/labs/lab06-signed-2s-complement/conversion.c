#include <stdio.h>
#include <stdlib.h>
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
 * Converts a byte to a decimal number (using Signed Mag)
 */
int to_decimal_num_sm(int byte[]) {
	int decimalConversion = 0;
	for (int i = MAX - 1; i > 0; i--)
		decimalConversion += byte[i] * pow(2, MAX - i - 1);
	
	if (byte[0]) decimalConversion *= -1;
	return decimalConversion;
}

/**
 * Converts a byte to a decimal number (using signed 2s comp)
 */
int to_decimal_num_2s(int byte[]) {
	int fullNum = to_decimal_num(byte);
	
	if (byte[0])
		fullNum -= pow(2, MAX);

	return fullNum;
}

/**
 * Prints a byte in binary (no conversion occurs)
 */
void to_binary(int a[]) {
	for (int i = 0; i < MAX; i++)
		printf("%d", a[i]);
}

/**
 * Prints a byte in octal format.
 */
void to_octal(int byte[], int use_sm) {
	char octal[MAX] = { 0 };

	int decimal = use_sm ? to_decimal_num_sm(byte) : to_decimal_num(byte);
	int negative = decimal < 0;
	for (int i = MAX - 2; i >= 0; i--) {
		octal[i] = '0' + abs(decimal) % 8;
		decimal /= 8;
	}
	printf("0o%c%s", (use_sm && negative) ? '7' : '0', octal);
}

/**
 * Prints a byte in decimal format.
 */
void to_decimal(int byte[], int use_sm) {
	printf("%d", use_sm ? to_decimal_num_sm(byte) : to_decimal_num(byte));
}

/**
 * Prints a byte in hexadecimal format.
 */
void to_hexadecimal(int byte[], int use_sm) {
	char hex[MAX] = { 0 }; // extra space to guarantee a string termination

	int decimal = use_sm ? to_decimal_num_sm(byte) : to_decimal_num(byte);
	int negative = decimal < 0;
	for (int i = MAX - 2; i >= 0; i--) {
		int rem = abs(decimal) % 16;
		hex[i] = (rem < 10) ? '0' + rem : 'A' + rem - 10;
		decimal /= 16;
	}
	printf("0x%c%s", (use_sm && negative) ? 'F' : '0', hex);
}