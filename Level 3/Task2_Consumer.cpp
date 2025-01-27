// C++ program to handle consumer side of producer-consumer problem using semaphore and mutex

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <Windows.h>

using namespace std;

#define BUFFER_SIZE 5
#define FILENAME "buffer.txt"
#define SEM_MUTEX L"Global\\sem_mutex" 
#define SEM_FULL L"Global\\sem_full"
#define SEM_EMPTY L"Global\\sem_empty"

// Semaphore handles
HANDLE mutex, full, empty;

void* consume(void* arg) {
    string item;
    while (true) {
        // Wait for a filled slot in the buffer
        WaitForSingleObject(full, INFINITE); // Wait if buffer is empty

        // Lock the buffer
        WaitForSingleObject(mutex, INFINITE);

        // Read and consume the first item from the buffer
        ifstream buffer_file(FILENAME);
        ofstream temp_file("temp.txt");

        string line;
        bool consumed = false;
        if (buffer_file.is_open() && temp_file.is_open()) {
            while (getline(buffer_file, line)) {
                if (!consumed) {
                    item = line; // Consume the first line
                    consumed = true;
                } else {
                    temp_file << line << endl;
                }
            }

            buffer_file.close();
            temp_file.close();

            // Replace the original file with the updated one
            remove(FILENAME);
            rename("temp.txt", FILENAME);

            // Ask the user if they want to consume the item
            cout << "Item available: " << item << ". Consume this item? (yes/no): ";
            string user_input;
            cin >> user_input;

            if (user_input == "yes") {
                cout << "Consumed: " << item << endl;
            } else {
                cout << "Item skipped.\n";
                // If the user chooses not to consume, add the item back to the file
                ofstream buffer_file(FILENAME, ios::app);
                buffer_file << item << endl;
                buffer_file.close();
            }
        } else {
            cerr << "Error: Could not open buffer file.\n";
        }

        // Unlock the buffer
        ReleaseSemaphore(mutex, 1, NULL);
        // Signal that an empty slot is now available
        ReleaseSemaphore(empty, 1, NULL);
    }
    return NULL;
}

int main() {
    mutex = CreateSemaphoreW(NULL, 1, 1, SEM_MUTEX); 
    full = CreateSemaphoreW(NULL, 0, BUFFER_SIZE, SEM_FULL); 
    empty = CreateSemaphoreW(NULL, BUFFER_SIZE, BUFFER_SIZE, SEM_EMPTY); 

    if (mutex == NULL || full == NULL || empty == NULL) {
        cerr << "Error: Semaphore creation failed. Error Code: " << GetLastError() << endl;
        return -1;
    }

    pthread_t consumer_thread;
    pthread_create(&consumer_thread, NULL, consume, NULL);
    pthread_join(consumer_thread, NULL);

    // Close semaphores
    CloseHandle(mutex);
    CloseHandle(full);
    CloseHandle(empty);

    return 0;
}