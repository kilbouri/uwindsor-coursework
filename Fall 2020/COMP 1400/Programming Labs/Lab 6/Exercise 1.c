#include <stdio.h>

int main(void) {
	int num, sum = 0;
	printf("Input 10 numbers:\n");
	for (int i = 0; i < 10; i++) {
		scanf(" %d", &num);
		sum += num;
	}
	printf("The sum is %d and the average is %g.\n", sum, (float) sum / 10);
}