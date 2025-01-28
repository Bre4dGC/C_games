#include <stdio.h>

int sum(int *arr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum;
}
void minmax(int *arr, int len, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 0; i < len; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}
void sort(int *arr, int len) {
    int temp = 0;
    for (int i = 0; i < len; i++){
        temp = arr[i];
        for (int j = i+1; j < len; j++) {
            if(arr[i] > arr[j]) {
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }    
}

void main(void) {
    
}