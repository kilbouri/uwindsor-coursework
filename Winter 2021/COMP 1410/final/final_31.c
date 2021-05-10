#include <stdio.h>

// reverses array between start and end. Completely in-place.
void reverse_array(int arr[], int start, int end) {
    while (start < end) {
        arr[start] += arr[end];
        arr[end] = arr[start] - arr[end];
        arr[start++] -= arr[end--];
    }
}

int main(void) {
    int arr[] = { 0, 1, 2, 3 };
    reverse_array(arr, 0, 3);
    return 0;
}