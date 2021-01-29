#include <stdio.h>

int main(void) {

	// only allowed 3 printf/puts? No problem. I've done it in two :)

	puts ("Please input the number of rows in the triangle:");
	int rows = 0;
	scanf (" %d", &rows);
	
	for (int row = 0; row <= rows; row ++)
		for (int star = 0; star < row; star ++)
			printf ("%s", (star == row - 1) ? "*\n" : "*");
}