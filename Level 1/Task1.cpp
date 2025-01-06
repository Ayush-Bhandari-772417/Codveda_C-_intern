#include <iostream>
#include <fstream>
#include <cstdlib> // For exit()
#include <limits>
#include <conio.h>
using namespace std;

void viewhistory(){
	ifstream file("Record.txt");
	if (!file)
		cout << "Unable to open file";
	else {
		cout << "\n\t Your history is : \n";
		char ch;
		while (file.get(ch))
			cout << ch;
		cout << endl;
	}
	file.close();
}

void deletehistory(){
	int status = remove("Record.txt");
	if (status != 0)
		perror("Error deleting history");
	else
		cout << "History cleared" << endl;
}

class operation {
public:
	float x, y;
	virtual void input() {
		while (true) {
			cout << "Enter first number: ";
			cin >> x;
			if (cin.fail()) {
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
	virtual float operate() {
		return 0.0f;
	}
	virtual void record(char ch){
		ofstream w("Record.txt", ios::app);
		if (!w)
			cout << "Error opening file!" << endl;
		else {
			w << x << " " << ch << " " << y << " = " << operate() << endl;
			w.close();
		}
	}
};

class addition : public operation {
public:
	virtual float operate() override {
		return x + y;
	}
};

class subtraction : public operation {
public:
	virtual float operate() override {
		return x - y;
	}
};

class multiplication : public operation {
public:
	virtual float operate() override {
		return x * y;
	}
};

class division : public operation {
public:
	virtual float operate() override {
		if (y == 0) {
			cout << "Error: Division by zero is not allowed." << endl;
			return std::numeric_limits<float>::infinity();
		}
		return x / y;
	}
};

class Factory {
public:
	operation* getFactory(char ch) {
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
	Factory *fac = new Factory();
	
	char ch;
	while (true) {
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
		
		switch (choice) {
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
		if(op!=NULL){
			op->input();
			cout << "Result is: " << op->operate() << endl;
			op->record(ch);
		}
		cout << endl;
		cout << "Print any key to continue ...";
		getch();
	}
	return 0;
}
