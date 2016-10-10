#include "sort.h"
#include <stdio.h>
int linearSearch(float v[], int n, float x) {
    for (int i = 0; i < n; i++)
        if (v[i] == x)
            return i;
    return -1;
}

int binarySearchIns(float v[], int b, int e, float x) {
    if(b > e)
        return e;
    int m = (b+e)/2;
    if(v[m] == x) return m;
    if(v[m] > x) return binarySearchIns(v,b,m-1,x);
    return binarySearchIns(v,m+1,e,x);
}


void bubbleSort(float v[], int n) {
    int ch = 1;
    while(ch) {
        ch = 0;
        for (int i = 0; i < n - 1; i++)
            if (v[i] > v[i+1]) {
                int aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                ch = 1;
            }
        n--;
    }
}

void selectionSort(float v[], int n) {
    int min;
    float aux;
    for (int i = 0; i < n-1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++)
            if(v[min] > v[j])
                min = j;
        if(min!=i) {
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

void insertionSort(float v[], int n) {
    float x;
    int j;
    for (int i = 1; i < n; i++) {
        x = v[i];
        for(j = i-1; j>=0 && v[j]>x; j--)
            v[j+1] = v[j];
        v[j+1] = x;
    }
}

//Insertion Sort with binarySearch
void insertionSortLog(float v[], int n) {
    float x;
    int j;
    for (int i = 1; i < n; i++) {
        x = v[i];
        j = binarySearchIns(v,0,i-1,x);
        for(int k = i-1; k > j; v[k+1] = v[k], k--);
        v[j+1] = x;
    }
}
