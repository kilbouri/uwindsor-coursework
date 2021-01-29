// Author: Isaac Kilbourne
// Name: clc_v3.c
// Date: November 28, 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/** ==========================================================================
 * Ok, a couple things to mention before you start reading this code...
 * 
 * 1. YES, I did overengineer it.
 * 2. YES, I did use things that we weren't taught.
 * 3. YES, I still hope to get full marks for this assignment.
 * 4. YES, COMP 1400 isn't really challenging me so I do more than I probably need to.
 * 
 * With that out of the way... have fun and sorry in advance.
 * - Isaac Kilbourne
 * ===========================================================================
 */

/**
 * ===========================================================================
 *                             CUSTOM TYPES
 * ===========================================================================
 */
typedef struct { char opString[1024]; double value; } MemoryObject;
typedef struct StackElement { MemoryObject data; struct StackElement* next; } StackElement; 
typedef struct { int stackSize; StackElement* head; } Stack;

/**
 * ===========================================================================
 *                          FUNCTION PROTOTYPES
 * ===========================================================================
 */
double getValidatedVariable(const char* prompt);
double getValidatedDouble(const char* prompt);
int getValidatedIndex(const char* prompt, int max);
char getValidatedChar(const char* prompt, const char* validChars);
char getMainOption();
char getSubOption();

MemoryObject binaryMathOps(double operand1, char operation, double operand2, int acceptVars);
MemoryObject unaryMathOps(double operand, char operation, int acceptVars); 	
MemoryObject advancedOps(char subOperation);
MemoryObject assignVariable(char varName, double varValue);
void showMemory(Stack memoryStack);
void clearMemory(Stack* memoryStack);
void exitCalculator(Stack* memoryStack);

void printWelcomeMessage();
void printLineBreak();
void printSelectHeader();

Stack newStack();
void stackPush(Stack* stack, MemoryObject data);
MemoryObject stackPop(Stack* stack);
MemoryObject getStackIndex(Stack* stack, int index);

void stackPrint(Stack* stack);
void stackElementPrint(StackElement* element);
void memoryObjectPrint(MemoryObject obj);

/**
 * ===========================================================================
 *                       GLOBAL VARIABLES/CONSTANTS
 * ===========================================================================
 */
double variables[] = { 0, 0, 0, 0, 0 }; // define 5 variables

#if defined _WIN32 // defined on Windows 32- or 64-bit.
#define SUCCESS ""
#define ERROR   ""				// Standard ANSI color codes don't work, so
#define OPTION  ""				// just define empty strings.
#define RESET   ""

#elif defined __unix__ || defined __linux__ // defined on everything that isn't Windows, it seems
#define SUCCESS	"\033[0;32m"	// green for outputs
#define ERROR	"\033[1;31m"	// red for invalid inputs
#define OPTION  "\033[1;36m"	// blue for options	
#define RESET	"\033[0m"		// RESET to default
#endif

#define BINARY_OPS		"+-*/%pxi"
#define UNARY_OPS		"slecf"
#define VARIABLE_NAMES	"abcde"

#define DECIMAL_PLACES  8

int main ( void ) {

	/**
	 * Yes, the assignment does say I must store results in an array.
	 * The "Stack" datastructure, as I've implemented it, is similar to
	 * a dynamic-sized array.
	 */
	Stack memory = newStack(); // define an empty linked list

	printWelcomeMessage();

	while (1) {
		// Print options list
		printLineBreak();
		printSelectHeader();

		char option = getMainOption();
		printLineBreak();

		MemoryObject thisOp;
		switch (option) {
			case 'B': {}
				double operand1 = getValidatedDouble(NULL);
				char binaryOp = getValidatedChar(NULL, BINARY_OPS);
				double operand2 = getValidatedDouble(NULL);

				thisOp = binaryMathOps(operand1, binaryOp, operand2, 0);
				break;

			case 'U': {}
				double operand = getValidatedDouble(NULL);
				char unaryOp = getValidatedChar(NULL, UNARY_OPS);

				thisOp = unaryMathOps(operand, unaryOp, 0);	
				break;

			case 'A': {}

				printSelectHeader();

				char subOption = getSubOption();
				printLineBreak();

				thisOp = advancedOps(subOption);

				break;

			case 'M': {}
				showMemory(memory);
				continue;

			case 'R': {}
				clearMemory(&memory);
				continue;

			case 'V': {}
				char varName = getValidatedChar(NULL, VARIABLE_NAMES);
				double num =  getValidatedDouble(NULL);

				thisOp = assignVariable(varName, num);
				break;

			case 'E': {}
				exitCalculator(&memory);
				continue;
		}

		stackPush(&memory, thisOp);
	}
}

