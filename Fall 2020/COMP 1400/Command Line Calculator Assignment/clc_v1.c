#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// these variables must be defined in the global scope and before getValidatedVariableInput() 
// for reading either a variable name OR a number
double variables[] = {0, 0, 0, 0, 0};

// These strings may be repeated frequently in the program, so to make modifying them easier they are declared here.
const char floatingPointPrompt[] = "\nInput a floating-point number (examples: 3.14, 3.1e4): ";
const char variableNamePrompt[] = "\nPlease input a variable name (any single letter between a and e): ";
const char varOrFloatingPointPrompt[] = "\nPlease input either the name of a variable (any single letter between a and e) or a floating-point number (examples: 3.14, 3.1e4): ";
const char binaryOperationPrompt[] = "\nInput a binary operation (+, - , *, /, %%, P (power), X (max), I (min)): "; 
const char unaryOperationPrompt[] = "\nInput a unary operation (S (square root), L (logarithm base 10), E (exponentiation), C (ceiling), F (floor)): ";
const char invalidNumberResponse[] = "Invalid number, please try again: ";
const char invalidVariableResponse[] = "Invalid variable name, please try again: ";
const char invalidVarOrNumberResponse[] = "Invalid number/variable name, please try again: ";
const char invalidOperationResponse[] = "Invalid operation, please try again: ";

// These operation arrays may be repeated in multiple places in the program, so 
// to make modifying them easier, they are declared here.
const char validOptions[] = {'b', 'u', 'a', 'v', 'e'};
const char validSubOptions[] = {'b', 'u', 'e'};
const char validBinaryOperations[] = {'+', '-', '*', '/', '%', 'p', 'x', 'i'};
const char validUnaryOperations[] = {'s', 'l', 'e', 'c', 'f'};
const char validVariableNames[] = {'a' ,'b' ,'c' ,'d' ,'e'};

double getValidatedVariableInput(const char prompt[]) {

	printf ("%s", prompt);

	double returnValue;

	// first try to scan a number
	while (1) { // will return once a valid input is gotten
		if (scanf (" %lg", &returnValue))
			return returnValue; // success will terminate the function here

		// if it fails, try getchar()ing the first character to see if it's a variable name
		char firstChar = tolower(getchar());

		if ( 'a' <= firstChar && firstChar <= 'e') {
			// variable name entered, fetch from the appropriate variable
			return variables[firstChar - 'a'];
		}
		while (getchar() != '\n'); // clear for next attempt
	}
}

double getValidatedDouble(const char prompt[]) {

	printf("%s", prompt);

	double returnValue;
	while (!scanf(" %lg", &returnValue)) {
		printf("Invalid, please try again: ");
		while (getchar() != '\n'); // clear input buffer for new input
	}
	return returnValue;
}

char getValidatedChar(const char prompt[], const char* validChars, int size) {

	printf("%s", prompt);

	// runs until the function returns, which only occurs for valid inputs
	while (1) {
		char character = tolower(getchar());
		if (character == '\n')
			continue;
		
		// iterate over validChars, looking for the read character
		for (int i = 0; i < size; i++) {
			if (validChars[i] == character) {
				return character;
			}
		}
		while(getchar() != '\n');
	}
}

void binaryMathOps(double operand1, char operation, double operand2, int acceptVars) {
	switch (operation) {
		case '+': 
			printf("\n%lg + %lg = %lg\n", operand1, operand2, operand1 + operand2);
			break;
		case '-':
			printf("\n%lg - %lg = %lg\n", operand1, operand2, operand1 - operand2);
			break;
		case '*':
			printf("\n%lg * %lg = %lg\n", operand1, operand2, operand1 * operand2);
			break;
		case '/':
			while (!operand2) { // run until non-zero is given
				if (acceptVars)
					operand2 = getValidatedVariableInput("\nYou can't divide by zero! Please try a different divisor: ");
				else
					operand2 = getValidatedDouble("\nYou can't divide by zero! Please try a different divisor: ");
			}
			printf("\n%lg / %lg = %lg\n", operand1, operand2, operand1 / operand2);	
			break;
		case '%':
			printf("\n%lg %% %lg = %lg\n", operand1, operand2, remainder(operand1, operand2));
			break;
		case 'p':
			printf("\n%lg ^ %lg = %lg\n", operand1, operand2, pow(operand1, operand2));
			break;
		case 'x':
			printf("\nmax(%lg, %lg) = %lg\n", operand1, operand2, (operand1 > operand2) ? operand1 : operand2);
			break;
		case 'i':
			printf("\nmin(%lg, %lg) = %lg\n", operand1, operand2, (operand1 < operand2) ? operand1 : operand2);
			break;
	}
	while (getchar() != '\n');
}

