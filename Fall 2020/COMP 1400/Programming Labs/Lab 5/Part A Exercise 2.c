#include <stdio.h>

int main(void) {
	int num = 0;
	printf ("Input a number:\n");
	scanf ("%d", &num);
	printf("%d is %s\n", num, (num % 2 == 0) ? "even." : "odd.");
}