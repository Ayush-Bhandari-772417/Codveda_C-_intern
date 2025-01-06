#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

int no_of_chances = 5;

void information(int x, int y){
	if(abs(x-y)<=10)
		cout << "You are too close to the number." << endl;
	else if((x-y)>100)
		cout << "Your guess is too high." << endl;
	else if((x-y)<100)
		cout << "Your guess is too low." << endl;
	else
		cout << "Your guess is around the number." << endl;
}

int main(){
	srand(time(0));
	int num = rand();
//	cout << num;
	int guess, flag=0;
	cout << "\n\t *** Welcome to number guessing game ***";
	cout << "\n______________________________________________________";
	cout << "\n Instruction";
	cout << "\n------------------------------------------------------";
	cout << "\n You need to guess a number." << endl << " You have 5 chances." << endl
		 << " Within 5 chances, you need to guess a correct number." << endl
		 << " Otherwise, you will loose the game" <<"\n______________________________________________________";
	for(int i=1; i<=no_of_chances; i++){
		cout << "\n\n Guess a number \n\t Chance " << i << " off " << no_of_chances << " : ";
		while (true) {
			cin >> guess;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You didn't enter an integer. Please enter a number as the chance " << i << " " <<endl;
				continue;
			}
			break;
		}
		if(num == guess){
			flag = 1;
			break;
		}
		information(guess, num);
	}
	if(num == guess){
		cout << "\n\n\t You correctly guessed the number." << endl << "\n\t    You won the game !!! \n";
	}
	else{
		cout << "\n\n\t You lost the game. The number was " << num << "\n\t    Better luck next time !!! \n";
	}
}
