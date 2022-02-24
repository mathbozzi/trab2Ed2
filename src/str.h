#ifndef STR_H
#define STR_H

#include <stdbool.h>

// Novo tipo de strings para evitar o inferno astral de ter de lidar com
// array de char terminado por '\0'.
typedef struct {
    char *c;
    int len;
} String;

// Cria uma estrutura String a partir de uma string do C (terminada por '\0').
String* create_string(char *cs);

// Libera a memória ocupada pela String.
void destroy_string(String *s);

// Exibe a String em stdout.
void print_string(String *s);

// Compara as duas Strings dadas. Retorna:
// -1 se s < t
//  1 se s > t
//  0 se s == t
int compare(String *s, String *t);

// Realiza a comparação das duas Strings dadas a partir do caractere 'd'.
int compare_from(String *s, String *t, int d);

// Cria um vetor vazio de ponteiros para String do tamanho dado.
String** create_str_array(int N);

// Libera o vetor de Strings, incluindo o seu conteúdo.
void destroy_str_array(String* *a, int N);

// Exibe o vetor de Strings em stdout.
void print_str_array(String* *a, int N);

bool equals_substring(String *text, int from, int to, String *query);

void print_substring(String *text, int from, int to);

#endif
