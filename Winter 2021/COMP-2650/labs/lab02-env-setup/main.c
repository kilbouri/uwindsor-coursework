#include <stdio.h>

int getInt(int, int);

int main(void) {
	while (1) {
		printf("0) Exit\n1) AND\n2) OR\n");
		int input = getInt(0, 2);

		// exit case
		if (input == 0) return 0;

		printf("x = ");
		int x = getInt(0, 1);

		printf("y = ");
		int y = getInt(0, 1);

		if (input == 1)
			printf("%s AND %s = %s\n\n", x ? "T" : "F", y ? "T" : "F", (x && y) ? "T" : "F");
		else
			printf("%s OR %s = %s\n\n", x ? "T" : "F", y ? "T" : "F", (x || y) ? "T" : "F");
	}
}

/**
 * Gets an integer in the range [START, END].
 */
int getInt(int START, int END) {
	int input;
	while (1) {
		scanf("%d", &input);

		if (START <= input && input <= END) return input;

		printf("Invalid, please enter an integer between %d and %d.\n", START, END);
		while (getchar() != '\n'); // clears STD_IN
	}
}
