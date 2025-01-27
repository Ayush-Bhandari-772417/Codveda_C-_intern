// C++ program to create a simple student management system using the concept of structure

#include <iostream>
#include <fstream>
#include <cstdlib> // For exit()
#include <limits>
#include <conio.h>
#include <windows.h>
using namespace std;

enum operation{                 // enumartes for operation of update and delete
    SUPDATE, SDELETE
};
typedef struct user{            // structure for students' information
    int id;
    char name[50];
    char address[50];
    char phone[20];
    char level[10];
    int enrolledYear;
    int completedYear;
    float gpa;
    char grade[3];
}Student;

void inputToFile(Student ch);
Student addStudent();
void getCursorPosition(int &row, int &col);
void setxy (int x, int y);
void showAllData();
void showIndividualData(Student st);
int inputStudentId(int Task);
void updateStudentInfo();
void deleteStudentInfo();
void searchStudent();

void inputToFile(Student ch){           	// function to write studednt info in file
    ofstream w("Record.txt", ios::app);
    if (!w)                                                     // handle erros if occured while opening file
    	cout << "Error opening file!" << endl;
    else {
        w.write((char*)&ch, sizeof(ch));        // write to file
        w.close();
    }
}

Student addStudent() {                      // function to take students' info
    Student s;                          // creates structure variable
    cout << "Enter ID of student :- ";
    cin >> s.id;
    cin.clear();
    fflush(stdin);
    cout << "Enter name of student :- ";
    cin.getline(s.name, 20);
    cin.clear();
    fflush(stdin);
    cout << "Enter address of student :- ";
    cin.getline(s.address, 20);
    cin.clear();
    fflush(stdin);
    cout << "Enter phone number :- ";
    cin.getline(s.phone, 20);
    cin.clear();
    fflush(stdin);
    cout << "Enter enrolled year :- ";
    cin >> s.enrolledYear;
    fflush(stdin);
    cout << "Enter graduated year :- ";
    cin >> s.completedYear;
    fflush(stdin);
    cout << "Enter GPA :- ";
    cin >> s.gpa;
    cin.clear();
    fflush(stdin);
    cout << "Enter obtained grade :- ";
    cin.getline(s.grade, 3);
    cin.clear();
    fflush(stdin);
    inputToFile(s);                     // calls function to keep record in file
    cout << "Successfully added student";
    return s;
}

void getCursorPosition(int &row, int &col) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        row = csbi.dwCursorPosition.Y; // Convert to 1-based index
        col = csbi.dwCursorPosition.X;
    } else {
        row = col = -1; // Handle error
    }
}

void setxy (int x, int y)		// set curosor in output console
{
    COORD c = {0, 0};
    c.X = x; c.Y = y; // Set X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void showAllData() {            // displays all data avilable in the database
    int i=0;
    Student a;
    cout << "\t\t\t Student Info" << endl;
    cout << " ID \t Name \t\t Address \t\t Phone number \t Enrolled year \t Graduated year  GPA \t Obtained grade " << endl;
    int row, col;
    getCursorPosition(row, col);
    ifstream r("Record.txt");
    r.seekg(0, ios::beg);
    while (r.read((char*)&a, sizeof(a))) {              // reads the entrfy untill end of file is encountered
        setxy(1, row+i);
        cout << a.id;
        setxy(7, row+i);
        cout << a.name;
        setxy(25, row+i);
        cout << a.address;
        setxy(50, row+i);
        cout << a.phone;
        setxy(67, row+i);
        cout << a.enrolledYear;
        setxy(85, row+i);
        cout << a.completedYear;
        setxy(97, row+i);
        cout << a.gpa;
        setxy(110, row+i);
        cout << a.grade << endl;
        i++;
    }
}

void showIndividualData(Student st) {                               // shows data of one person only but in detail
    cout << "ID : " << st.id << endl;
    cout << "Name : " << st.name << endl;
    cout << "Address : " << st.address << endl;
    cout << "Phone number : " << st.phone << endl;
    cout << "Enrolled year : " << st.enrolledYear << endl;
    cout << "Graduated year : " << st.enrolledYear << endl;
    cout << "GPA : " << st.gpa << endl;
    cout << "Obtained grade : " << st.grade << endl;
}

void searchStudent(){                               // function to allow search student by id
    int flag=0, id;
    Student stds;
    cout << "Enter the ID of student whose informtion is to be displayed: ";
    cin >> id;

	ifstream file("Record.txt");
	if (!file)
		cout << "Unable to open file";
	else {
        file.seekg(0, ios::beg);
        while (file.read((char*)&stds, sizeof(stds))) {         // loops untill EOF is encountered
            if (stds.id == id) {
                flag = 1;                   // flag to determined if student exists
                showIndividualData(stds);       // calls function to display detail info
                break;
            }
        }
        if(flag == 0)
            cout << "No data found";
    }
	file.close();
}

