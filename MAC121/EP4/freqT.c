#include <stdio.h>
#include "buffer.c"
int main(int argc, char const *argv[]) {
    Buffer *B;
    B = buffer_create();    
    if (argc != 4)
        die("Erro! Forneça todos os argumentos necessários!");

    return 0;
}
