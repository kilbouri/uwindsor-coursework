#include <stdio.h>

#include "lib/console_colouring.h"
#include "lib/fast_math.h"
#include "lib/input.h"
#include "truth_tables.h"

void print_row(int, int, int, short[], short[]);
void print_sop(int, int, int, short[], short[]);
void print_pos(int, int, int, short[], short[]);
void to_minterm(short[], int);
void to_MAXTERM(short[], int);

int main(void) {

	ready_terminal();

	printf(RED "Please enter the number of variables: \n" RESET);
	const int VARIABLE_COUNT = get_int(0, 52); // A-Z + a-z

	printf(RED "Please enter the number of functions: " RESET);
	const int FUNCTION_COUNT = get_int(0, 10); // F0 - F9

	if (!VARIABLE_COUNT || !FUNCTION_COUNT)
		return 0;

	short left[VARIABLE_COUNT * fast_pow_2_l(VARIABLE_COUNT)];
	build_left_side(VARIABLE_COUNT, left);

	short right[fast_pow_2_l(VARIABLE_COUNT) * FUNCTION_COUNT];
	build_right_side(VARIABLE_COUNT, FUNCTION_COUNT, right);

	// ================================== DRAW CODE ==================================
	// variable header
	putchar('\n');
	for (int i = 0; i < VARIABLE_COUNT; i++)
	{
		printf(B_BLUE " %c " RESET, ((i < 26) ? 'A' : 'a') + (i % 26));

		if (i != VARIABLE_COUNT - 1)
			printf("|");
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
	for (int i = 0; i < fast_pow_2_l(VARIABLE_COUNT); i++)
	{
		print_row(VARIABLE_COUNT, FUNCTION_COUNT, i, left, right);
	}

	puts(B_RED "\nPlease select an option:" RESET);
	puts(RED "  0) Exit");
	puts("  1) Cannonical Sum of Products");
	puts("  2) Cannonical Product of Sums" RESET);
	switch (get_int(0, 2))
	{
	case 0:
		return 0;

	case 1:
		printf(GREEN);
		for (int i = 0; i < FUNCTION_COUNT; i++)
			print_sop(VARIABLE_COUNT, FUNCTION_COUNT, i, left, right);
		printf(RESET);
		break;

	case 2:
		printf(GREEN);
		for (int i = 0; i < FUNCTION_COUNT; i++)
			print_pos(VARIABLE_COUNT, FUNCTION_COUNT, i, left, right);
		printf(RESET);
		break;
	}

	putchar('\n');
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

/**
 * Prints the cannonical sum of products of the provided function
 */
void print_sop(int var_cnt, int func_cnt, int func, short left[], short right[]) {
	long n_rows = fast_pow_2_l(var_cnt);
	char hit = 0; // set to 1 when the first true result is hit. Else Fn = F

	printf("F%d = ", func);
	for (int i = 0; i < n_rows; i++)
	{
		if (right[func_cnt * i + func] == 1)
		{ // if minterm
			hit = 1;
			to_minterm(left + (var_cnt * i), var_cnt);
			printf(" + ");
		}
	}
	if (hit) // at least 1 minterm, erase the leftover " + ".
		printf("\b\b\b   \n");
	else // no minterms, this function is always False.
		printf("F\n");
}

/**
 * Prints the cannonical product of sums of the provided function
 */
void print_pos(int var_cnt, int func_cnt, int func, short left[], short right[]) {
	long n_rows = fast_pow_2_l(var_cnt);
	char hit = 0;

	printf("F%d = ", func);
	for (int i = 0; i < n_rows; i++)
	{
		if (right[func_cnt * i + func] == 0)
		{ // if MAXTERM
			hit = 1;
			to_MAXTERM(left + (var_cnt * i), var_cnt);
		}
	}
	printf("%c\n", hit ? '\0' : 'T');
}

/**
 * Outputs the minterm given the first var_cnt bits in first_var, which points
 * to the first of the variables.
 */
void to_minterm(short first_var[], int var_cnt) {
	printf("(");

	for (int l = 0; l < var_cnt; l++)
	{
		char letter = ((l < 26) ? 'A' : 'a') + (l % 26);
		char comp = first_var[l] ? 0 : '\'';
		printf("%c%c", letter, comp);
	}

	printf(")");
}

/**
 * Outputs the MAXTERM given the first var_cnt bits in first_var, which points
 * to the first of the variables.
 */
void to_MAXTERM(short first_var[], int var_cnt) {
	printf("(");

	for (int l = 0; l < var_cnt; l++)
	{
		char letter = ((l < 26) ? 'A' : 'a') + (l % 26);
		char comp = first_var[l] ? '\'' : 0;
		printf("%c%c%s", letter, comp, (l < var_cnt - 1) ? " + " : "");
	}

	printf(")");
}