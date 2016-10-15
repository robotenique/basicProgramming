#include <stdio.h>
#include <stdlib.h>
#include "arrayOps.h"
void printArray (int *array, int n);

int main(int argc, char const *argv[]) {
    int *v;
    int val;
    int n = 100000000;
    v = malloc(n*sizeof(int));
    for (int i = n; i > 0; i--)
        v[i] = i+7;
    val = binarySearchRec(v,0,n-1,123341);
    printf("val = %d\n",val);
    return 0;
}

void printArray (int v[], int n) {
    int k = 0;
    printf("[%2d,",v[k]);
    for (k = 1; k < n - 1; printf(" %2d,",v[k]), ++k);
    printf(" %2d]",v[k]);
    printf("\n");
}

int binarySearch(int *array, int n, int x) {
    int b = 0, e = n - 1, m;
    while (b <= e) {
        m = (b+e)/2;
        if (x > array[m])
            b = m+1;
        else if (x < array[m])
            e = m-1;
        else
            return m;
        }
    return -1;
}

int binarySearchRec (int *array, int b, int e , int x) {
    int m;
    if (b > e) return -1;
    m = (b + e)/2;
    if (array[m] == x) return m;
    if (x < array[m]) return (binarySearchRec(array, b , m - 1, x));
    return binarySearchRec(array, m + 1, e, x);
}
