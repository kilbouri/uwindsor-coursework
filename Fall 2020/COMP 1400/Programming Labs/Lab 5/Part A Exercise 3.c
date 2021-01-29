#include <stdio.h>

int main(void) {
	int year;

	printf ("Enter a year:\n");
	scanf (" %d", &year);

	/*
	 * Non-turn-of-century years are leap years if divisible by 4.
	 * Turn-of-century years are leap yers only if divisible by 400.
	 */
	if (year % 100 == 0 && year % 400 == 0)
		printf ("%d is a turn-of-century leap year.\n", year);
	else if (year % 4 == 0)
		printf ("%d is a leap year.\n", year);
	else
		printf ("%d is not a leap year.\n", year);
}