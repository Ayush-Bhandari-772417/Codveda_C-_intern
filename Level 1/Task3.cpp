// C++ program for string  manipulation

#include <iostream>
#include <cstdlib>

using namespace std;

const int SIZE=100;

char* reverse(const char* s1);
char* upper(const char* s1);
char* lower(const char* s1);
char* palindrome(const char* s1);
int length(const char* s1);
int no_of_letters(const char* s1);
int vowels(const char* s1);
int consonants(const char* s1);

int main() {
	char input[SIZE];
	cout << "Enter a string : ";
	cin.getline(input, SIZE);				// allows a sentence to be entered
	char* reversed = reverse(input);
	char* lowercase = lower(input);
	char* uppercase = upper(input);
	char* palindrome_check = palindrome(input);
	int l = length(input);
	int letter_count = no_of_letters(input);
	int vow = vowels(input);
	int cons = consonants(input);
	
	cout << "                   Your input is: " << input << endl;
	cout << "Input string in all lowercase is: " << lowercase << endl;
	cout << "Input string in all uppercase is: " << uppercase << endl;
	cout << "         Length of your input is: " << l << endl;
	cout << "              Reversed string is: " << reversed << endl;
	cout << "      Is input string palindrome? " << palindrome_check << endl;
	cout << "   No. of letters in the string = " << letter_count << endl;
	cout << "                  No. of vowels = " << vow << endl;
	cout << "              No. of consonants = " << cons << endl;
}

char* lower(const char* s){										// change input to lowercase
	int i=0;
	char* result = new char[length(s)];
	while(s[i] != '\0'){						// loops untill the end of string which is signified by the character '\0'
		if(s[i]>=65 && s[i]<=90)								// cheecks whether a character is in uppercase
			result[i] = s[i] + 32;								// logic to convert uppercase into lowercase
		else
			result[i] = s[i];
		i++;
	}
	return result;
}

char* upper(const char* s){										// change input to uppercase
	int i=0;
	char* result = new char[length(s)];
	while(s[i] != '\0'){
		if(s[i]>=97 && s[i]<=122)								// cheecks whether a character is in lowercase
			result[i] = s[i] - 32;								// logic to convert uppercase into lowercase
		else
			result[i] = s[i];
		i++;
	}
	return result;
}

char* reverse(const char* s1){
	char* result = new char[length(s1)];
	int l = length(s1)-1,i=0;
	while(s1[i] != '\0')							// looping till the end of the input
		result[i++] = s1[l--];						// assign character by character to the new variable in reverse order
	result[i] = '\0';
	return result;
}

char* palindrome(const char* s1){		// checks wether input is palindrome
	char* s2=reverse(s1);				// reverse string
	int flag=0, i=0;
	while(s1[i] != '\0'){				// loop throughout the string character by character
		if(s1[i] != s2[i]){				// check if the correspondance are same or not and sgnals if there is difference
			flag = 1;
			break;
		}
		i++;
	}
	if(flag == 1)
		return "No";
	else
		return "Yes";
}

int length(const char* s1){
	int i=0;							// counter variable to count the string length
	while(s1[i] != '\0')
		i++;							// increment in count
	return i;
}

int no_of_letters(const char* s){			// counts no. of letters
	int c=0, i=0;
	while(s[i] != '\0'){
		if((s[i]>=65 && s[i]<=90)||(s[i]>=97 && s[i]<=122))		// checks for letters
			c++;
		i++;
	}
	return c;			// return total count
}

int vowels(const char* s1){					// count no. of vowels
	int c=0, i=0;
	char* temp = lower(s1);			// lowers all the input
	while(s1[i] != '\0'){
		switch (temp[i]){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				c++;
				break;
			default:
				break;
		}
		i++;
	}
	return c;			// returns count
}

int consonants(const char* s1){				// count no. of consonants
	return (no_of_letters(s1)-vowels(s1));			// calculates by subtracting no. of vowels from total no. of letters
}
