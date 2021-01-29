#include <stdio.h>

int main( void ) {

	int day = 0;
	puts ("Input an integer in the range [0, 7]:");
	scanf ("%d", &day);
	
	/* Mathematical formula: f(x) = mod(floor(abs(x)) - 1, 7) + 1
	 * Try the formula into a graphing program such as Desmos.com
	 * This function WRAPS the day to the range of [1, 7].
	 */
	day = ((((day >= 0) ? day : -day) - 1) % 7) + 1;

	switch (day) {
		case 1:
			puts ("Monday");
			break;
		case 2:
			puts ("Tuesday");
			break;
		case 3:
			puts ("Wednesday");
			break;
		case 4:
			puts ("Thursday");
			break;
		case 5:
			puts ("Friday");
			break;
		case 6:
			puts ("Saturday");
			break;
		case 7:
			puts ("Sunday");
			break;	
	}
}