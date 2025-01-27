// C++ program to handle producer side of producer-consumer problem using semaphore and mutex

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

void* produce(void* arg) {
    string item;
    while (true) {
        cout << "Enter item to produce (or type 'exit' to stop): ";
        getline(cin, item);
        if (item == "exit") break;

        // Wait for an empty slot in the buffer
        WaitForSingleObject(empty, INFINITE); // Wait if buffer is full

        // Lock the buffer
        WaitForSingleObject(mutex, INFINITE);

        // Write the item to the buffer file
        ofstream buffer_file(FILENAME, ios::app);
        if (buffer_file.is_open()) {
            buffer_file << item << endl;
            cout << "Produced: " << item << endl;
            buffer_file.close();
        } else {
            cerr << "Error: Could not open buffer file.\n";
        }

        // Unlock the buffer
        ReleaseSemaphore(mutex, 1, NULL);
        // Signal that a new item has been added
        ReleaseSemaphore(full, 1, NULL);
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

    pthread_t producer_thread;
    pthread_create(&producer_thread, NULL, produce, NULL);
    pthread_join(producer_thread, NULL);

    // Close semaphores
    CloseHandle(mutex);
    CloseHandle(full);
    CloseHandle(empty);

    return 0;
}