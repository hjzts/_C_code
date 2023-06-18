#include <stdio.h>

#define INF 100
#define datatype int

void test_print(datatype array[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", array[i]);
    }
    putchar(10);
}

void SelectionSort(datatype array[], int len) {
    int i,j;
    for(i = 1;i < len; ++i) {
        datatype temp = array[i];
        j = i - 1;
        while (j >= 0) {
            if(temp < array[j]) {
                array[j+1] = array[j];
                j--;
            }else break;
        }
        array[j + 1] = temp;
    }
}

int main() {
    datatype a[] = {15, 65, 2, 56, 5, 4, 3, 2, 1, 2, 55, 1, 2, 89, 6, 5};
    test_print(a,16);
    SelectionSort(a, 16);
    test_print(a, 16);
    return 0;
}