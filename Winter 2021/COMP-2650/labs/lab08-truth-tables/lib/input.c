#include <stdio.h>
/**
 * Gets a short within [min, max]
 */
short get_short(short min, short max) {
	short input;
	while (1) {
		if (!scanf("%hd", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets an int within [min, max]
 */
int get_int(int min, int max) {
	int input;
	while (1) {
		if (!scanf("%d", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets a long within [min, max]
 */
long get_long(long min, long max) {
	long input;
	while (1) {
		if (!scanf("%ld", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets a long long within [min, max]
 */
long long get_long_long(long long min, long long max) {
	long long input;
	while (1) {
		if (!scanf("%Ld", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets a float within [min, max]
 */
float get_float(float min, float max) {
	float input;
	while (1) {
		if (!scanf("%f", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets a double within [min, max]
 */
double get_double(double min, double max) {
	double input;
	while (1) {
		if (!scanf("%lf", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets an unsigned short within [min, max]
 */
unsigned short get_ushort(unsigned short min, unsigned short max) {
	unsigned short input;
	while (1) {
		if (!scanf("%hu", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets an unsigned int within [min, max]
 */
unsigned get_uint(unsigned min, unsigned max) {
	unsigned input;
	while (1) {
		if (!scanf("%u", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets an unsigned long within [min, max]
 */
unsigned long get_ulong(unsigned long min, unsigned long max) {
	unsigned long input;
	while (1) {
		if (!scanf("%lu", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}

/**
 * Gets an unsigned long long within [min, max]
 */
unsigned long long get_ulong_long(unsigned long long min, unsigned long long max) {
	unsigned long long input;
	while (1) {
		if (!scanf("%Lu", &input)) {
			printf("Invalid, please try again: ");
			while (getchar() != '\n'); // clears STD_IN
			continue;
		}

		if (min <= input && input <= max) return input;

		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clears STD_IN
	}
}