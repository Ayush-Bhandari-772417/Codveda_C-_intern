/* C++ Program to implement simple calculator 
The program uses factory method pattern to implement different simple mathematical calculations :-
								addition, subtraction, multiplication and division
Also, it uses file structures to store and view hihistory
*/

#include <iostream>
#include <fstream>
#include <cstdlib> // For exit()
#include <limits>
#include <conio.h>
using namespace std;

void viewhistory(){								// displays records of calculation previously carried out by reading from file
	ifstream file("Record.txt");				// opens file for reading
	if (!file)									// handles error
		cout << "Unable to open file";
	else {
		cout << "\n\t Your history is : \n";
		char ch;
		while (file.get(ch))					// get characters from file
			cout << ch;							// displays history
		cout << endl;
	}
	file.close();								// close the file
}

void deletehistory(){
	int status = remove("Record.txt");			// delete the history stored in file
	if (status != 0)
		perror("Error deleting history");		// displays error if any
	else
		cout << "History cleared" << endl;
}

class operation {								// cretes a base class
public:
	float x, y;
	virtual void input() {						// creates virtual function so that classes inherating the class could use to take input
		while (true) {
			cout << "Enter first number: ";
			cin >> x;
			if (cin.fail()) {					// handles input error
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a numeric value." << endl;
				continue;
			}
			break;
		}
		while (true) {
			cout << "Enter second number: ";
			cin >> y;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a numeric value." << endl;
				continue;
			}
			break;
		}
	}
	virtual float operate() {					// virtual function to implement the actual operation
		return 0.0f;
	}

	virtual void record(char ch){				// function to keep the track of history by using file
		ofstream w("Record.txt", ios::app);
		if (!w)
			cout << "Error opening file!" << endl;
		else {
			w << x << " " << ch << " " << y << " = " << operate() << endl;
			w.close();
		}
	}
};

class addition : public operation {				// class for performing addition that inherits the baase class
public:
	virtual float operate() override {			// owrriddes the function to perform addition
		return x + y;
	}
};

class subtraction : public operation {				// class for performing subtraction that inherits the baase class
public:
	virtual float operate() override {			// owrriddes the function to perform subtraction
		return x - y;
	}
};

class multiplication : public operation {				// class for performing multiplication that inherits the baase class
public:
	virtual float operate() override {			// owrriddes the function to perform multiplication
		return x * y;
	}
};

class division : public operation {				// class for performing division that inherits the baase class
public:
	virtual float operate() override {			// owrriddes the function to perform division
		if (y == 0) {																// handles  division by zero
			cout << "Error: Division by zero is not allowed." << endl;
			return std::numeric_limits<float>::infinity();							// returns infinity if tried to divide by zero
		}
		return x / y;
	}
};

class Factory {											// class to generate child class on the basis of operation that is intended to perform
public:
	operation* getFactory(char ch) {					// function for returning different class during run time
		switch (ch) {
			case '+':
				return new addition();
			case '-':
				return new subtraction();
			case '*':
				return new multiplication();
			case '/':
				return new division();
			default: {
				cout << "Invalid choice, returning null operation." << endl;
				return NULL;
			}
		}
	}
};

int main() {
	int choice;
	Factory *fac = new Factory();						// making instance of object for getting the respective class
	
	char ch;
	while (true) {										// loop for taking user choice after each operation
		system("cls");
		cout << "\t\t Welcome to Calculator \n";
		cout << "\t 1. Addition \n";
		cout << "\t 2. Subtraction \n";
		cout << "\t 3. Multiplication \n";
		cout << "\t 4. Division \n";
		cout << "\t 5. View history \n";
		cout << "\t 6. Delete history \n";
		cout << "\t 7. Exit \n";
		while (true) {
			cout << "Enter your choice: ";
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter an integer value." << endl;
				continue;
			}
			break;
		}
		
		operation *op = NULL;
		
		switch (choice) {								// switch case to call factory on the basis of user's choice
			case 1: {
				op = fac->getFactory('+');
				ch = '+';
				break;
			}
			case 2: {
				op = fac->getFactory('-');
				ch = '-';
				break;
			}
			case 3: {
				op = fac->getFactory('*');
				ch = '*';
				break;
			}
			case 4: {
				op = fac->getFactory('/');
				ch = '/';
				break;
			}
			case 5: {
				viewhistory();
				break;
			}
			case 6: {
				deletehistory();
				break;
			}
			case 7:
				cout << "Exiting program." << endl;
				exit(0);
			default:
				cout << "Invalid choice. Please try again." << endl;
				break;
		}
		if(op!=NULL){								// checks if the instance is created or not for the operation
			op->input();
			cout << "Result is: " << op->operate() << endl;
			op->record(ch);
		}
		cout << endl;
		cout << "Print any key to continue ...";
		getch();											// pause the screen after final output is shown
	}
	return 0;
}
