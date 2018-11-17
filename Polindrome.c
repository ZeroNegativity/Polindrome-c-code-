#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void writeFile(char fileName[], char ssData[], char oStringData[][50], //function which writes in the every row of the oString.txt
		int nrIOfileLines) {
	FILE *outputFile;
	outputFile = fopen(fileName, "a");
	int size = 0;
	if (outputFile == NULL) {
		printf("Can't open output file %s!\n", fileName); //if there no such file it outputs error
	}
	fprintf(outputFile, "%s\n", ssData);
	do {
		fprintf(outputFile, "%s", oStringData[size]);
		size++;
	} while (size < nrIOfileLines);
	fprintf(outputFile, "\n\n");  //here we output two blankspaces
	fclose(outputFile);
}
int isPalindrome(char str[]) {
	int first, last;    //here we take first and last characters of the string
	first = 0;
	int numStr = strlen(str);
	last = numStr - 1;
	do {
		if (str[first++] != str[last--]) { //here we compare these two strings and cheks every character
			return 0;     //if it returns "0" it is false
		}
	} while (last > first);
	return 1;           // if it is returns "1" it is true
}
char *getPalindrome(char str[]) {
	int x = isPalindrome(str);
	if (x == 1) { //if isPalindrome will be equal to the "0" it isnt a palindrome
		return "Is_Palindrome";
	} else {    //if isPalindrome will be equal to the "1" it is palindrome
		return "Not_Palindrome";
	}
}
int howManySubstrings(char subStr[], char str[]) {  //output the number og the substrings in the string
	int i = 0, j = 0;
	int numberOfoccurrences = 0;
	int y;
	int x;
	x = strlen(subStr);
	y = strlen(str);
	while (j < y) {      //loop which cheks every character and mathes it
		if (subStr[i] == str[j]) {
			j++;
			if (i == x - 1) {
				numberOfoccurrences++;
				i = 0;
			} else {
				i++;
			}
		} else {
			j++;
			i = 0;
		}
	}
	return numberOfoccurrences;
}
void checkSubstringPalindrome(char subStr[], char iStringData[][50],
		char oStringData[][50], int nrIOfileLines) {
	int x, size;
	char integer[100];
	x = 0;
	do {
		strcpy(oStringData[x], iStringData[x]);
		size = howManySubstrings(subStr, iStringData[x]);
		sprintf(integer, "%i", size); // function which converts the integer to the character
		strcat(oStringData[x], "\t");
		strcat(oStringData[x], integer);
		strcat(oStringData[x], "\t");
		strcat(oStringData[x], getPalindrome(iStringData[x]));
		strcat(oStringData[x], "\n");
		printf("%s\n", oStringData[x]);
		x++;
	} while (x < nrIOfileLines);
}
int countFileLines(char filename[]) {
	int c, count = 0; //c = it is the number of every character count = count the numbe of characters and lines
	FILE *stringFile;
	stringFile = fopen(filename, "r");
	if (stringFile == NULL) {
		printf("Can't open output file %s!\n", filename); //if there no such file it outputs error
	}
	do {
		c = fgetc(stringFile);
		if (c == '\n') {  //  this loop counts new line
			count++;
		}
	} while (c != EOF);
	fclose(stringFile);
	return count;
}
void readFile(char filename[], char twoDimArr[][50]) {
	FILE *stringFile;
	stringFile = fopen(filename, "r");
	int row, column;
	char c;
	if (stringFile == NULL) {          //if there no such file it outputs error
		printf("Can't open output file %s!\n", filename);
	}
	row = 0;
	column = 0;
	do {                                  //loop which cheks every character
		c = getc(stringFile);
		if (c == '\n') { //if the character is newline it goes to the next characters
			twoDimArr[row][column] = '\0';
			column = -1;
			row++;
		} else {
			twoDimArr[row][column] = c; // else we store the character in the array
		}
		if (c == EOF) {             //End of the characters then loop will stops
			break;
		}
		column++;
	} while (column < 50);
	fclose(stringFile);
}
int main() {
	int numI = countFileLines("iStrings.txt"); //stores number of lines in iStrings.txt
	int numSub = countFileLines("subStrings.txt"); // stores number of lines in subStrings.txt
	char instorage[numI][50]; // array which contains the information from the iStrings.txt
	char substorage[numSub][50]; // array which contains the information from the subStrings.txt
	char outstorage[50][50]; // array which contains the information from the oStrings.txt
	readFile("iStrings.txt", instorage);
	readFile("subStrings.txt", substorage);
	int x = 0;
	do {
		checkSubstringPalindrome(substorage[x], instorage, outstorage, numI); // fuction which cheks the array and then updates it
		writeFile("oStrings.txt", substorage[x], outstorage, numI); // function whichwrites the output data into the oString.txt
		x++;
	} while (x < numSub);
	return 0;
}
