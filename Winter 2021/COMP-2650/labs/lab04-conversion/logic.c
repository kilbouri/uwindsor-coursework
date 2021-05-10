#define MAX 8

/**
 * Takes two bytes (length-8 int arrays of 0s or 1s) and applies
 * the bitwise AND operation on them. Stores the result in out.
 * Unspecified Behaviour may occur if there are less than 8 slots
 * in any of the arrays.
 */
void func_and(int a[], int b[], int out[]) {
	for (int i = 0; i < MAX; i++)
		out[i] = a[i] && b[i];
}

/**
 * Takes two bytes and applies the bitwise OR operation on them. Stores
 * the result in out. Unspecified Behaviour may occur if there are less
 * than 8 slots in any of the arrays.
 */
void func_or(int a[], int b[], int out[]) {
	for (int i = 0; i < MAX; i++)
		out[i] = a[i] || b[i];
}

/**
 * Takes a byte and applies the logical NOT operation on it. Stores the
 * result in out. Unspecified Behaviour may occur if there are less than
 * 8 slots in either array.
 */
void func_not(int a[], int out[]) {
	for (int i = 0; i < MAX; i++)
		out[i] = !a[i];
}