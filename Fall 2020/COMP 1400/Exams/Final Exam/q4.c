// Author: Isaac Kilbourne
// Name: q4.c
// Date: Dec 12, 2020
/** You can run this code online at https://repl.it/@voidvenom/Question-4 **/

#include <stdio.h>

// A valid password must contain at least one lowercase letter, one uppercase letter, and at least one digit.
// Also, the length of the password must not be less than 8 characters. In addition, the valid password should
// not contain any character from your last name and any digit from your student ID.
// Write a C function that gets a password as the first parameter, your last name as the second parameter,
// and your student ID as the third parameter, and returns 1 if it is a valid password and 0 otherwise.
// Then write a C program that receives a password from the user and prints out a proper message.

#define STUDENT_ID "110043640"
#define LAST_NAME "Kilbourne"

int isValid(char passcode[], char lastName[], char studentID[]);

int main(void) {

	printf("Please enter a password: ");

	char pass[1000];
	scanf("%1000s", pass);

	if (isValid(pass, LAST_NAME, STUDENT_ID))
		puts("That's a valid password!");
	else
		puts("That's not a valid password!");
}

int isValid(char passcode[], char lastName[], char studentID[]) {
	// count password length
	int passLen;
	for (passLen = 0; passcode[passLen] != '\0'; passLen++);

	// count lastName length
	int lastLen;
	for (lastLen = 0; lastName[lastLen] != '\0'; lastLen++);

	// count sID length
	int sidLen;
	for (sidLen = 0; studentID[sidLen] != '\0'; sidLen++);

	if (passLen < 8)
		return 0; // too short!

	/*
	 * Criteria (other than length):
	 * at least one uppercase
	 * at least one lowercase
	 * at least one digit
	 * no digits from student ID (returns automatically when failed)
	 * no characters from last name (returns automatically when failed)
	 */

	// these represents states for each of the character criteria
	int uppercase = 0;
	int lowercase = 0;
	int digit = 0;

	// not the most efficient strategy, but it's good enough
	for (int i = 0; i < passLen; i++) {
		char c = passcode[i];

		// is uppercase
		if ('A' <= c && c <= 'Z')
			uppercase = 1;

		// is lowercase
		else if ('a' <= c && c <= 'z')
			lowercase = 1;

		// is digit
		else if ('0' <= c && c <= '9') {
			digit = 1;
			for (int x = 0; x < sidLen; x++) {
				if (c == studentID[x])
					return 0; // digit in student ID
			}
		}

		for (int x = 0; x < lastLen; x++) {
			if (c == lastName[x])
				return 0;
		}
	}

	// sums to 5 if all valid. Else integer division rounds to 0
	return (uppercase + lowercase + digit) / 3; 
}