int inputStudentId(int Task) {          // asks student id
    int id = 0;
    switch (Task){
    case SUPDATE:                                   // for updating purpose
        cout << "\n\n\t\tEnter student id to update. ";
        break;
    case SDELETE:                                   // for deleting purpose
        cout << "\n\n\t\tEnter student id to delete. ";
        break;
    default:
        break;
    }
    cin >> id;          // allows user to enter id
    return id;
}

void updateStudentDetailsToFile(Student s, Student st, int ch){     // updates database
    Student stds;
    ifstream file("Record.txt");
    ofstream w("Temp.txt", ios::app);               // makes temporary file
    file.seekg(0, ios::beg);
	if (!file)
		cout << "Unable to open file for reading";
	else {
        file.seekg(0, ios::beg);
        while (file.read((char*)&stds, sizeof(stds))) {
            if (stds.id != s.id)
                w.write((char*)&stds, sizeof(stds));
        }
    }
	file.close();
    w.close();
	int status = remove("Record.txt");                          // deletes original file
	if (status != 0)
		perror("Error deleting student's database");
    status = rename("temp.txt", "Record.txt");                   // makes temporary file as original file
	if (status != 0)
		perror("Error while renaming");
}

void updateStudentInfo(){                                   // implements logic to update student info
    Student std, stds;
    int flag=0;
    int id = inputStudentId(SUPDATE);

	ifstream file("Record.txt");
	if (!file)
		cout << "Unable to open file";
	else {
        file.seekg(0, ios::beg);
        while (file.read((char*)&stds, sizeof(stds))) {
            if (stds.id == id) {                                // checks if student with given id exists or not
                flag = 1;
                showIndividualData(stds);
                break;
            }
        }
        file.close();
        if(flag == 0)
            cout << "No data found";
        if(flag == 0)
            cout << "\n\t\tThere is no student with giuven id";
        else{
            cout << "\n\n\t\t You can update the student info" << endl;
            std = addStudent();                                         // allows to enter new updates
            updateStudentDetailsToFile(stds, std, SUPDATE);         // calls functio to update database
        }
    }
    cout << "Successfully updated student info" << endl;
}

void deleteStudentInfo(){               // implements deletion of individual student's detail fron database
    Student std, stds;
    char ch;
    int flag=0;
    int id = inputStudentId(SDELETE);       // calls function to take student id for deletion

	ifstream file("Record.txt");
	if (!file)
		cout << "Unable to open file";
	else {
        file.seekg(0, ios::beg);
        while (file.read((char*)&stds, sizeof(stds))) {
            if (stds.id == id) {            // checks if the student with given id exists
                flag = 1;
                break;
            }
        }
        file.close();
        if(flag == 0)
            cout << "No data found";
        if(flag == 0)
            cout << "\n\t\tThere is no student with giuven id";
        else{
            cout << "\n\n\t\t You can delete this student info";
            showIndividualData(stds);
            cout << "Are you sure to delete this info (Y/N)? ";
            cin >> ch;         // asks for consent of deletion
            if(ch=='Y' || ch=='y'){
                updateStudentDetailsToFile(stds, std, SDELETE);     // calls function for deletion of information from database
                cout << "Successfully deleted !!!" << endl;
            }
            else
                cout << "You aborted deletion process ";
        }
    }
}

void deleteDatabase(){                      // deletes the whole database
	int status = remove("Record.txt");          // removes the database
	if (status != 0)                            // handles error
		perror("Error deleting student's database");
	else
		cout << "Student's database cleared" << endl;
}

int main() {
	int choice;
	
	char ch;
	while (true) {                                  // loops continuously
		system("cls");                                                      // clears output screen when starting each loop
		cout << "\t\t Welcome to Student Management System \n";
		cout << "\t 1. Add student information \n";
		cout << "\t 2. Display student information \n";
		cout << "\t 3. Search student information \n";
		cout << "\t 4. Update student information \n";
		cout << "\t 5. Delete individual student information \n";
		cout << "\t 6. Delete whole database \n";
		cout << "\t 7. Exit \n";
		while (true) {
			cout << "Enter your choice: ";
			cin >> choice;
			if (cin.fail()) {               // handles error while accepting user's input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter an integer value." << endl;
				continue;
			}
			break;
		}
        
		switch (choice) {                       // switch case to decide
			case 1: {
                addStudent();
				break;
			}
			case 2: {
                showAllData();
				break;
			}
			case 3: {
                searchStudent();
				break;
			}
			case 4: {
                updateStudentInfo();
				break;
			}
			case 5: {
				deleteStudentInfo();
				break;
			}
			case 6: {
                deleteDatabase();
				break;
			}
			case 7:
				cout << "Exiting program." << endl;
				exit(0);                                // exits the program only if correct decision is taken
			default:
				cout << "Invalid choice. Please try again." << endl;
				break;
		}
		getch();
	}
	return 0;
}