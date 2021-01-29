// So I heard Pooya doesn't like emotionless programs... this one is full of... heh... memotion (meme emotion)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getUserGuess() {

	printf ("\nPlease guess a number: ");

	int guess = 0;
	while (!scanf("%d", &guess)) {
		printf ("Invalid input, please try again: ");
		while (getchar() != '\n');
	}
	return guess;
}

int main(void) {
	/*
	* This function is needed because rand() always generates the same numbers unless we initialize it 
	* with srand and a seed first.
	* 
	* We can't just use srand(rand()), however, as that would still generate the same seed and therefore
	* the same numbers each time. A better approach is to use the time, which is different every time the
	* program runs.
	*/
	srand(time(0));

	printf("░░░░░░   ░░    ░░ ░░░░░░░ ░░░░░░░ ░░░░░░░ \n");
	printf("▒▒       ▒▒    ▒▒ ▒▒      ▒▒      ▒▒      \n");
	printf("▒▒   ▒▒▒ ▒▒    ▒▒ ▒▒▒▒▒   ▒▒▒▒▒▒▒ ▒▒▒▒▒▒▒ \n");
	printf("▓▓    ▓▓ ▓▓    ▓▓ ▓▓           ▓▓      ▓▓ \n");
	printf(" ██████   ██████  ███████ ███████ ███████ \n");

	// Generate random number in the range [0, 50]
	int random = rand() % 51;

	for (int i = 9; i >= 0; i--) {
		// Get user input
		int guess = getUserGuess();

		// If the user wins, print a win message and return.
		if (guess == random) {
			printf ("\nYou win! All bases of CATS were destroyed.\n");
			return 0;
		} else {
			// If the user does not input a correct input, respond with high/low and a memessage (meme-message).
			printf ("Too %s...\n", (random > guess) ? "low" : "high");
			if (i <= 2 && !i)
				printf ("You have no chance to survive make your time. (%d lives remaining)\n", i);
			else
				printf ("You have %d base left. (%d lives remaining)\n", i, i);
		}
	}

	// If the for loop runs to completion, then 10 guesses have been made 
	// and the user has lost.
	printf ("\nYou lose! All your base are belong to us!\n");
}