/**
 * ===========================================================================
 *                              INPUT FUNCTIONS
 * ===========================================================================
 */

/**
 * Gets a variable OR a number from the user. In the case of a variable,
 * the value of said variable will be returned. Does not prevent INF or
 * undefined operations such as dividing by 0. Prints default prompt if
 * prompt is NULL.
 */
double getValidatedVariable(const char* prompt) {

	if (prompt == NULL)
		printf ("Please input a number or variable (a letter between " OPTION "'a'" RESET " and " OPTION "'e'" RESET "): ");
	else
		printf("%s", prompt);
	
	double returnValue;

	while (1) {
		if (scanf (" %lg", &returnValue))
			break;

		char firstChar = toupper(getchar());

		if ('A' <= firstChar && firstChar <= 'E') {
			returnValue = variables[firstChar - 'A'];
			break;
		}
		printf (ERROR "Invalid, please try again: " RESET);
		while (getchar() != '\n');
	}

	while (getchar() != '\n');
	return returnValue;
}

/**
 * Gets a single number in double precision from the user.
 * If prompt is NULL, then prints a default message.
 */
double getValidatedDouble(const char* prompt) {

	if (prompt == NULL)
		printf ("Please enter a number: ");
	else
		printf ("%s", prompt);

	double returnValue;
	while (!scanf(" %lg", &returnValue)) {
		printf (ERROR "Invalid, please try again: " RESET);
		while (getchar() != '\n');
	}

	while (getchar() != '\n');
	return returnValue;
}

/**
 * Returns a positive integer if an index is entered,
 * -1 if 0 (print whole memory) is entered, or -2 if the user enters 'e' to exit.
 * 
 * Not overly pleased about having such a single-use function in
 * my program, but as of the time I am writing this, I haven't thought
 * of a better implementation of this functionality.
 */
int getValidatedIndex(const char* prompt, int max) {
	if (prompt == NULL)
		printf ("Please enter a number: ");
	else
		printf ("%s", prompt);

	int returnValue;
	while (!scanf(" %d", &returnValue) || 0 > returnValue || returnValue > max ) {

		char c = toupper(getchar());
		if (c == 'E')
			return -2;
		
		if (c == '\n')
			continue; // end of buffer, we don't need to clear
		
		printf (ERROR "Invalid, please try again: " RESET);
		while (getchar() != '\n');
	}

	while (getchar() != '\n');
	return returnValue - 1;
}

/**
 * Gets a valid character from the user, using a list of characters to check
 * validity.
 */
char getValidatedChar(const char* prompt, const char* validChars) {

	int len = strlen(validChars);
	
	if (prompt == NULL) {
		printf ("Please select an option (");

		for (int i = 0; i < len - 1; i++) {
			printf (OPTION "%c" RESET", ", toupper(validChars[i]));
		}
		printf (OPTION"%c" RESET "): ", toupper(validChars[len - 1]));
	} else {
		printf("%s", prompt);
	}

	while (1) {
		char character = toupper(getchar());

		if (character == '\n')
			continue;
		
		for (int i = 0; i < len; i++) {
			if (toupper(validChars[i]) == character) {
				while (getchar() != '\n');
				return character;
			}
		}
		while (getchar() != '\n');
		printf (ERROR "Invalid, please try again: " RESET);
	}
}

