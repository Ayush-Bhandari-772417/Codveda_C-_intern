#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
const char* path = "."; // Current directory.

struct dirent* viewDirectory() {
    
    DIR* dir = opendir(path);

    if (dir == NULL) {
        cerr << "Could not open directory.\n";
        return NULL;
    }

    cout << "Files in the current directory:\n";
    struct dirent* entry;
    struct stat fileStat;

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path and use stat to check if it's a regular file
        string fullPath = string(path) + "/" + entry->d_name;

        if (stat(fullPath.c_str(), &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            cout << entry->d_name << "\n";
        }
    }

    closedir(dir);
    return entry;
}

int createFile(){
    char filename[30];
    int flag=0;
    cout << "Enter filename you want to create : ";
    cin.ignore();
    cin.getline(filename,30);
    
    DIR* dir = opendir(path);
    struct dirent* entry;

    if (dir == NULL) {
        cerr << "Could not open directory. You cannot created file now. Try later !!!\n";
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            flag = 1;
            break;
        }
    }

    closedir(dir);
    
    if(flag==0){
		ofstream w(filename);
		if (!w)
			cout << "Error creating file !!!" << endl;
		else
			cout << "File created successfully !!!";
        w.close();
    }
    else
        cout << "File with given name exists in the directory. Try with different name.";	
}

bool fileExists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int writeIntoFile() {
    char filename[30];
    cout << "Enter filename to write into: ";
    cin.ignore(); // Clear input buffer
    cin.getline(filename, 30);

    if (!fileExists(filename)) {
        cout << "Error: File does not exist. Cannot write to a non-existent file. \n First create file with the given filename\n";
        return 0;
    }

    // Open the file in append mode
    ofstream w(filename, ios::app);
    if (!w) {
        cout << "Error opening file for writing!!!\n";
        return 0;
    }

    cout << "Enter text to write (Press Enter twice to save):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        w << line << endl;
    }
    w.close();
    cout << "Content written successfully!!!\n";
    return 1;
}


void display(){
    char filename[30];
    cout << "Enter the filename to display contents: ";
    cin.ignore(); // To ignore any leftover newline character in the input buffer
    cin.getline(filename, 30);

    if (!fileExists(filename)) {
        cout << "\nError: File does not exist.\n";
        return ;
    }
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file. File does not exist or cannot be accessed!" << endl;
        return;
    }

    cout << "\nContents of the file \"" << filename << "\":\n";
    cout << "----------------------------------------\n";

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    cout << "----------------------------------------\n";
    file.close();
    cout << "End of file.\n";
}