void unaryMathOps(double operand, char operation, int acceptVars) {
	switch (operation) {
		case 's':
			while (operand < 0) {
				if (acceptVars)
					operand = getValidatedVariableInput("You can't take the square root of a negative number, try a different number: ");
				else 
					operand = getValidatedDouble("You can't take the square root of a negative number, try a different number: ");
			}
			printf ("\nsqrt(%lg) = %lg\n", operand, sqrt(operand));
			break;
		case 'l':
			while (operand < 0) {
				if (acceptVars)
					operand = getValidatedVariableInput("You can't take the logarithm of a negative number, try a different number: ");
				else 
					operand = getValidatedDouble("You can't take the logarithm of a negative number, try a different number: ");
			}
			printf("\nlog(%lg) = %lg\n", operand, log10(operand));
			break;
		case 'e':
			printf("\ne ^ %lg = %lg\n", operand, exp(operand));
			break;
		case 'c':
			printf("\nceiling(%lg) = %lg\n", operand, ceil(operand));
			break;
		case 'f':
			printf("\nfloor(%lg) = %lg\n", operand, floor(operand));
			break;
	}
	while (getchar() != '\n');
}

int main ( void ) {

	printf ("Welcome to my Command-Line Calculator\n");
	printf ("Version: 1.1\n");
	printf ("Date: November 9, 2020\n");

	while (1) {
		printf ("-----------------------------------------------------------\n");
		printf ("Select one of the following options:\n");
		printf ("B) - Binary Mathematical Operations, such as addition and subtraction.\n");
		printf ("U) - Unary Mathematical Operations, such as square root, and log.\n");
		printf ("A) - Binary and Unary Mathematical Operations, using variables.\n");
		printf ("V) - Define variables and assign them values.\n");
		printf ("E) - Exit\n");

		switch (getValidatedChar("", validOptions, ARRAY_SIZE(validOptions))) {
			case 'b': { // braces are needed to fix scope issues

				double operand1 = 0, operand2 = 0;
				char operation = '\n';

				operand1 = getValidatedDouble(floatingPointPrompt);
				operation = getValidatedChar(binaryOperationPrompt, validBinaryOperations, ARRAY_SIZE(validBinaryOperations));
				operand2 = getValidatedDouble(floatingPointPrompt);

				binaryMathOps(operand1, operation, operand2, 0);

				break;
			}
			case 'u': {
				
				double operand = 0;
				char operation = '\n';

				operand = getValidatedDouble(floatingPointPrompt);
				operation = getValidatedChar(unaryOperationPrompt, validUnaryOperations, ARRAY_SIZE(validUnaryOperations));

				unaryMathOps(operand, operation, 0);	

				break;
			}
			case 'a': {

				printf ("-----------------------------------------------------------\n");
				printf ("Select one of the following sub-options:\n");
				printf ("B) - Binary Mathematical Operations, such as addition and subtraction.\n");
				printf ("U) - Unary Mathematical Operations, such as square root, and log.\n");
				printf ("E) - Exit\n");

				switch (getValidatedChar("", validSubOptions, ARRAY_SIZE(validSubOptions))) {
					case 'b': {

						double operand1, operand2;
						char operation;

						operand1 = getValidatedVariableInput(varOrFloatingPointPrompt);
						operation = getValidatedChar(binaryOperationPrompt, validBinaryOperations, ARRAY_SIZE(validBinaryOperations));
						operand2 = getValidatedVariableInput(varOrFloatingPointPrompt);

						binaryMathOps(operand1, operation, operand2, 1);

						break;
					}
					case 'u': {
						
						double operand;
						char operation;

						operand = getValidatedVariableInput(varOrFloatingPointPrompt);
						operation = getValidatedChar(unaryOperationPrompt, validUnaryOperations, ARRAY_SIZE(validUnaryOperations));

						unaryMathOps(operand, operation, 1);

						break;
					}
				}
				break;
			}
			case 'v': {
				double num;
				char varName;

				varName = getValidatedChar(variableNamePrompt, validVariableNames, ARRAY_SIZE(validVariableNames));
				num =  getValidatedDouble(floatingPointPrompt);

				// assign to the appropriate varibale
				variables[varName - 'a'] = num;

				printf("%lg has been assigned to \"%c\"\n", num, varName);

				break;
			}
			case 'e': return 0;
		}
	}
}