/**
 * Literally just prints the main menu options and calls
 * getValidatedChar() with a list of menu options.
 */
char getMainOption() {
	
	puts(OPTION "B" RESET " - Binary Mathematical Operations, such as addition and subtraction.");
	puts(OPTION "U" RESET " - Unary Mathematical Operations, such as square root, and log.");
	puts(OPTION "A" RESET " - Binary and Unary Mathematical Operations, using variables.");
	puts(OPTION "M" RESET " - View the calculator's memory.");
	puts(OPTION "R" RESET " - Reset the calculator's memory.");
	puts(OPTION "V" RESET " - Define variables and assign them values.");
	puts(OPTION "E" RESET " - Exit");
	
	return getValidatedChar("", "buamrve");
}

/**
 * Literally just prints the submenu options and calls
 * getValidatedChar() with a list of submenu options.
 */
char getSubOption() {

	puts(OPTION "B" RESET" - Binary Mathematical Operations, such as addition and subtraction.");
	puts(OPTION "U" RESET" - Unary Mathematical Operations, such as square root, and log.");
	puts(OPTION "E" RESET" - Exit");
	
	return getValidatedChar("", "bue");
}

/**
 * ===========================================================================
 *                            CALCULATOR FUNCTIONS
 * ===========================================================================
 */

/**
 * Runs the binary calculation(s) using the provided operands and operation.
 * In the case of invalid arguments, "acceptVars" indicates whether to call 
 * getValidatedDouble() or getValidatedVariable()
 */
MemoryObject binaryMathOps(double operand1, char operation, double operand2, int acceptVars) {
	
	MemoryObject opMemory = { };

	switch (operation) {
		case '+': {}
			opMemory.value = operand1 + operand2;
			break;
		
		case '-': {}
			opMemory.value = operand1 - operand2;
			break;
		
		case '*': {}
			opMemory.value = operand1 * operand2;
			break;
		
		case '/': {}
			while (!operand2) {
				char errorString[100] = ERROR "You can't divide by zero! Please try a different number: " RESET;

				if (acceptVars)
					operand2 = getValidatedVariable(errorString);
				else
					operand2 = getValidatedDouble(errorString);
			}
			opMemory.value = operand1 / operand2;
			break;

		case '%': {}
			opMemory.value = remainder(operand1, operand2);
			break;
		
		case 'P': {}
			opMemory.value = pow(operand1, operand2);
			sprintf (opMemory.opString, "%.*lg ^ %.*lg", DECIMAL_PLACES, operand1, DECIMAL_PLACES, operand2);

			printf(SUCCESS "%s = %.*lg\n" RESET, opMemory.opString, DECIMAL_PLACES, opMemory.value);
			return opMemory;
		
		case 'X': {}
			opMemory.value = (operand1 > operand2) ? operand1 : operand2;
			sprintf (opMemory.opString, "max(%.*lg, %.*lg)", DECIMAL_PLACES, operand1, DECIMAL_PLACES, operand2);
			
			printf(SUCCESS "%s = %.*lg\n" RESET, opMemory.opString, DECIMAL_PLACES, opMemory.value);
			return opMemory;
		
		case 'I': {}
			opMemory.value = (operand1 < operand2) ? operand1 : operand2;
			sprintf (opMemory.opString, "min(%.*lg, %.*lg)", DECIMAL_PLACES, operand1, DECIMAL_PLACES, operand2);

			printf(SUCCESS "%s = %.*lg\n" RESET, opMemory.opString, DECIMAL_PLACES, opMemory.value);
			return opMemory;

	}

	sprintf (opMemory.opString, "%.*lg %c %.*lg", DECIMAL_PLACES, operand1, operation, DECIMAL_PLACES, operand2);
	printf (SUCCESS "%s = %.*lg" RESET "\n", opMemory.opString, DECIMAL_PLACES, opMemory.value);

	return opMemory;
}

