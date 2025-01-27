// C++ program to implement sorting and searching algorithm

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to merge two sorted arrays into a single sorted array
int* merge(const int* left, int leftSize, const int* right, int rightSize) {
    int* result = new int[leftSize + rightSize];
    int i = 0, j = 0, k = 0;

    // Merge both subarrays
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            result[k++] = left[i++];
        } else {
            result[k++] = right[j++];
        }
    }

    // Append remaining elements from left subarray
    while (i < leftSize) {
        result[k++] = left[i++];
    }

    // Append remaining elements from right subarray
    while (j < rightSize) {
        result[k++] = right[j++];
    }

    return result;
}

// Function to recursively perform merge sort
int* mergeSort(const int* arr, int size) {
    // Base case: If array has 1 or 0 elements, it is already sorted
    if (size <= 1) {
        int* baseCase = new int[size];
        if (size == 1) {
            baseCase[0] = arr[0];
        }
        return baseCase;
    }

    // Split the array into two halves
    int mid = size / 2;

    // Recursively sort each half
    int* left = mergeSort(arr, mid);
    int* right = mergeSort(arr + mid, size - mid);

    // Merge sorted halves
    int* result = merge(left, mid, right, size - mid);

    // Free the memory of temporary arrays
    delete[] left;
    delete[] right;

    return result;
}

// Function to copy one array to another
int* copy(const int* arr, int n) {
    int* result = new int[n];
    for (int i = 0; i < n; i++) {
        result[i] = arr[i];
    }
    return result;
}

// Function to perform bubble sort on a copy of the array
int* bubbleSort(const int* arr, int n) {
    // Handle the base case for arrays of size 0 or 1
    if (n <= 1) {
        int* baseCase = new int[n];
        if (n == 1) {
            baseCase[0] = arr[0];
        }
        return baseCase;
    }

    // Create a copy of the input array
    int* result = copy(arr, n);

    // Perform bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                // Swap the elements
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
    return result;
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1); // Index of smaller element
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1); // Return partition index
}

void quickSortHelper(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partition the array
        quickSortHelper(arr, low, pi - 1);  // Sort left of pivot
        quickSortHelper(arr, pi + 1, high); // Sort right of pivot
    }
}

// Function to implent quicksort
int* quickSort(const int* arr, int n) {
    if (n <= 1) {
        int* baseCase = new int[n];
        if (n == 1) baseCase[0] = arr[0];
        return baseCase;
    }

    int* result = copy(arr, n);
    quickSortHelper(result, 0, n - 1); // Use the helper function
    return result;
}

// Function to search input/entered number using linear search
int linearSearch(int arr[], int size, int item){
    for(int i=0; i<size; i++)
        if(arr[i]==item)
            return 1;
    return 0;
}

// Function to search input/entered number using binary search
int binarySearch(int arr[], int size, int item){
    int beg = 0, end = size - 1;
    while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (arr[mid] == item)
            return 1;
        else if (arr[mid] > item)
            end = mid - 1;
        else
            beg = mid + 1;
    }
    return 0;
}

// Function to verify if all algorithms results in same sorted order
int check(const int* arr1, const int* arr2, const int* arr3, int n) {
    int flag=1,i;
    for (i=0; i<n; i++){
        // cout << arr1[i]<<" "<<arr2[i]<<" "<<arr3[i]<<endl;
        if((arr1[i]!=arr2[i]) || (arr1[i]!=arr3[i]))
            flag=0;
    }
    return flag;
}

int main() {
    int size, num;

    // Input array size
    cout << "Enter the size of the array: ";
    cin >> size;

    // Input array elements
    int* arr = new int[size];
    cout << "Enter " << size << " numbers to be sorted: ";
    for (int i = 0; i < size; ++i) {                        // displays sorted array
        cin >> arr[i];
    }

    // Perform sorts
    auto start = high_resolution_clock::now();                              // records time before calling for sorting
    int* sortedArray_merge = mergeSort(arr, size);                          // applies merge sort algorithm to sort array
    auto stop = high_resolution_clock::now();                              // records time after calling for sorting
    auto duration = duration_cast<microseconds>(stop - start);              // calculates time taken
    cout << "Time taken by merge sort: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    int* sortedArray_bubble = bubbleSort(arr, size);                          // applies bubble sort algorithm to sort array
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by bubble sort: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    int* sortedArray_quick = quickSort(arr, size);                          // applies quick sort algorithm to sort array
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by quick sort: " << duration.count() << " microseconds" << endl;
    
    // Output the sorted array
    cout << "The sorted numbers are: ";
    for (int i = 0; i < size; ++i)
        cout << sortedArray_merge[i] << " ";
    cout << endl;

    if(!check(sortedArray_merge, sortedArray_bubble, sortedArray_quick, size))      // compares result of each sorting algorithm
        cout << "Some sorting algoriths are mistakenly implemented"<<endl;

    cout << "Enter number to be searched : ";
    cin >> num;

    start = high_resolution_clock::now();
    if(binarySearch(sortedArray_bubble, size, num))                 // calls function to implement binary search algorithm
        cout << "Item found using binary search" << endl;
    else
        cout << "Item not found using binary search" << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken to search element by binary search: " << duration.count() << " microseconds" << endl;
    
    start = high_resolution_clock::now();
    if(linearSearch(sortedArray_bubble, size, num))                 // calls function to implement linear search algorithm
        cout << "Item found using linear search"<< endl;
    else
        cout << "Item not found using linear search"<< endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken to search element by linear search: " << duration.count() << " microseconds" << endl;

    // Free allocated memory
    delete[] arr;
    delete[] sortedArray_merge;
    delete[] sortedArray_merge;
    delete[] sortedArray_quick;

    return 0;
}
