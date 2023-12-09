#include <iostream>

void printHeapArray(int arr[], int size, int index) {
    // Base case: return when the index exceeds the size of the array
    if (index >= size) {
        return;
    }

    // Print the current element
    std::cout << arr[index] << " ";

    // Recursive call on the left subtree
    printHeapArray(arr, size, 2 * index + 1);

    // Recursive call on the right subtree
    printHeapArray(arr, size, 2 * index + 2);
}

int main() {
    // Example heap array
    int heapArray[] = {1, 2, 3, 4, 5, 6, 7};

    int size = sizeof(heapArray) / sizeof(heapArray[0]);

    // Print the heap array in preorder
    printHeapArray(heapArray, size, 0);

    return 0;
}
