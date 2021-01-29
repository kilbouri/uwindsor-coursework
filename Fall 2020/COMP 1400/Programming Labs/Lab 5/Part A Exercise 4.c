#include <stdio.h>

// not taught yet but way easier to just create a pair of functions
int min(a, b) {
	return (a < b) ? a : b;
}
int max(a, b) {
	return (a > b) ? a : b;
}

int main(void) {
  
	int a, b, c;
	printf ("Input 3 integers separated by spaces (ie, '1 2 3')\n");
	scanf ("%d %d %d", &a, &b, &c);

	printf ("The biggest of %d, %d, and %d is %d\n", a, b, c, max(a, max(b, c)));
	printf ("The smallest of %d, %d, and %d is %d\n", a, b, c, min(a, min(b, c)));

}
