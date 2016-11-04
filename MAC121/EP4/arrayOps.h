/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Header file para funções auxiliares e tipos básicos das tabelas de símbolos.
 */
#ifndef __ARRAYOPS_H__
#define __ARRAYOPS_H__

/*-------- Tipos e structs -------- */
typedef char minINT;

/* Tipo booleano */
typedef enum { false, true } bool;
/* Struct que contém uma palavra e sua frequência */
typedef struct {
    char* p;
    unsigned int freq;
} word;
/* O valor armazenado na tabela de símbolos */
typedef union {
  int i;
  char *str;
  void *p;
} EntryData;
/* Tipo de retorno da função de inserção na tabela de símbolos */
typedef struct {
  int new;
  EntryData *data;
} InsertionResult;
/* Tipo das palavras da BST */
typedef struct {
    word *wArr;
    int i; /* Quantidade de Palavras */
} word_BST;

/* Tipo que representa o input */
typedef struct inputConfig {
    minINT stableType;
    bool orderByAlpha; /* Deve ordenar alfabeticamente? */
} inputConfig;

/*
 * Função: emalloc
 * --------------------------------------------------------
 * Executa um malloc, porém termina a execução do programa se não
 * foi possível alocar memória.
 * @args    size: tamanho para alocar
 *
 * @return ponteiro para a memória alocada.
 */
void * emalloc(int size);

/*
 * Função: die
 * --------------------------------------------------------
 * Imprime uma mensagem de erro e termina a execução do programa.
 *
 * @args    s: Mensagem de erro
 *
 * @return
 */
void die(const char *s);
/*
 * Função: estrdup
 * --------------------------------------------------------
 * Duplica uma string (usando strdup), verifica se há erro e retorna a string
 * duplicada caso não houve problemas na alocação.
 *
 * @args    s: String para ser duplicada
 *
 * @return Ponteiro para cópia da String
 */
char * estrdup(const char *s);
/*
 * Função: linearSearch
 * --------------------------------------------------------
 * Faz uma busca linear no vetor de palavras e retorna a posição do
 * elemento no vetor.
 *
 * @args    keys: Vetor de palavras
 *          str : Palavra a ser pesquisada
 *          n   : Tamanho do vetor
 *
 * @return -1 se a palavra não foi encontrada, senão retorna a posição
 * onde a palavra se encontra no vetor 'keys'
 */
int linearSearch(char **keys, char* str, int n);
/*
 * Função: copyValue
 * --------------------------------------------------------
 * Copia uma palavra e o dado para a posição 'i' do array de palavras 'arr'.
 * É usado como callback para as operações 'apply' das tabelas de símbolo.
 *
 * @args    key:  Uma palavra da Tabela de Símbolos
 *          data: O dado da tabela de símbolos
 *          arr:  Array de palavras
 *          i:    Posição onde se deve inserir a palavra
 *
 * @return Um inteiro (1) solicitando uma nova entrada.
 */
int  copyValue(const char *key, EntryData *data, word *arr, int i);
/*
 * Função: copyValue_BST
 * --------------------------------------------------------
 * Possui a mesma funcinalidade que copyValue, porém o array recebido é
 * do tipo word_BST. É usado como callback na operação apply da tabela de
 * símbolos de árvore de busca.
 *
 * @args    key:  Uma palavra da Tabela de Símbolos
 *          data: O dado da tabela de símbolos
 *          arr:  Array de palavras + próxima posição livre
 *
 * @return
 */
void copyValue_BST(const char *key, EntryData *data, word_BST *arr);
/*
 * Função: compareAlphabet
 * --------------------------------------------------------
 * Função que compara duas palavras usando strcmp, usada como
 * callback para o qsort.
 *
 * @args    a: Uma palavra do vetor
 *          b: Outra palavra do vetor
 *
 * @return 0 se são iguais, -1 se a < b, 1 se a > b
 */
int compareAlphabet(const void * a, const void * b);
/*
 * Função: compareFreq
 * --------------------------------------------------------
 * Compara duas frequências e retorna a comparação, é usado como
 * callback para o qsort.
 *
 * @args    a: Primeira frequência
 *          b: Segunda frequência
 *
 * @return -1 se a < b, 1 se a > b, se são iguais, retorna
 * o resultado de compareAlphabet(a, b), sendo a e b as palavras que contém
 * as frequências iguais.
 */
int compareFreq(const void * a, const void * b);
/*
 * Função: max
 * --------------------------------------------------------
 * Retorna o máximo entre dois números
 *
 * @args    a: Primeiro número
 *          b: Segundo número
 *
 * @return  a se a > b, b se b > a
 */
int max(int a, int b);
/*
 * Função: isValid
 * --------------------------------------------------------
 * Verifica se um caracter é valido na palavra (isto é, é um número ou letra).
 *
 * @args    c: char para ser verificado
 *
 * @return true se é número ou letra, false caso contrário
 */
bool isValid(char c);
/*
 * Função: isNotAlpha
 * --------------------------------------------------------
 * Verifica se é um número ou não é uma letra
 *
 * @args    c: char para ser verificado
 *
 * @return true se é um número um não é uma letra, false caso contrário
 */
bool isNotAlpha(char c);

#endif
