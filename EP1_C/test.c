#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define DEFAULT_MAXNUM  100000000

static uint16_t *result;

uint16_t collatz(uint64_t n)
{
    uint64_t originalNumber = n;
    uint16_t count          = 1;

    while (1) {
        if (n & 1) {
            n = n*3+1;
        } else {
            n /= 2;
            if (n < originalNumber)
                return count + result[n];
        }
        count++;
    }
}

int main(int argc, char *argv[])
{
    uint64_t i         = 0;
    uint16_t count     = 0;
    uint16_t bestCount = 1;
    uint64_t bestNum   = 1;
    uint64_t maxNum    = DEFAULT_MAXNUM;

    result = malloc(maxNum * sizeof(result[0]));
    if (result == NULL) {
        fprintf(stderr, "Error: Not enough memory\n");
        return 1;
    }

    result[1] = 1;
    for(i=2; i<maxNum; i++) {
        count = result[i] = collatz(i);
        if (count > bestCount) {
            bestCount = count;
            bestNum   = i;
        }
    }

    printf("Max considered: %" PRIu64 "\n", maxNum);
    printf("Largest number: %" PRIu64 "\n", bestNum);
    printf("Largest count : %d\n", bestCount);
    return 0;
}