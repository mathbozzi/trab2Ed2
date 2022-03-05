#include "suffix.h"

#include <stdio.h>
#include <stdlib.h>

Suffix** create_suf_array(String* text, int N) {
	Suffix** sufArray = malloc(N * sizeof(Suffix*));

	for (int i = 0; i < N; i++) {
		sufArray[i] = create_suffix(text, i);
	}
	return sufArray;
}

Suffix* create_suffix(String* s, int index) {
	Suffix* suf = malloc(sizeof *suf);
	suf->index = index;
	suf->s = s;
	return suf;
}

void print_suf_array(Suffix** a, int N) {
	for (int i = 0; i < N; i++) {
		print_suffix(a[i]);
	}
}
void print_suffix(Suffix* suf) {
	int n = suf->s->len - suf->index;
	for (int i = 0; i < n; i++) {
		if ((suf->index + i) < suf->s->len) {
			printf("%c", suf->s->c[suf->index + i]);
		}
	}
	printf("\n");
}
int cmpfunc(const void* a, const void* b) {
	int maxSize = 0;

	if (*((Suffix**)a) == *((Suffix**)b)) {
		return 0;
	}
	int sizeA = (*((Suffix**)a))->s->len - (*((Suffix**)a))->index;
	int sizeB = (*((Suffix**)b))->s->len - (*((Suffix**)b))->index;
	if (sizeA < sizeB) {
		maxSize = sizeA;
	} else {
		maxSize = sizeB;
	}

	for (int i = 0; i < maxSize; i++) {
		int aa = 0, bb = 0;
		if ((*((Suffix**)a))->index + i < (*((Suffix**)a))->s->len) {
			aa = (*((Suffix**)a))->s->c[(*((Suffix**)a))->index + i];
		}
		if ((*((Suffix**)b))->index + i < (*((Suffix**)b))->s->len) {
			bb = (*((Suffix**)b))->s->c[(*((Suffix**)b))->index + i];
		}

		if (aa > bb) {
			return 1;
		}
		if (aa < bb) {
			return -1;
		}
	}
	return sizeA - sizeB;
}

void sort_suf_array(Suffix** a, int N) {
	qsort(a, N, sizeof(Suffix*), cmpfunc);
}

int rank(Suffix** a, int N, String* query) {
	int i = 0;
	int j = N - 1;
	while (i <= j) {
		// int cmp = compare_to_suf(query, a[i + (j - i) / 2]);
		int end, result = 0;
		if (query->len < (a[i + (j - i) / 2]->s->len - a[i + (j - i) / 2]->index)) {
			end = query->len;
		} else {
			end = (a[i + (j - i) / 2]->s->len - a[i + (j - i) / 2]->index);
		}

		for (int k = 0; k < end; k++) {
			int flag;
			if ((a[i + (j - i) / 2]->index + k) < a[i + (j - i) / 2]->s->len) {
				flag = a[i + (j - i) / 2]->s->c[a[i + (j - i) / 2]->index + k];
			} else {
				flag = -1;
			}
			if (query->c[k] > flag) {
				result = 1;
				break;
			}
			if (query->c[k] < flag) {
				result = -1;
				break;
			}
		}
		if (result == 0) {
			result = query->len - (a[i + (j - i) / 2]->s->len - a[i + (j - i) / 2]->index);
		}

		if (result < 0) {
			j = (i + (j - i) / 2) - 1;
		} else if (result > 0) {
			i = (i + (j - i) / 2) + 1;
		} else {
			return (i + (j - i) / 2);
		}
	}
	return i;
}
