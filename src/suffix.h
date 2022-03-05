#ifndef SUFFIX_H
#define SUFFIX_H

#include "str.h"

typedef struct {
	String *s;
	int index;
} Suffix;

Suffix *create_suffix(String *s, int index);  // done

void destroy_suffix(Suffix *suf);

void print_suffix(Suffix *suf);  //done

Suffix **create_suf_array(String *text, int N);  //done

void destroy_suf_array(Suffix **a, int N);

void print_suf_array(Suffix **a, int N);  //done

// Use uma (ou mais) funcoes deste tipo para ordenar
// o arry de sufixos usando o qsort e outro metodo de sua escolha
void sort_suf_array(Suffix **a, int N);

int rank(Suffix **a, int N, String *query);

#endif
