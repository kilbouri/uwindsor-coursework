/**
 * Uses bit shifting to compute 2^n faster (in theory. In practice,
 * the implementation of pow() may be just as good as bit shift) than
 * the standard math's pow() function
 */
int fast_pow_2(int n) {
	return 2 << (n - 1);
}

/**
 * Long version of fast_pow_2.
 */
long fast_pow_2_l(int n) {
	return (long)2 << (n - 1);
}