/* ========================================
 * COMP-1410 Assignment 2
 * ----------------------------------------
 * Student name: 			Isaac Kilbourne
 * External Sources:		None
 * ========================================
 */

#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define EMPTY_CHAR ' '
#define PLAYER_A   'A'
#define PLAYER_B   'B'

 /* Terminal coloring */
#ifndef __unix__
#define P1_Char   "X"
#define P2_Char   "O"
#define Player1   ""            // Standard ANSI color codes don't work, so
#define Player2   ""            // just define empty strings.
#define RESET     ""

#else
#define P1_Char   "■"
#define P2_Char   "■"
#define Player1   "\033[0;31m"  // Player 1 -> Red
#define Player2   "\033[0;36m"  // Player 2 -> Blue
#define RESET	  "\033[0m"     // RESET to default
#endif

void do_startup_checks();
bool make_move(char[6][7], int, char);
bool check_win(char[6][7], char);
bool check_stalemate(char[6][7]);
bool board_cmp(char[6][7], int, const char*);
void print_board(char[6][7]);
char first_capital(const char[], int);
void deepest_substring(const char[], char[]);

int main(void) {

	// all function tests are located in this function
	do_startup_checks();

	puts("Now starting game...");
	puts("\n\n\n");

	puts("   █████████                                                           ███          ███   ███  ");
	puts("  ███░░░░░███                                                         ░███         ░███  ░███  ");
	puts(" ███     ░░░    ██████   ████████    ████████     ██████    ██████   ███████       ░███  ░███  ");
	puts("░███           ███░░███  ░███░░███   ░███░░███   ███░░███  ███░░███░ ░░███░        ░███████████");
	puts("░███          ░███ ░███  ░███ ░███   ░███ ░███  ░███████  ░███ ░░░    ░███         ░░░░░░░███░ ");
	puts("░░███     ███ ░███ ░███  ░███ ░███   ░███ ░███  ░███░░░   ░███  ███   ░███               ░███  ");
	puts(" ░░█████████  ░░██████   ░███ ░███   ░███ ░███  ░░██████  ░░██████    ░███               ░███  ");
	puts("  ░░░░░░░░░    ░░░░░░    ░░░  ░░░░   ░░░  ░░░░   ░░░░░░    ░░░░░░     ░░░░               ░░░   ");
	char game_board[6][7] = {
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '}
	};
	print_board(game_board);

	char player = PLAYER_A;
	while (1) {
		printf("Your move, %sPlayer %c%s.\n", (player == PLAYER_A) ? Player1 : Player2, player, RESET);
		printf("Enter an integer between 0 and 6 to place a piece, or anything else to surrender: ");

		int column = -1;
		do {
			if (scanf("%d", &column)) {
				if (0 <= column && column <= 6) {
					if (make_move(game_board, column, player))
						break;
					else {
						printf("Invalid selection, please select again: ");
						continue;
					}
				}
			}
			if (player == PLAYER_A) {
				printf("\n" Player1 "Player A" RESET " surrenders. ");
				printf("Congratulations " Player2 "Player B" RESET ", you win!\n\n");
			} else {
				printf("\n" Player2 "Player B" RESET " surrenders. ");
				printf("Congratulations " Player1 "Player A" RESET ", you win!\n\n");
			}
			return 0;
		} while (true);

		print_board(game_board);

		if (check_win(game_board, PLAYER_A)) {
			printf("Congratulations " Player1 "Player A" RESET ", you win!\n\n");
			return 0;
		} else if (check_win(game_board, PLAYER_B)) {
			printf("Congratulations " Player2 "Player A" RESET ", you win!\n\n");
			return 0;
		} else if (check_stalemate(game_board)) {
			printf("Tie!\n\n");
			return 0;
		}

		player = (player == PLAYER_A) ? PLAYER_B : PLAYER_A;
	}
}

void do_startup_checks() {
	puts("Running startup checks...");
	puts("---------------------------");

	char moveTest[6][7] = {
		"O     ",
		"O     ",
		"X     ",
		"X     ",
		"X     ",
		"XXXXOO"
	};
	assert(!make_move(moveTest, 0, 'X'));
	assert(!strcmp(moveTest[0], "O     "));
	assert(make_move(moveTest, 1, 'O'));
	assert(!strcmp(moveTest[4], "XO    "));
	assert(!strcmp(moveTest[5], "XXXXOO"));
	puts("[PASS] make_move()");

	char upCheck[6][7] = {
		"O     ",
		"X     ",
		"X     ",
		"X     ",
		"X     ",
		"OOOOOO"
	};
	assert(check_win(upCheck, 'X'));
	char rightCheck[6][7] = {
		"      ",
		"      ",
		" XXXX ",
		" OOOX ",
		" OXOO ",
		" XOOO "
	};
	assert(check_win(rightCheck, 'X'));
	char diag_check1[6][7] = {
		"      ",
		"      ",
		" OOOX ",
		" OOXO ",
		" OXOO ",
		" XOOO "
	};
	assert(check_win(diag_check1, 'X'));
	char diag_check2[6][7] = {
		"      ",
		"      ",
		" XOOO ",
		" OXOO ",
		" OOXO ",
		" OOOX "
	};
	assert(check_win(diag_check2, 'X'));
	puts("[PASS] check_win()");

	assert(first_capital("abcABC", 6) == 'A');
	assert(first_capital("ABCDEF", 6) == 'A');
	assert(first_capital("0BCDEF", 6) == 'B');
	assert(first_capital("abcdef", 6) == 0);
	assert(first_capital("0bcdef", 6) == 0);
	puts("[PASS] first_capital()");

	char out[256];
	deepest_substring("a+((b+c)+d)", out);
	assert(!strcmp(out, "b+c"));
	deepest_substring("((a))", out);
	assert(!strcmp(out, "a"));
	deepest_substring("((a)+(b+(d)))", out);
	assert(!strcmp(out, "d"));
	deepest_substring("()", out);
	assert(!strcmp(out, ""));
	puts("[PASS] deepest_substring()");

	puts("---------------------------");
}

