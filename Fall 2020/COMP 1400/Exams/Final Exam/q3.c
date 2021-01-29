// Author: Isaac Kilbourne
// Name: q3.c
// Date: Dec 12, 2020
/** You can run this code online at https://repl.it/@voidvenom/Question-3 **/

#include <stdio.h>

// a) Write a C function, append, that receives a string as input and (15 marks)
// 	• Creates a new string by adding your first name to the end of the string parameter
// 	• Prints out the new string.
// 	• For example, if the input string is "FinalExamCS2020", and the name is " John", the function will
//    print out "FinalExamCS2020John".
void append(char str[]);

// b) Write a C function, replace, that receives a string and two integer numbers (starting and ending points)
//    as input and (15 marks)
// 		• Creates a new string from the string parameter by replacing the characters within the starting to the
// 	      ending points with your name in this new string, and
//  	• Prints out the new string.
//  	• For example, if the input string is "FinalExamCS2020", the start point is 9, the endpoint is 10, and
//    	  the name is " John", the function will print out "FinalExamJohn2020".
void replace(char str[], int start, int end);

// c) Write a C program that gets two strings, a source, and a keyword, from a user and searches the keyword
//    in the source string as follows: (15 marks)
// 	• First, the program prompts a message and receives the source string from the user
// 	• Second, the program shows another message and gets the keyword string
// 	• Third, the program conducts the search and shows the result by a proper message as follows:
// 		o If the keyword does not exist in the source string, prints out a proper message and calls the
//  	  append function you have already developed in part a.
// 		o If the keyword exists in the source string, prints out a proper message and calls the replace
//  	  function you have already developed in part b.
// 		o Note: The source string and the starting and ending positions of the keyword inside the
//  	  source string are the three arguments in this function call. For example, if the input string is
//  	  "FinalExamCS2020", and the keyword is “CS”, the start point is 9, and the endpoint is 10

int main(void) {

	char source[61] = "";
	printf("Please input the string to search: ");
	scanf("%60s", source);

	char key[15] = "";
	printf("Please input the string to find: ");
	scanf("%15s", key);

	int srcLen;
	for (srcLen = 0; source[srcLen] != '\0'; srcLen++);

	int keyLen;
	for (keyLen = 0; key[keyLen] != '\0'; keyLen++);
	
	int startIndex, match = 0;
	for (startIndex = 0; startIndex <= srcLen - keyLen; startIndex++) {
		for (int x = 0; x < keyLen; x++) {
			match = 1;
			if (source[startIndex + x] != key[x]) {
				match = 0;
				break;
			}
		}
		if (match)
			break;
	}

	puts("**************************");

	if (match) {
		puts("The key exists in the string.");
		printf("The new string is: ");
		replace(source, startIndex, startIndex + keyLen);
	} else {
		puts("The key did not exist in the string.");
		printf("The new string is: ");
		append(source);
	}
}

void append(char str[]) {
	printf("%sIsaac\n", str); // idk if this is cheating or not.

	// !!!!! If the above is considered cheating, uncomment this code. !!!!!

	/** int len; // custom strlen implementation
	for (len = 0; str[len] != '\0' ; len++);

	char newString[len + 6];
	char ap[] = "Isaac";
	for (int i = 0; i <= len + 6; i++) {
		if (i < len)
			newString[i] = str[i];
		else
			newString[i] = ap[i - len];
	}
	printf("%s\n", newString); **/
}

void replace(char str[], int start, int end) {

	// strlen isn't allowed, we have to implement it ourselves
	int len;
	for (len = 0; str[len] != '\0' ; len++);

	// lower bounds checking
	start = (start < 0) ? 0 : start; // make sure start is positive
	end = (end < 0) ? 0 : end;

	// upper bounds checking
	start = (start > len) ? len : start;
	end = (end > len) ? len : end;

	if (start > end) {
		int temp = end;
		end = start;
		start = temp;
	}

	char newString[len - (end-start) + 5];
	char name[] = "Isaac";

	for (int i = 0; i < start; i++) {
		newString[i] = str[i];
	}
	for (int i = 0; i < 5; i++) {
		newString[i + start] = name[i];
	}
	for (int i = end; i < len; i++) {
		newString[i - end + start + 5] = str[i]; 
	}
	newString[len - (end-start) + 5] = '\0';

	printf("%s\n", newString);
}