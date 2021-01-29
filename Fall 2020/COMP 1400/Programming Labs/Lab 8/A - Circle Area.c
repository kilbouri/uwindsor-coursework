// Author: Isaac Kilbourne
// Name: A - Circle Area
// Date: Nov 15, 2020

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RADIUS 5 // how big the random radii can be
#define TEST_COUNT 5 // how many random radii to generate
#define PRE_SEED 0   // should the program seed random first?

float circArea(float radius);

int main(void) {

	if (PRE_SEED)
		srand(time(NULL));

	for (int i = 0; i < TEST_COUNT; i++) {
		float radius = ((float) rand()/RAND_MAX) * MAX_RADIUS;
		printf("Radius: %.3f\t\tArea: %.3f\n", radius, circArea(radius));
	}
}

float circArea(float radius) {
	/* pi = M_PI is defined within math.h */
	return radius * radius * M_PI;
}