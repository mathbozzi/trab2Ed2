#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./a.out [file.txt]\n");
        exit(1);
    }

    // Input
    String *text = strip_read(argv[1]);
    int N = text->len;
    Suffix* *a = create_suf_array(text, N);

    // Sort
    clock_t start, stop;
    start = clock();
    //sort_suf_array_sys(a, N);
    sort_suf_array_msd(a, N);
    stop = clock();

    // Output
    print_suf_array(a, N);
    double time_taken = ((double) stop - start) / CLOCKS_PER_SEC;
    printf("\nElapsed time: %.3f\n", time_taken);

    destroy_suf_array(a, N);
    destroy_string(text);

    return 0;
}
