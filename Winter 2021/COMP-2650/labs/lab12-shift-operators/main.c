#include <stdio.h>
#include <limits.h>

#include "lib/console_colouring.h"
#include "lib/input.h"

int fast_pow_2(int);
int fast_div_2(int);

int main(void) {

    ready_terminal();

    do {
        puts(RED   "Enter the command number:" RESET);
        puts(B_RED "  0) Exit" RESET);
        puts(B_RED "  1) Powers of 2" RESET);
        puts(B_RED "  2) Divisions of 2" RESET);

        switch (get_int(0, 2)) {
            case 0: {
                reset_terminal();
                return 0;
            }
            case 1: {
                printf(RED "Enter a decimal number: " RESET);
                int mult = get_int(INT_MIN, INT_MAX);

                // the positive restraint is imposed as -ve powers will
                // always result in 0.
                printf(RED "Enter a positive power number: " RESET);
                int pow = get_int(0, INT_MAX);

                printf(GREEN "%d * 2^%d = %d\n" RESET, mult, pow, mult * fast_pow_2(pow));
                break;
            }
            case 2: {
                printf(RED "Enter a decimal number: " RESET);
                int base = get_int(INT_MIN, INT_MAX);

                printf(GREEN "%d/2 = %d\n" RESET, base, fast_div_2(base));
                break;
            }
        }
    } while (1);

}

/**
 * Returns 2^pow using bitshift which is (typically) faster than
 * the C standard pow() function
 */
int fast_pow_2(int pow) {
    return 1 << pow;
}

/**
 * Returns num/2 by bitshift to the right.
 */
int fast_div_2(int num) {
    return num >> 1;
}