#include <stdio.h>

#include "lib/console_colouring.h"
#include "lib/fast_math.h"
#include "lib/input.h"
#include "truth_tables.h"

void print_row(int, int, int, short[], short[]);

int main(void) {

	ready_terminal();

	printf(RED "Please enter the number of input variables: " RESET);
	const int VARIABLE_COUNT = get_int(0, 52); // A-Z + a-z

	printf(RED "Please enter the number of functions: " RESET);
	const int FUNCTION_COUNT = get_int(0, 10); // F0 - F9

	if (!VARIABLE_COUNT || !FUNCTION_COUNT) return 0;

	short left[VARIABLE_COUNT * fast_pow_2_l(VARIABLE_COUNT)];
	build_left_side(VARIABLE_COUNT, left);

	short right[fast_pow_2_l(VARIABLE_COUNT) * FUNCTION_COUNT];
	build_right_side(VARIABLE_COUNT, FUNCTION_COUNT, right);

	// ================================== DRAW CODE ==================================
	// variable header
	putchar('\n');
	for (int i = 0; i < VARIABLE_COUNT; i++) {
		printf(B_BLUE " %c " RESET, ((i < 26) ? 'A' : 'a') + (i % 26));

		if (i != VARIABLE_COUNT - 1) printf("|");
	}

	// function header
	for (int i = 0; i < FUNCTION_COUNT; i++)
		printf("|" B_GREEN " F%d " RESET, i);
	putchar('\n');

	// horizontal line break
	for (int i = 0; i < VARIABLE_COUNT; i++)
		printf("---+");
	for (int i = 0; i < FUNCTION_COUNT; i++)
		printf("----%c", (i != FUNCTION_COUNT - 1) ? '+' : '\n');

	// data
	for (int i = 0; i < fast_pow_2_l(VARIABLE_COUNT); i++) {
		print_row(VARIABLE_COUNT, FUNCTION_COUNT, i, left, right);
	}

	reset_terminal();
	return 0;
}

void print_row(int var_cnt, int func_cnt, int row, short left[], short right[]) {
	for (int x = 0; x < var_cnt; x++)
		printf(BLUE " %hd " RESET "%c", left[(row * var_cnt) + x], (x != var_cnt - 1) ? '|' : '\0');

	for (int x = 0; x < func_cnt; x++)
		printf("|" GREEN " %hd  " RESET, right[(row * func_cnt) + x]);
	putchar('\n');
}