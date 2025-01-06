#include <iostream>
#include <cstdlib>
//#include <cstring> // For strlen, strcpy, and strcat

using namespace std;

const int SIZE=100;

char* reverse(const char* s1);
char* upper(const char* s1);
char* lower(const char* s1);
char* palindrome(const char* s1, const char* s2);
int length(const char* s1);
int no_of_letters(const char* s1);
int vowels(const char* s1);
int consonants(const char* s1);

int main() {
	char input[SIZE];
	cout << "Enter a string : ";
	cin.getline(input, SIZE);
	char* reversed = reverse(input);
	char* lowercase = lower(input);
	char* uppercase = upper(input);
	char* palindrome_check = palindrome(input, reversed);
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

char* lower(const char* s){
	int i=0;
	char* result = new char[length(s)];
	while(s[i] != '\0'){
		if(s[i]>=65 && s[i]<=90)
			result[i] = s[i] + 32;
		else
			result[i] = s[i];
		i++;
	}
	return result;
}

char* upper(const char* s){
	int i=0;
	char* result = new char[length(s)];
	while(s[i] != '\0'){
		if(s[i]>=97 && s[i]<=122)
			result[i] = s[i] - 32;
		else
			result[i] = s[i];
		i++;
	}
	return result;
}

char* reverse(const char* s1){
	char* result = new char[length(s1)];
	int l = length(s1)-1,i=0;
	while(s1[i] != '\0')
		result[i++] = s1[l--];
	return result;
}

char* palindrome(const char* s1, const char* s2){
	int flag=0, i=0;
	while(s1[i] != '\0'){
		if(s1[i] != s2[i]){
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
	int i=0;
	while(s1[i] != '\0')
		i++;
	return i;
}

int no_of_letters(const char* s){
	int c=0, i=0;
	while(s[i] != '\0'){
		if((s[i]>=65 && s[i]<=90)||(s[i]>=97 && s[i]<=122))
			c++;
		i++;
	}
	return c;
}

int vowels(const char* s1){
	int c=0, i=0;
	char* temp = lower(s1);
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
	return c;
}

int consonants(const char* s1){
	return (no_of_letters(s1)-vowels(s1));
}
