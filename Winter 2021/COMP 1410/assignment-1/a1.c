/* ===========================================================================
COMP-1410 Assignment 1
==============================================================================
Student name: Isaac Kilbourne

External sources:
- List of prime numbers: https://en.wikipedia.org/wiki/List_of_prime_numbers
- That's all I used. That's why my implementations are so terribly optimized 🤣

Internal sources:
- choose(n, m) test cases: A calculator capable of performing the binomial coefficient
=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int choose(int, int);
int num_divisors_up_to_k(int, int);
bool is_prime(int);
int collatz(int);
int collatz_mute(int);

int main(void) {
	assert(!choose(2, 5));			// test case: n < m
	assert(!choose(5, -1));			// test case: negative m
	assert(!choose(-1, 5));			// test case: negative n
	assert(!choose(0, 5));			// test case: picking from 0 elements
	assert(choose(5, 0) == 1);		// test case: picking 0 0 elements
	assert(choose(4, 2) == 6);		// test case: 4 choose 2 should be 6
	assert(choose(5, 1) == 5);		// test case: 5 choose 1 should be 5
	assert(choose(10, 3) == 120);	// test case: 10 choose 3 should be 120
	puts("[PASS] choose(n, m)");

	assert(!num_divisors_up_to_k(-1, 3));		// test case: negative n
	assert(!num_divisors_up_to_k(5, -1));		// test case: negative k
	assert(!num_divisors_up_to_k(0, 1));		// test case: divisors of 0
	assert(num_divisors_up_to_k(9, 3) == 2);	// test case: 2 factors in [1, 3] for 9
	assert(num_divisors_up_to_k(6, 6) == 4);	// test case: 4 factors in [1, 6] for 6
	assert(num_divisors_up_to_k(100, 25) == 7);	// test case: 7 factors in [1, 25] for 100
	puts("[PASS] num_divisors_up_to_k(n, k)");

	assert(!is_prime(-5));	// test case: negative prime number should not be prime
	assert(!is_prime(1));	// test case: 1 is non-prime
	assert(!is_prime(4));	// test case: 4 is non-prime
	assert(!is_prime(210));	// test case: 210 is non-prime
	assert(is_prime(5));	// test case: 5 is prime
	assert(is_prime(23));	// test case: 23 is prime
	assert(is_prime(1429));	// test case: 1429 is prime
	puts("[PASS] is_prime(n)");

	assert(!collatz_mute(0));		// test case: n = 0
	assert(!collatz_mute(1));		// test case: n = 1
	assert(!collatz_mute(-1));		// test case: negative n
	assert(collatz_mute(5) == 5);	// test case: collatz(5) takes 5 steps
	assert(collatz_mute(7) == 16);	// test case: collatz(7) takes 16 steps
	puts("[PASS] collatz(n)");

	puts("All functions passed their tests.");
	puts("=================================");

	int n = 0;
	while (true) {
		puts("Please enter an integer greater than or equal to 1, or type \"quit\" to exit.");
		if (!scanf(" %d", &n)) break;

		if (n <= 1) {
			puts("Error: Invalid input.");
			continue;
		}

		collatz(n);
	}
}

/**
* choose(n, m) returns how many ways there are to chose m items from a set of
* n items. Requires 0 <= m <= n.
*/
int choose(int n, int m) {
	if (n <= 0 || m < 0 || m > n) return 0; // make sure 0 <= m <= n
	if (m == 0 || m == n) return 1; // recursive base case

	return choose(n - 1, m) + choose(n - 1, m - 1);
}

/**
* num_divisors_up_to_k(n, k) returns the number of positive divisors of n
* that are less than or equal to k. Requires: 1 <= k <= n
*/
int num_divisors_up_to_k(int n, int k) {
	if (k > n || k < 1 || n < 1) return 0;

	// adds one to the returned total if k is a factor of n
	return num_divisors_up_to_k(n, k - 1) + (n % k == 0);
}

/**
* is_prime(n) returns whether or not n is a prime number. Requires 1 <= n
*/
bool is_prime(int n) {
	// only 2 factors (1, n) in [1, n] for n when n is prime
	return num_divisors_up_to_k(n, n) == 2;
}

/**
* collatz(n) returns the number of steps it takes to reach 1 by repeatedly
* the Collatz mapping on n; prints each number in the sequence starting at
* n. Requires 1 <= n
*/
int collatz(int n) {
	if (n <= 1) { // recursive base case
		printf("%d\n", n);
		return 0;
	}

	printf("%d -> ", n);

	const int nxt = (n % 2) ? 3 * n + 1 : n / 2;
	return collatz(nxt) + 1;
}

/**
* Just like the regular collatz funciton, but silenced. Intended for use with
* assert testing since printing the path of every collatz function would be ugly.
* Still requires 1 <= n.
*/
int collatz_mute(int n) {
	if (n <= 1) return 0;

	const int nxt = (n % 2) ? 3 * n + 1 : n / 2;
	return collatz_mute(nxt) + 1;
}
