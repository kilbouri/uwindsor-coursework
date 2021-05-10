#define MAX 8

/**
 * Takes a byte and stores the 1's complement in the out array. Unspecified
 * Behaviour may occur if there are less than 8 slots in either array.
 */
void func_1s_comp(int a[], int out[]) {
	for (int i = 0; i < MAX; i++)
		out[i] = !a[i];
}

/**
 * Takes a byte and stores the 2's complement in the out array. Unspecified
 * Behaviour may occur if there are less than 8 slots in either array.
 */
void func_2s_comp(int a[], int out[]) {
	func_1s_comp(a, out);

	int carry = 1;
	for (int i = MAX - 1; i >= 0; i--) {
		out[i] += carry;
		carry = out[i] > 1; // sets the carry
		out[i] %= 2;

		if (!carry) break; // stop when there is nothing to carry
	}
}

/**
 * Uses an alternate algorithm to calculate the 2's complement of a provided byte.
 * Stores the result in out. Unspecifed behaviour may occur if there are less
 * than 8 slots in either array.
 */
void func_2s_comp_star(int a[], int out[]) {
	int not = 0;
	for (int i = MAX - 1; 0 <= i; i--) {
		out[i] = not ? !a[i] : a[i];
		not = not || a[i]; // will flip to 1 once a 1 is encountered
	}
}