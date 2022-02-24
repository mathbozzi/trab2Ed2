#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "suffix.h"

// Lê o conteúdo do arquivo informado como um grande vetor de char,
// elimina todos os caracteres extras de espaço em branco e quebra de linha,
// retornando uma string com as palavras separadas por um único espaço.
String* strip_read(char *file_name) {
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open file '%s'!\n", file_name);
        exit(1);
    }

    int N;
    fscanf(fp, "%d\n", &N);

    char *a = malloc(N * sizeof(char));
    int k = 0;
    bool ws = false;
    for (int i = 0; i < N; i++) {
        char c;
        fscanf(fp, "%c", &c);
        if (c == ' ' || c == '\n') { ws = true; continue; }
        if (ws) { a[k++] = ' '; ws = false; }
        a[k++] = c;
    }

    fclose(fp);

    String *s = malloc(sizeof *s);
    s->len = k;
    s->c = malloc(s->len * sizeof(char));
    for (int i = 0; i < s->len; i++) {
        s->c[i] = a[i];
    }
    free(a);
    return s;
}

String* read_query() {
    char buf[100];
    int i = 0;
    while ((buf[i++] = getchar()) != '\n') ;
    buf[i-1] = '\0';
    String *s = create_string(buf);
    return s;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./a.out [file.txt] [context]\n");
        exit(1);
    }

    String *text = strip_read(argv[1]);
    int N = text->len;
    int context = atoi(argv[2]);

    Suffix* *a = create_suf_array(text, N);
    sort_suf_array_sys(a, N);

    String *query = read_query();
    while (query->len > 0) {
        for (int i = rank(a, N, query); i < N; i++) {
            int from1 = a[i]->index;
            int to1 = from1 + query->len;
            if (to1 > N) { to1 = N; }
            if (!equals_substring(text, from1, to1, query)) break;
            int from2 = a[i]->index - context;
            if (from2 < 0) { from2 = 0; }
            int to2 = a[i]->index + context + query->len;
            if (to2 > N) { to2 = N; }
            print_substring(text, from2, to2);
            printf("\n");
        }
        printf("\n");
        destroy_string(query);
        query = read_query();
    }

    destroy_string(query);
    destroy_suf_array(a, N);
    destroy_string(text);

    return 0;
}
