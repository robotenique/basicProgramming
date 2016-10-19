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

ull bubbleSort(float v[], int n) {
    ull nSwap = 0;
    int flag = 0;
    for (int i = n - 1; i > 0 && !flag; i--) {
            flag = 1;
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j+1]) {
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                nSwap += 1;
                flag = 0;
            }
        }
    }
    return nSwap;
}

ull selectionSort(float v[], int n) {
    ull nSwap = 0;
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
    return nSwap;
}

ull insertionSort(float v[], int n) {
    ull nSwap = 0;

    float x;
    int j;
    for (int i = 1; i < n; i++) {
        x = v[i];
        for(j = i-1; j>=0 && v[j]>x; j--)
            v[j+1] = v[j];
        v[j+1] = x;
    }
    return nSwap;
}

//Insertion Sort with binarySearch
ull insertionSortLog(float v[], int n) {
    ull nSwap = 0;

    float x;
    int j;
    for (int i = 1; i < n; i++) {
        x = v[i];
        j = binarySearchIns(v,0,i-1,x);
        for(int k = i-1; k > j; v[k+1] = v[k], k--);
        v[j+1] = x;
    }
    return nSwap;
}

ull merge(float v[], float aux[], int ini, int mid, int end) {
    ull cmp = 0;
    //Copy
    for (int k = ini; k <= end; aux[k] = v[k], k++);
    //Merging
    int i = ini;
    int j = mid+1;
    for (int k = ini; k <= end; k++) {
        cmp++;
        if(i > mid) v[k] = aux[j++];
        else if(j > end) v[k] = aux[i++];
        else if(aux[j] < aux[i]) v[k] = aux[j++];
        else v[k] = aux[i++];
    }
    return cmp;
}

ull mergeSort(float v[], float aux[], int ini, int end, ull cmp) {
    if(end <= ini) return cmp;
    int mid = ini + (end-ini)/2;
    mergeSort(v,aux,ini,mid,cmp);
    mergeSort(v,aux,mid+1,end,cmp);
    cmp += merge(v,aux,ini,mid,end);
    return cmp;
}

void swap(float v[], int a, int b) {
    int aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}
void sink(float v[], int k, int n) {
    int j;
    while(2*k < n){
        j =2*k + 1;
        if(j < n - 1 && v[j] < v[j+1]) j++;
        if(v[k] > v[j]) break;
        swap(v,k,j);
        k = j;
    }
}

void heapify(float v[], int n) {
    for (int k = n/2; k >= 0; k--)
        sink(v,k,n);
}

ull heapSort(float v[], int n) {
    heapify(v,n);
    printArray(v,n);

    for (int k = n - 1; k > 0; k--) {
        swap(v, k, 0);
        printf("Faz (%2.2f) <-> (%2.2f) , ",v[k],v[0]);
        sink(v, 0, k);
        printArray(v,n);
    }
    return 0;
}

void printArray (float v[], int n) {
    int k = 0;
    printf("[%2.0f,",v[k]);
    for (k = 1; k < n - 1; printf(" %2.0f,",v[k]), ++k);
    printf(" %2.0f]",v[k]);
    printf("\n");
}
