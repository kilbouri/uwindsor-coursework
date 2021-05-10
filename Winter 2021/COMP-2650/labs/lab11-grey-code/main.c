#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BITS 8
void to_grey(unsigned number);
unsigned get_uint(unsigned, unsigned);

int main(void) {

    while (1) {
        puts("Enter the encoding command number:");
        puts("    0) Exit");
        puts("    1) Gray code");

        switch (get_uint(0, 1)) {
            case 0:
                return 0;

            case 1:
                printf("Please enter the number to encode: ");
                to_grey(get_uint(0, 255));
        }
    }
    to_grey((unsigned) 20);
    return 0;
}

/**
 * Stores the bits in a int array
 */
int* to_bits(unsigned num) {
    int* bits = (int*) calloc(MAX_BITS, sizeof(int));

    for (int i = MAX_BITS - 1; i >= 0 && num > 0; i--) {
        bits[i] = num % 2;
        num /= 2;
    }

    return bits;
}

/**
 * Prints the grey code representation of the provided
 * unsigned number
 */
void to_grey(unsigned number) {
    printf("Greycode of %u -> ", number);

    // perform greycode encoding on the bits
    number ^= (number >> 1);

    // display bits
    int* bits = to_bits(number);
    for (int i = 0; i < MAX_BITS; i++) {
        printf("%d", bits[i]);
    }
    printf("\n");

    free(bits);
}

/**
 * Gets an unsigned int within [min, max]
 */
unsigned get_uint(unsigned min, unsigned max) {
    unsigned input;
    while (1) {
        if (!scanf("%u", &input)) {
            printf("Invalid, please try again: ");
            while (getchar() != '\n'); // clears STD_IN
            continue;
        }

        if (min <= input && input <= max)
            return input;

        printf("Invalid, please try again: ");
        while (getchar() != '\n'); // clears STD_IN
    }
}