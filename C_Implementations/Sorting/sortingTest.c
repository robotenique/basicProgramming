#include "sort.h"
#include <stdio.h>
int main(int argc, char const *argv[]) {
    //Initialize an array
    int n = 50;
    float *v = malloc(n*sizeof(float));
    for (int i = 0; i < n; i++)
        v[i] = (float)rand()%n;
    for (int k = 0; k < n; printf("%f |",v[k]), k++);
    return 0;
}
