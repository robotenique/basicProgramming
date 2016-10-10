#include "sort.h"

int linearSearch(float v[], int n, float x) {
    for (int i = 0; i < n; i++)
        if (v[i] == x)
            return i;
    return -1;
}
