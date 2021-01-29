// Author: Isaac Kilbourne
// Name: B - Linear Search and Number Frequency.c
// Date: November 21, 2020

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int linearCount(int target, int* list, int count);
int* bubbleSort(int* list, int count);
int generateRandomNumber();
void prettyPrintIntList(int* list, int count);

int main(void) {

	/**
	 * Developer comment:
	 * =======================================================================================
	 * I could SLIGHTLY reduce the running time by using binary search instead of linear
	 * since I end up sorting the list anyways. However, I'm not going to be bothered to
	 * implement binary search for the tiny gain that it would get over linear.
	 * =======================================================================================
	 */

	// seed random with the current time
	srand(time(NULL));

	// allocate list and fill it with randoms
	int list[30];
	for (int i = 0; i < 30; i++) {
		list[i] = generateRandomNumber();
	}

	// gets a number in the range of 0 to 20 from the user
	int target;
	while (!scanf("%d", &target) || !(0 <= target && target <= 20))
		while(getchar() != '\n');

	// use linear scan to count the number of occurences
	int count = linearCount(target, list, 30);
	
	// Sort the list first to make it more readable
	bubbleSort(list, 30);

	printf("%d was found %d times in the following list:\n", target, count);
	prettyPrintIntList(list, 30);
	printf("\n");
}

/**
 * Linearly scans the provided list, looking for target.
 * Returns the number of time "target" was found in the
 * list up to index "count"
 */
int linearCount(int target, int* list, int count) {

	int instances = 0;
	for (int i = 0; i < count; i++) {
		if (list[i] == target)
			instances++;
	}

	return instances;
}

/**
 * Sorts the provided list of length "count" with Bubble Sort
 * Returns the sorted list, even though it doesn't need to be
 * for the swaps to take effect
 */
int* bubbleSort(int* list, int count) {

	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (list[j] > list[j+1]) {
				int temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
	return list;
}

/**
 * Generates a random number in the range 0 - 20
 */
int generateRandomNumber() { return rand() % 21; }

/** 
 * Pretty prints a list of integers 
 */
void prettyPrintIntList(int* list, int count) {
	printf("[");

	for (int i = 0; i < count - 1; i++)
		printf("%d, ", list[i]);

	printf("%d]", list[count - 1]);
}