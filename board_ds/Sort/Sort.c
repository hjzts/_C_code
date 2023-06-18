//
// Created by 86152 on 2023/6/10.
//

//Author hugo
//Time 2023/6/10 17:58
/*
 *  µœ÷¡Àº∏÷÷≥£º˚µƒ≈≈–ÚÀ„∑®£¨∞¸¿®≤Â»Î≈≈–Ú°¢’€∞Î≤Â»Î≈≈–Ú°¢√∞≈›≈≈–Ú°¢º¶Œ≤æ∆≈≈–Ú°¢—°‘Ò≈≈–Ú°¢øÏÀŸ≈≈–Ú∫Õ∂—≈≈–Ú°£
 * ªπ√ª”– µœ÷Õ∞≈≈–Ú
*/
#include <stdio.h>
#include <stdlib.h>

// ≤Â»Î≈≈–Ú
void insertionSort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// ’€∞Î≤Â»Î≈≈–Ú
void binaryInsertionSort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int low = 0;
        int high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (array[mid] > key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= low; j--) {
            array[j + 1] = array[j];
        }
        array[low] = key;
    }
}

// √∞≈›≈≈–Ú
void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// º¶Œ≤æ∆≈≈–Ú  shell sort
void cocktailSort(int *array, int size) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            if (array[i] < array[i - 1]) {
                int temp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = temp;
            }
        }
        left++;
    }
}

// —°‘Ò≈≈–Ú
void selectionSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

// øÏÀŸ≈≈–Ú
void quickSort(int *array, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = array[left];
    int i = left;
    int j = right;
    while (i < j) {
        while (i < j && array[j] >= pivot) {
            j--;
        }
        array[i] = array[j];
        while (i < j && array[i] <= pivot) {
            i++;
        }
        array[j] = array[i];
    }
    array[i] = pivot;
    quickSort(array, left, i - 1);
    quickSort(array, i + 1, right);
}

// ∂—≈≈–Ú
void heapify(int *array, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && array[left] > array[largest]) {
        largest = left;
    }
    if (right < size && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        heapify(array, size, largest);
    }
}

void heapSort(int *array, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }
    for (int i = size - 1; i >= 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);
    }
}

int main() {
    int array[] = {5, 2, 4, 6, 1, 3};
    int size = sizeof(array) / sizeof(array[0]);
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    insertionSort(array, size);
    printf("Insertion sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    int array2[] = {5, 2, 4, 6, 1, 3};
    binaryInsertionSort(array2, size);
    printf("Binary insertion sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    int array3[] = {5, 2, 4, 6, 1, 3};
    bubbleSort(array3, size);
    printf("Bubble sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array3[i]);
    }
    printf("\n");

    int array4[] = {5, 2, 4, 6, 1, 3};
    cocktailSort(array4, size);
    printf("Cocktail sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array4[i]);
    }
    printf("\n");

    int array5[] = {5, 2, 4, 6, 1, 3};
    selectionSort(array5, size);
    printf("Selection sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array5[i]);
    }
    printf("\n");

    int array6[] = {5, 2, 4, 6, 1, 3};
    quickSort(array6, 0, size - 1);
    printf("Quick sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array6[i]);
    }
    printf("\n");

    int array7[] = {5, 2, 4, 6, 1, 3};
    heapSort(array7, size);
    printf("Heap sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array7[i]);
    }
    printf("\n");

    return 0;
}