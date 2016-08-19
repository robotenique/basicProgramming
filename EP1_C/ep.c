/*
 * Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 22/08/2016
 */
#include <stdio.h> /* printf, scanf, NULL */
#include <stdlib.h> /* malloc, free, rand */

/* Definindo constantes de alocação máxima de memória */ 
#define MAX_ALLOC 600000000
#define DESVIO     10000001

typedef unsigned long  int uLint;
typedef unsigned short int uSint;
typedef unsigned       int uInt;

uInt   begin;
uSint *numbersCalc;
uSint *dynamicAloc;


/* Calcula a quantidade de passos da seq. de Collatz de um número
 *  no intervalo especificado na entrada.
 */
uSint calcCollatz (uInt n)
{    
  uLint auxN   = n;
  uSint steps  = 0;  

    while (auxN >= DESVIO) {
      if (auxN & 1) {
        auxN   = (3*auxN + 1)/2;
        steps += 2;
      }
      else {
        auxN >>= 1;            
        if ( auxN < n           && 
             auxN<MAX_ALLOC     &&
             auxN >= begin      &&
             dynamicAloc[auxN-begin] != 0) {                     
          return steps + dynamicAloc[auxN-begin];
        }
        steps += 1;
      }
    }
  return steps+numbersCalc[auxN];
}



/* Cria uma tabela com a quantidade de passos até n = DESVIO*/

void preparaTabela (uSint *tab)
{
  uInt  i;
  uLint auxN;
  uSint steps;

  for (i = 2; i < DESVIO; i++) {
    auxN  = i;
    steps = 0;
    while (1) {
      if (auxN & 1) {
        auxN   = (3*auxN + 1)/2;
        steps += 2;
      }
      else {
        auxN >>= 1;
        steps += 1;
        if (auxN < i) {
          steps += tab[auxN];
          break;
        }
      }
    }
    tab[i] = steps;
  }
}


int main()
{
    uInt  end;
    uInt  i;
    uSint steps;    
    
    /* É garantido que:
    - begin >  0;
    - end   >= begin;
    - begin e end são inteiros.
    */
    scanf("%u %u", &begin, &end);
   
    numbersCalc = calloc(DESVIO,sizeof(uSint));    
    if(end - begin + 1 < MAX_ALLOC)
      dynamicAloc = calloc(end - begin + 1,sizeof(uSint));
    else
      dynamicAloc = calloc(MAX_ALLOC,sizeof(uSint));
    if (numbersCalc == NULL || dynamicAloc == NULL) {
      printf("Erro na alocação de memória, verifique a entrada novamente!\n");
      return 1;
    }

    preparaTabela(numbersCalc);    
    
    for (i = begin; i <=end; i++) {
      steps = calcCollatz(i);      
      if (i > DESVIO && (i - begin) < MAX_ALLOC) {
        dynamicAloc[i-begin] = steps;
      }
      printf("%hu\n",steps);
      
    }
    /* Como o programa é terminado nesse exato momento, toda memória alocada é
       liberada, sem necessidade de usar free()
    */
    return 0;
}