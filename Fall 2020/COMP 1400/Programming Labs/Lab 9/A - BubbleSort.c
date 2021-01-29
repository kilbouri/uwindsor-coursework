// Author: Isaac Kilbourne
// Name: A - BubbleSort.c
// Date: November 21, 2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

unsigned long getMillisecondsElapsed(struct timeval start, struct timeval stop);
int generateRandomNumber();
int* bubbleSort(int* list, int count);
void prettyPrintIntList(int* list, int count);

int main(void) {

	srand(time(NULL));

	// Get the length of the list to be sorted
	int len;
	do {
		printf("Please input a positive, non-0 integer:  ");
	} while (!scanf("%d", &len) || len <= 0);

	// Generate the list to sort
	int toSort[len];
	for (int i = 0; i < len; i++) {
		toSort[i] = generateRandomNumber();
	}
	printf("The list to sort: ");
	prettyPrintIntList(toSort, len);
	printf("\n\nSorting...\n");

	// will store the time
	struct timeval start, stop;

	gettimeofday(&start, NULL); // store the start time
	int* sorted = bubbleSort(toSort, len); // BubbleSort the list
	gettimeofday(&stop, NULL); // store the stop time

	unsigned long elapsed = getMillisecondsElapsed(start, stop);
	printf("\nTook %lu seconds to sort %d items with Bubble Sort.\n", elapsed, len);
	printf("Sorted list: ");
	prettyPrintIntList(sorted, len);
	puts("");

}

int generateRandomNumber() { return rand() % 100 + 1; }

unsigned long getMillisecondsElapsed(struct timeval start, struct timeval stop) {
	return (unsigned long) (stop.tv_sec - start.tv_sec);
}

/**
 * Sorts the provided list of length "count" with Bubble Sort
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
 * Pretty prints a list of integers 
 */
void prettyPrintIntList(int* list, int count) {
	printf("[");

	for (int i = 0; i < count - 1; i++)
		printf("%d, ", list[i]);

	printf("%d]", list[count - 1]);
}