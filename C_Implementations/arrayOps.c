#include <stdio.h>
#include <stdlib.h>
#include "arrayOps.h"

int main(int argc, char const *argv[]) {
    int *v;
    int val;
    int n = 100000;
    v = malloc(n*sizeof(int));
    for (int i = n; i > 0; i--)
        v[n - i] = i;
    val = binarySearch(v, n, 34);
    printf("val = %d\n",val );
    return 0;
}
/* TODO : FIX THIS */
int binarySearch(int *array, int n, int x) {
    int b = 0, e = n - 1, m;
    while (b < e) {
        m = (b+e)/2;
        if (x > array[m])
            b = m+1;
        else if (x < array[m])
            e = m+1;
        else
            return m;
        printf("[%d        |%d|        %d]\n",b,m,e );
    }

    return -1;
}
