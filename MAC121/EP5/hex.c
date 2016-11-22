#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef enum { false, true } bool;
typedef enum { WHITE, BLACK } color;

void printUsage() {
    printf("Usage: ./ep5 <pegColor(p, b)> [d]\n");
    exit(EXIT_SUCCESS);
}
int main(int argc, char const *argv[]) {
    bool gameIsOn;
    bool debug;
    color myColor;
    gameIsOn = debug = false;

    /* Input verification */
    if(argc < 2 || argc > 3) {
        printUsage();
    }
    if(strcmp(argv[1],"p") == 0) {
        myColor = BLACK;
    }
    else if(strcmp(argv[1],"b") == 0) {
        myColor = WHITE;
    }
    else {
        printUsage();
    }
    if(argc == 3) {
        if(strcmp(argv[2],"d") == 0)
            debug = true;
        else
            printUsage();
    }



    return 0;
}
