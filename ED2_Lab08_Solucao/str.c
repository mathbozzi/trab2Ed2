#include <stdio.h>
#include <stdlib.h>
#include "str.h"

// Retorna o tamanho da string C, sem contar o terminador '\0'.
static int mystrlen(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++);
    return i;
}

// Cria uma estrutura String a partir de uma string do C (terminada por '\0').
String* create_string(char *a) {
    String *s = malloc(sizeof *s);
    s->len = mystrlen(a);
    s->c = malloc(s->len * sizeof(char));
    for (int i = 0; i < s->len; i++) {
        s->c[i] = a[i];
    }
    return s;
}

// Libera a memória ocupada pela String.
void destroy_string(String *s) {
    free(s->c);
    free(s);
}

// Exibe a String em stdout.
void print_string(String *s) {
    for (int i = 0; i < s->len; i++) {
        printf("%c", s->c[i]);
    }
}

// Compara as duas Strings dadas. Retorna:
// -1 se s < t
//  1 se s > t
//  0 se s == t
int compare(String *s, String *t) {
    return compare_from(s, t, 0);
}

// Realiza a comparação das duas Strings dadas a partir do caractere 'd'.
int compare_from(String *s, String *t, int d) {
    int min = s->len < t->len ? s->len : t->len;
    for (int i = d; i < min; i++) {
        if (s->c[i] < t->c[i]) { return -1; }
        if (s->c[i] > t->c[i]) { return  1; }
    }
    return s->len - t->len;
}

// Cria um vetor vazio de ponteiros para String do tamanho dado.
String** create_str_array(int N) {
    String* *a = malloc(N * sizeof(String*));
    return a;
}

// Libera o vetor de Strings, incluindo o seu conteúdo.
void destroy_str_array(String* *a, int N) {
    for (int i = 0; i < N; i++) {
        destroy_string(a[i]);
    }
    free(a);
}

// Exibe o vetor de Strings em stdout.
void print_str_array(String* *a, int N) {
    for (int i = 0; i < N; i++) {
        print_string(a[i]);
        printf("\n");
    }
}

bool equals_substring(String *text, int from, int to, String *query) {
    //if (query->len < (to - from + 1)) { return false; }
    for (int i = 0; i < query->len; i++) {
        if(query->c[i] != text->c[from + i]) { return false; }
    }
    return true;
}

void print_substring(String *s, int from, int to) {
    for (int i = from; i < to; i++) {
        printf("%c", s->c[i]);
    }
}
