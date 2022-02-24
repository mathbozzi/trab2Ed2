#include <stdio.h>
#include <stdlib.h>
#include "suffix.h"

#define suf_len(SUF) (SUF->s->len - SUF->index)

#define char_at(SUF, D) (((SUF->index + D) < SUF->s->len) ? \
                          SUF->s->c[SUF->index + D] : -1)

Suffix* create_suffix(String *s, int index) {
    Suffix *suf = malloc(sizeof *suf);
    suf->s = s;
    suf->index = index;
    return suf;
}

void destroy_suffix(Suffix *suf) {
    free(suf);
}

void print_suffix(Suffix *suf) {
    for (int i = 0; i < suf_len(suf); i++) {
        printf("%c", char_at(suf, i));
    }
}

Suffix** create_suf_array(String *text, int N) {
    Suffix* *a = malloc(N * sizeof(Suffix*));
    for (int i = 0; i < N; i++) {
        a[i] = create_suffix(text, i);
    }
    return a;
}

void destroy_suf_array(Suffix* *a, int N) {
    for (int i = 0; i < N; i++) {
        destroy_suffix(a[i]);
    }
    free(a);
}

void print_suf_array(Suffix* *a, int N) {
    for (int i = 0; i < N; i++) {
        print_suffix(a[i]);
        printf("\n");
    }
}

int compare_suf_sys(const void *p1, const void *p2) {
    Suffix *s1 = *((Suffix**) p1);
    Suffix *s2 = *((Suffix**) p2);
    if (s1 == s2) return 0;
    int N = suf_len(s1) < suf_len(s2) ? suf_len(s1) : suf_len(s2);
    for (int i = 0; i < N; i++) {
        if (char_at(s1, i) < char_at(s2, i)) { return -1; }
        if (char_at(s1, i) > char_at(s2, i)) { return +1; }
    }
    return suf_len(s1) - suf_len(s2);
}

void sort_suf_array_sys(Suffix* *a, int N) {
    qsort(a, N, sizeof(Suffix*), compare_suf_sys);
}

#define R 256

void count_sort(Suffix* *a, Suffix* *aux, int *count,
                int lo, int hi, int d) {
    for (int i = lo; i <= hi; i++) {  // Count frequencies.
        count[char_at(a[i], d) + 2]++;
    }
    for (int r = 0; r < R+1; r++) {   // Compute cumulates.
        count[r+1] += count[r];
    }
    for (int i = lo; i <= hi; i++) { // Move items.
        int p = count[char_at(a[i], d) + 1]++;
        aux[p] =  a[i];
    }
    for (int i = lo; i <= hi; i++) { // Copy back.
        a[i] = aux[i - lo];
    }
}

int compare_suf(Suffix *s1, Suffix *s2, int d) {
    if (s1 == s2) return 0;
    int N = suf_len(s1) < suf_len(s2) ? suf_len(s1) : suf_len(s2);
    for (int i = d; i < N; i++) {
        if (char_at(s1, i) < char_at(s2, i)) { return -1; }
        if (char_at(s1, i) > char_at(s2, i)) { return +1; }
    }
    return suf_len(s1) - suf_len(s2);
}

#define less_from(A, B, d)  (compare_suf(A, B, d) < 0)
#define exch(A, B)          { Suffix* t = A; A = B; B = t; }

void insert_sort_from(Suffix* *a, int lo, int hi, int d) {
  for (int i = lo; i <= hi; i++) {
    for (int j = i; j > lo && less_from(a[j], a[j-1], d); j--) {
       exch(a[j], a[j-1]);
    }
  }
}

#define CUTOFF 20

void rec_MSD(Suffix* *a, Suffix* *aux, int lo, int hi, int d) {
    if (hi <= lo + CUTOFF - 1) {
        insert_sort_from(a, lo, hi, d);
        return;
    }

    // +2: Start counting from 1, other +1 for end of string marker.
    int *count = calloc(R+2, sizeof(int));
    count_sort(a, aux, count, lo, hi, d); // Key-indexed counting.

    for (int r = 1; r < R+1; r++) { // Sort R subarrays recursively.
        rec_MSD(a, aux, lo + count[r], lo + count[r+1] - 1, d+1);
    }

    free(count);
}

void sort_suf_array_msd(Suffix* *a, int N) {
    Suffix* *aux = malloc(N * sizeof(Suffix*));
    rec_MSD(a, aux, 0, N-1, 0);
    free(aux);
}

int compare_to_suf(String *query, Suffix *suffix) {
    int N = query->len < suf_len(suffix) ? query->len : suf_len(suffix);
    for (int i = 0; i < N; i++) {
        if (query->c[i] < char_at(suffix, i)) { return -1; }
        if (query->c[i] > char_at(suffix, i)) { return +1; }
    }
    return query->len - suf_len(suffix);
}

int rank(Suffix* *a, int N, String *query) {
    int lo = 0;
    int hi = N - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = compare_to_suf(query, a[mid]);
        if      (cmp < 0) { hi = mid - 1; }
        else if (cmp > 0) { lo = mid + 1; }
        else return mid;
    }
    return lo;
}
