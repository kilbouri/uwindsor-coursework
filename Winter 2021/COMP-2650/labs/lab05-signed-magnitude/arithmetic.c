#include <stdlib.h>
#include <string.h> // for memcpy()

#include "arithmetic.h"
#include "conversion.h"
#include "complement.h"

#define MAX 8
#define ARRAY_BYTES sizeof(int) * MAX

/**
 * Performs signed magnitude addition between A and B, outputting the
 * result to out.
 * Returns 1 if under/overflow occurred.
 */
int func_signed_mag_addition(int A[], int B[], int out[]) {
	// Step 0: clone a and b
	int* a = (int*) malloc(ARRAY_BYTES);
	memcpy(a, A, ARRAY_BYTES);
	int* b = (int*) malloc(ARRAY_BYTES);
	memcpy(b, B, ARRAY_BYTES);
	
	// Step 1: Make `a` the larger magnitude
	for (int i = 1; i < MAX; i++) {
		if (b[i] > a[i]) { // b has higher magnitude 
			// swap pointers then terminate
			int* tmp = a;
			a = b;
			b = tmp;

			break;
		} else if (a[i] > b[i]) { // a has higher magnitude
			break; // just break
		}
	}

	out[0] = a[0];

	// matching signs -> just add magnitudes
	if (a[0] == b[0]) {
		int carry = 0;
		for (int i = MAX - 1; i >= 0; i--) {
			out[i] = a[i] + b[i] + carry;
			carry = out[i] > 1;
			out[i] %= 2;
		}
		out[0] = a[0];
	} else { // unmatching signs
		int invertSign = 1;
		if (a[0] == 1) { // sign layout -+, change to -(+-)
			invertSign = 0;
			a[0] = 0;
			b[0] = 1;
		}

		// sign layout +-, aka subtraction
		func_2s_comp(b, b);
		int carry = 0;
		for (int i = MAX - 1; i > 0; i--) {
			out[i] = a[i] + b[i] + carry;
			carry = out[i] > 1;
			out[i] %= 2;
		}

		if (invertSign)
			out[0] = !out[0];
	}

	free(a);
	free(b);

	// overflow detection, the easy but inefficient way
	int dec_a = to_decimal_num_sm(A);
	int dec_b = to_decimal_num_sm(B);
	return dec_a + dec_b != to_decimal_num_sm(out);
}

/**
 * Performs signed magnitude subtraciton between a and b, outputting
 * the result to out. (Shorthand for negating B and calling addition 
 * instead).
 * Returns 1 if under/overflow occurred.
 */
int func_signed_mag_subtraction(int a[], int b[], int out[]) {
	b[0] = !b[0];
	int overflow = func_signed_mag_addition(a, b, out);
	b[0] = !b[0];

	return overflow;
}