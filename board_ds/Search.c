//
// Created by 86152 on 2023/6/10.
//

//Author hugo
//Time 2023/6/10 17:51
/*
 *题目表述
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 顺序查找的递归算法
int sequentialSearchRecursive(int *array, int key, int index, int size) {
    if (index >= size) {
        return -1;
    }
    if (array[index] == key) {
        return index;
    }
    return sequentialSearchRecursive(array, key, index + 1, size);
}

// 折半查找（非递归算法）
int binarySearchNonRecursive(int *array, int key, int size) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (array[mid] == key) {
            return mid;
        } else if (array[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// 折半查找的递归算法
int binarySearchRecursive(int *array, int key, int low, int high) {
    if (low > high) {
        return -1;
    }

    int mid = (low + high) / 2;
    if (array[mid] == key) {
        return mid;
    } else if (array[mid] < key) {
        return binarySearchRecursive(array, key, mid + 1, high);
    } else {
        return binarySearchRecursive(array, key, low, mid - 1);
    }
}

// 在按值递增排列且长度为 n 的线性表中折半查找并插入一元素
void binarySearchInsert(int *array, int *size, int key) {
    int low = 0;
    int high = *size - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (array[mid] == key) {
            break;
        } else if (array[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (array[mid] < key) {
        mid++;
    }

    for (int i = *size; i > mid; i--) {
        array[i] = array[i - 1];
    }
    array[mid] = key;
    (*size)++;
}

// 在按值递增排列且长度为 n 的线性表中折半查找值不小于 key 的最小元素
int binarySearchLowerBound(int *array, int key, int size) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (array[mid] >= key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low < size ? low : -1;
}
int main() {
    int array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(array) / sizeof(array[0]);
    int key = 7;

    printf("Sequential search recursive: ");
    int index1 = sequentialSearchRecursive(array, key, 0, size);
    if (index1 != -1) {
        printf("Found key %d at index %d\n", key, index1);
    } else {
        printf("Key %d not found\n", key);
    }

    printf("Binary search non-recursive: ");
    int index2 = binarySearchNonRecursive(array, key, size);
    if (index2 != -1) {
        printf("Found key %d at index %d\n", key, index2);
    } else {
        printf("Key %d not found\n", key);
    }

    printf("Binary search recursive: ");
    int index3 = binarySearchRecursive(array, key, 0, size - 1);
    if (index3 != -1) {
        printf("Found key %d at index %d\n", key, index3);
    } else {
        printf("Key %d not found\n", key);
    }

    int insertKey = 6;
    printf("Before insert: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    int newSize = size + 1;
    int *newArray = (int *)malloc(newSize * sizeof(int));
    memcpy(newArray, array, size * sizeof(int));
    binarySearchInsert(newArray, &newSize, insertKey);

    printf("After insert key %d: ", insertKey);
    for (int i = 0; i < newSize - 1; i++) {
        printf("%d ", newArray[i]);
    }
    printf("\n");

    int lowerBoundKey = 8;
    int lowerBoundIndex = binarySearchLowerBound(array, lowerBoundKey, size);
    printf("Lower bound of key %d: ", lowerBoundKey);
    if (lowerBoundIndex != -1) {
        printf("Found at index %d, value %d\n", lowerBoundIndex, array[lowerBoundIndex]);
    } else {
        printf("Not found\n");
    }

    free(newArray);
    return 0;
}