#include <stdio.h>

int main( void ) {
	int base = 0, max = 0;
	
	puts("Input two numbers to compute the multiplication table of the first up to the second:");
	scanf ("%d %d", &base, &max);

	for (int i = 0; i <= max; i++) {
		printf("%d \t X %d \t = %Ld\n", base, i, (long long) base * i);
	}
}