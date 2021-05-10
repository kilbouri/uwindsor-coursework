#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);

int main(void) {
    int arr1[] = { 1,2,3,0,0,0 };
    int arr2[] = { 2,5,6 };
    merge(arr1, 6, 3, arr2, 3, 3);
    return 0;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    // we start by creating a copy of nums1
    int* n1cpy = (int*)malloc(m * sizeof(int));
    memcpy(n1cpy, nums1, m * sizeof(int));
    
    printf("%d\n", m);
    printf("%d\n", n);
    
    // we now iterate over the n+m elements, setting the lowest into nums1
    int* pos_a = n1cpy;
    int* pos_b = nums2;
    for (int i = 0; i < nums1Size; i++) {
        if (pos_a < n1cpy + m && *pos_a <= *pos_b) {
            nums1[i] = *pos_a;
            pos_a++;
        } else if (pos_b < nums2 + n){
            nums1[i] = *pos_b;
            pos_b++;
        }
    }
    
    // finally, we clean up the extra memory
    free(n1cpy);
}