/**
 * Runs the unary calculation(s) using the provided operands and operation.
 * In the case of invalid arguments, "acceptVars" indicates whether to call 
 * getValidatedDouble() or getValidatedVariable()
 */
MemoryObject unaryMathOps(double operand, char operation, int acceptVars) {

	MemoryObject opMemory = { };
	switch (operation) {
		case 'S': {}
			while (operand < 0) {
				char errorString[100] = ERROR "You can't divide by zero! Please try a different number: " RESET;

				if (acceptVars)
					operand = getValidatedVariable(errorString);
				else
					operand = getValidatedDouble(errorString);
			}
			opMemory.value = sqrt(operand);
			sprintf (opMemory.opString, "sqrt(%.*lg)", DECIMAL_PLACES, operand);
			break;
		
		case 'L': {}
			while (operand < 0) {
				char errorString[100] = ERROR "You can't divide by zero! Please try a different number: " RESET;

				if (acceptVars)
					operand = getValidatedVariable(errorString);
				else
					operand = getValidatedDouble(errorString);
			}
			opMemory.value = log10(operand);
			sprintf (opMemory.opString, "log(%.*lg)", DECIMAL_PLACES, operand);
			break;
		
		case 'E': {}
			opMemory.value = exp(operand);
			sprintf (opMemory.opString, "e ^ %.*lg", DECIMAL_PLACES, operand);
			break;
		
		case 'C': {}
			opMemory.value = ceil(operand);
			sprintf (opMemory.opString, "ceiling(%.*lg)", DECIMAL_PLACES, operand);
			break;
		
		case 'F': {}
			opMemory.value = floor(operand);
			sprintf (opMemory.opString, "floor(%.*lg)", DECIMAL_PLACES, operand);
			break;
	}

	printf(SUCCESS "%s = %.*lg" RESET "\n", opMemory.opString, DECIMAL_PLACES, opMemory.value);
	return opMemory;
}

/**
 * Just calls the appropriate functions for advanced operations
 */
MemoryObject advancedOps(char subOption) {
	switch (subOption) {
		case 'B': {}
			double operand1 = getValidatedVariable(NULL);
			char binaryOp = getValidatedChar(NULL, BINARY_OPS);
			double operand2 = getValidatedVariable(NULL);

			return binaryMathOps(operand1, binaryOp, operand2, 1);
		case 'U': {}
			double operand = getValidatedVariable(NULL);
			char unaryOp = getValidatedChar(NULL, UNARY_OPS);

			return unaryMathOps(operand, unaryOp, 1);
	}
	return (MemoryObject) { };
}

/**
 * Assigns "varValue" to the approperiate variable
 */
MemoryObject assignVariable(char varName, double varValue) {

	MemoryObject opMemory = { };
	opMemory.value = varValue;

	variables[varName - 'A'] = varValue;
	sprintf (opMemory.opString, "%.*lg -> %c", DECIMAL_PLACES, varValue, toupper(varName));

	printf(SUCCESS "%s" RESET "\n", opMemory.opString);

	return opMemory;
}

/**
 * Presents the user with the count of numbers, then waits for either a
 * number (memory index) or e (return to menu)
 */
void showMemory(Stack memoryStack) {

	if (memoryStack.stackSize == 0) {
		puts (ERROR "There are no previous calculations to show." RESET);
		return;
	}
	
	if (memoryStack.stackSize == 1)
		puts("There is 1 previous calculation.\n");
	else 
		printf("There are %d previous calculations.\n\n", memoryStack.stackSize);

	while (1) {

		puts  ("Please select one of the following: ");
		puts  (OPTION "0" RESET " - View the entire operation history.");
		printf(OPTION "1 to %d" RESET " - View a previous calculation. ", memoryStack.stackSize);
		printf("(" OPTION "1" RESET " being most recent, " OPTION "%d" RESET " being first)\n", memoryStack.stackSize);
		puts  (OPTION "E" RESET " - Exit back to main menu.");

		int index = getValidatedIndex("", memoryStack.stackSize);
		if (index == -2) {
			puts (SUCCESS "Exiting to main menu..." RESET);
			return;
		}

		puts("");
		if (index == -1) {
			stackPrint(&memoryStack);
		} else {
			MemoryObject e = getStackIndex(&memoryStack, index);
			memoryObjectPrint(e);
		}
		printLineBreak();
	}
}