int modify(){
    char filename[30];
    cout << "Enter name of the file you want to modify : ";
    cin.ignore();
    cin.getline(filename, 30);

    vector<string> lines;
    
    if (!fileExists(filename)) {
        cout << "Error: File does not exist. Cannot modify a non-existent file. \n First create file with the given filename\n";
        return 0;
    }
    ifstream fileIn(filename);

    // Load the file content into a buffer
    if (!fileIn) {
        cout << "File not found! Creating a new one.\n";
        lines.push_back(""); // Start with an empty line if the file doesn't exist
    }
    else {
        string line;
        while (getline(fileIn, line))
            lines.push_back(line);
        fileIn.close();
    }

    // Display instructions
    cout << "Editing file: " << filename << "\n";
    cout << "Instructions:\n";
    cout << "Arrow keys to navigate, Enter to add a new line, Backspace to delete, Ctrl+S to save, and Ctrl+Q to exit without saving.\n";
    getch();

    // Initialize cursor position
    int row = 0, col = 0;
    bool running = true;
    bool saveFlag = false;

    while (running) {
        // Clear the console and display the content
        system("cls");
        for (size_t i = 0; i < lines.size(); ++i) {
            cout << lines[i] << "\n";
        }

        // Move the cursor to the current position
        cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";

        char ch = getch(); // Get a character without waiting for Enter
        
        if (ch == -32) { // Handle arrow keys (prefix -32 on Windows)
            ch = getch();
            switch (ch) {
                case 72:{ // Up
                    if (row > 0) row--;
                    if (col > (int)lines[row].size()) col = lines[row].size();
                    break;
                }
                case 80:{ // Down
                    if (row < (int)lines.size() - 1) row++;
                    if (col > (int)lines[row].size()) col = lines[row].size();
                    break;
                }
                case 75:{ // Left
                    if (col > 0) col--;
                    break;
                }
                case 77:{ // Right"
                    if (col < (int)lines[row].size()) col++;
                    break;
                }
            }
        }
        else if (ch == 8) { // Backspace
            if (col > 0) {
                lines[row].erase(col - 1, 1);
                col--;
            }
            else if (row > 0) {
                col = lines[row - 1].size();
                lines[row - 1] += lines[row];
                lines.erase(lines.begin() + row);
                row--;
            }
        }
        else if (ch == 13) { // Enter
            lines.insert(lines.begin() + row + 1, lines[row].substr(col));
            lines[row] = lines[row].substr(0, col);
            row++;
            col = 0;
        }
        else if (ch == 19) { // Ctrl+S to save
            ofstream fileOut(filename);
            for (size_t i = 0; i < lines.size(); ++i) {
                fileOut << lines[i] << "\n";
            }
            fileOut.close();
            saveFlag = true;
            cout << "\nFile saved successfully!\n";
            getch(); // Wait for user to press a key
        }
        else if (ch == 17) { // Ctrl+Q to quit
            running = false;
        }
        else { // Regular character input
            lines[row].insert(col, 1, ch);
            col++;
        }
    }

    // Exit message
    if (!saveFlag) {
        cout << "\nExiting without saving changes.\n";
    } else {
        cout << "\nChanges saved to file.\n";
    }
}

int eraseContent(){
    char filename[30];
    cout << "Enter name of the file you want to delete : ";
    cin.ignore();
    cin.getline(filename,30);
    
    if (!fileExists(filename)) {
        cout << "Error: File does not exist.\n";
        return 0;
    }
    ofstream w(filename);
    if (!w)
    	cout << "Error erasing the content !!!" << endl;
    else
    	cout << "Content of the file erased successfully !!!";
    w.close();
}

void deleteFile(){
    char filename[30];
    cout << "Enter name of the file you want to delete : ";
    cin.ignore();
    cin.getline(filename,30);
	int status = remove(filename);
	if (status != 0)
		perror("Error deleting file");
	else
		cout << "File deleted" << endl;
}

int main(){
    int choice;
	char ch;
	while (true) {
		system("cls");
		cout << "\t\t Welcome to Simple File System Simulation \n";
		cout << "\t 1. View files in current directory \n";
		cout << "\t 2. Create a file \n";
		cout << "\t 3. Write into a file \n";
		cout << "\t 4. Display contents of a file \n";
		cout << "\t 5. Modify file \n";
		cout << "\t 6. Erase contents of a file \n";
		cout << "\t 7. Delete filed \n";
		cout << "\t 8. Exit \n";
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
		
		switch (choice) {
			case 1: {
                system("cls");
                viewDirectory();
				break;
			}
			case 2: {
                system("cls");
				createFile();
				break;
			}
			case 3: {
                system("cls");
				writeIntoFile();
				break;
			}
            case 4:{
                system("cls");
                display();
                break;
            }
			case 5: {
                system("cls");
				modify();
				break;
			}
			case 6: {
                system("cls");
				eraseContent();
				break;
			}
			case 7: {
                system("cls");
				deleteFile();
				break;
			}
			case 8:
				cout << "Exiting program." << endl;
				exit(0);
			default:
				cout << "Invalid choice. Please try again." << endl;
				break;
		}
		cout << endl;
		cout << "Print any key to continue ...";
		getch();
	}
	return 0;
}