/**
 * Updates the board following a move by the given player in the given column.
 * Returns false if the move was illegal (ie, a full column)
 * Requires 0 <= col <= 7
 */
bool make_move(char board[6][7], int col, char player) {
	for (int r = 0; r < 6; r++) {
		if (board[r][col] != EMPTY_CHAR) {
			if (!r) return false; // top of column, invalid move

			board[r - 1][col] = player;
			return true;
		}
	}
	board[5][col] = player;
	return true;
}

/**
 * Returns true if the specified player has 4 connected pieces on
 * the board along the horizontal, vertical, or diagonal directions.
 *
 * Uses a brute-force comparison check. Not the most efficient, but
 * its good enough. Does not check down, left, or downward diagonals
 * as they will be checked via the progressive scan.
 */
bool check_win(char b[6][7], char player) {
	for (int y = 5; y >= 0; y--) {
		for (int x = 0; x < 6; x++) {
			if (b[y][x] != player) continue;

			// check: up
			if (y >= 3) {
				if (b[y - 1][x] == player && b[y - 2][x] == player && b[y - 3][x] == player)
					return true;
			}

			// check: right
			if (x <= 3) {
				if (b[y][x + 1] == player && b[y][x + 2] == player && b[y][x + 3] == player)
					return true;
			}

			// check: up-right
			if (x <= 3 && y >= 3) {
				if (b[y - 1][x + 1] == player && b[y - 2][x + 2] == player && b[y - 3][x + 3] == player)
					return true;
			}

			// check: up-left
			if (x >= 3 && y >= 3) {
				if (b[y - 1][x - 1] == player && b[y - 2][x - 2] == player && b[y - 3][x - 3] == player)
					return true;
			}
		}
	}
	return false;
}

/**
 * Checks whether all positions in the game board are filled
 */
bool check_stalemate(char b[6][7]) {
	for (int i = 0; i < 7; i++)
		if (b[0][i] == EMPTY_CHAR) return false;

	return true;
}

/**
 * Prints the board to the screen
 */
void print_board(char board[6][7]) {
	puts("╔═════════════╗");
	for (int y = 0; y < 6; y++) {
		printf("║");
		for (int x = 0; x < 7; x++) {
			if (board[y][x] == PLAYER_A)
				printf(Player1 P1_Char RESET);
			else if (board[y][x] == PLAYER_B)
				printf(Player2 P2_Char RESET);
			else
				putchar(' ');

			if (x != 6)
				putchar(' ');
		}
		printf("║\n");
	}
	puts("╚═════════════╝");
	puts(" 0 1 2 3 4 5 6 ");
}

/**
 * Returns the first capital letter in the provided string of length len,
 * or 0 (null) if there are no capital letters in the string.
 * Requires that all lowercase letters preceed all capital letters.
 */
char first_capital(const char str[], int len) {
	int left = 0, right = len;
	while (left <= right) {
		int mid = left + (right - left) / 2; // calculate midpoint

		// this is the first capital, return it
		if (isupper(str[mid]) && (mid == 0 || !isupper(str[mid - 1])))
			return str[mid];

		// ignore right half
		else if (isupper(str[mid]))
			right = mid - 1;

		// ignore left half
		else
			left = mid + 1;
	}

	return (char)0;
}

/**
 * Sets out to contain the string within the deepest parenthesis in the provided
 * string. Unspecified Behaviour may occur if out is shorter than the deepest
 * substring, or if str contains unbalanced parenthesis.
 *
 * Requires str be a string with balanced parenthesis
 * Requires out points to enough memory to store the deepest substring in str.
 */
void deepest_substring(const char str[], char out[]) {
	// indicate the max depth found, and the current depth
	int max = 0, curr = 0;
	// indicate where the substring starts and ends, including parenthesis
	int deepest_start = 0, deepest_end = 0;

	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == '(') {
			curr++;
			if (curr > max) {
				max = curr;
				deepest_end = deepest_start = i; // set start and end to current position
			}
		} else if (str[i] == ')') {
			if (curr == max) // if this is the end of the deepest known pair, set endpoint.
				deepest_end = i;
			curr--;
		}
	}

	// copy substring to out
	int substr_len = deepest_end - deepest_start - 1;
	memcpy(out, str + deepest_start + 1, sizeof(char) * substr_len);
	out[substr_len] = 0; // set string termination
}