/**
 * Clears the provided Stack, then tells the user how many entries
 * were deleted.
 */
void clearMemory(Stack* memoryStack) {

	if (!memoryStack -> stackSize) {
		puts(ERROR "There is no memory to clear." RESET);
		return;
	}

	int deleted = 0;
	while (memoryStack -> stackSize != 0) {
		stackPop(memoryStack);
		deleted++;
	}

	if (deleted == 1)
		puts(SUCCESS "1" RESET " item was cleared from memory.");
	else
		printf(SUCCESS "%d" RESET " items were cleared from memory.\n", deleted);

}

/**
 * Frees the memory taken up by the memory stack, then calls exit(0)
 */
void exitCalculator(Stack* memoryStack) {

	while (memoryStack -> stackSize != 0) {
		stackPop(memoryStack);
	}

	printf (SUCCESS "Thank you for using the calculator.\n" RESET);
	exit(0);
}

/**
 * ===========================================================================
 *                         UTILITY OUTPUT FUNCTIONS
 * ===========================================================================
 */

void printWelcomeMessage() {
	puts(
		"Welcome to my Command-Line Calculator\n"
		"Version: 2.0\n"
		"Developer: Isaac Kilbourne\n"
		"Date: November 22, 2020"
	);
}
void printLineBreak() {
	puts("\n----------------------------------------------------------------------\n");
}
void printSelectHeader() {
	puts("Please select one of the following option(s): ");
}

/**
 * Pretty-prints the entire Stack
 */
void stackPrint(Stack* stack) {

	StackElement* current = stack -> head;
	int i = 1;

	while (current != NULL) {
		printf ("[ %d ]  ", i++);
		stackElementPrint(current);
		current = current -> next;
	}
}

/**
 * Pretty-prints the provided StackElement
 */
void stackElementPrint(StackElement* element) {
	char* opString = element -> data.opString;
	double result = element -> data.value;
	printf("[ " SUCCESS "Operation: %s" RESET " | " SUCCESS "Result: %lg" RESET " ]\n", opString, result);
}

/**
 * Pretty-prints the provided MemoryObject
 */
void memoryObjectPrint(MemoryObject obj) {
	stackElementPrint(&((StackElement) {obj, NULL}));
}


/**
 * ===========================================================================
 *                         LINKED LIST FUNCTIONS
 * ===========================================================================
 */
 /**
  * Returns an empty Stack
  */
Stack newStack() {
	return (Stack) { 0, NULL };
}

/**
 * Pushes the provided MemoryObject onto the stack
 */
void stackPush(Stack* stack, MemoryObject data) {
	StackElement* newElement = (StackElement*) malloc(sizeof(StackElement));

	newElement -> data = data;
	newElement -> next = stack -> head;

	stack -> head = newElement;
	stack -> stackSize++;
}

/**
 * Pops a MemoryObject off of the stack
 */
MemoryObject stackPop(Stack* stack) {

	StackElement* popped = stack -> head;
	MemoryObject data = popped -> data;

	stack -> head = popped -> next;

	// clean up memory and decrement stack size
	free(popped);
	stack -> stackSize--;

	return data; 

}

/**
 * Returns the MemoryObject at the specified index from the head
 */
MemoryObject getStackIndex(Stack* s, int index) {

	StackElement* current = s -> head;
	int ind = 0;

	while (current != NULL && ind++ < index)
		current = current -> next;

	return current -> data;
}