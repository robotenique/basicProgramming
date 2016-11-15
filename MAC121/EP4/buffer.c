/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Implementação do Buffer. Maiores detalhes sobre cada função
 * no arquivo de header.
 */
#include "buffer.h"

 Buffer *buffer_create() {
     Buffer *B;
     B = emalloc(sizeof(Buffer));
     B->n = 1024;
     B->i = 0;
     B->data = emalloc(B->n) ;
     return B;
 }

 void buffer_destroy(Buffer *B) {
     free(B->data);
     free(B);
 }

 void buffer_reset(Buffer *B) {
    free(B -> data);
    B->n = 1024;
    B->i = 0;
    B->data = emalloc(B->n);
 }

 void buffer_push_back(Buffer *B, char c){
     int p;
     if((B->i) >= B->n) {
        char *temp = emalloc((B->n)*2);
        for (p = 0; p < B->n; p++)
            temp[p] = B->data[p];
        free(B->data);
        B->n = 2 * (B->n);
        B->data = temp;
    }
     B->data[B->i++] = c;
 }

 int read_line(FILE *input, Buffer *B){
    char c;
    int count = 0;
    buffer_reset(B);

    while((c = fgetc(input)) != EOF && c != '\n') {
        buffer_push_back(B, c);
        count++;
    }
    if (c == '\n') {
        buffer_push_back(B, c);
        count++;
    }
    return count;
 }

 void buffer_lower(Buffer *B) {
     int k;
     for (k = 0; k < B-> i && B->data[k] != 0; k++)
        B->data[k] = tolower(B->data[k]);
}
