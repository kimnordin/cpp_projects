#include <iostream>

using namespace std;

void insertElement(int*& arr, int& currentSize, int& maxSize, int element) 
{
    if (currentSize == maxSize) {
        // Resize array
        maxSize *= 2;
        int* temp = new int[maxSize];

        for (int i = 0; i < currentSize; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
    }

    arr[currentSize++] = element;
}

void displayArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int maxSize = 2; // Initial size of array
    int currentSize = 0;
    int* arr = new int[maxSize];

    // Example usage
    insertElement(arr, currentSize, maxSize, 10);
    insertElement(arr, currentSize, maxSize, 20);
    insertElement(arr, currentSize, maxSize, 30); // Triggers resize

    displayArray(arr, currentSize);

    delete[] arr; // Free allocated memory
    return 0;
}
