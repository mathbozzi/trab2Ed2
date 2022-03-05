#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "str.h"
#include "suffix.h"

int main(int argc, char *argv[]) {
	if (argc != 5) {
		printf("Execução: ./a.out [-aorcs] caminho_arquivo [contexto] [query]\n");
		return 0;
	}

	FILE *arqv_de_entrada = fopen(argv[2], "r");
	if (arqv_de_entrada == NULL) {
		printf("Erro ao abrir o arquivo de entrada\n");
		return 0;
	}
	int N;
	fscanf(arqv_de_entrada, "%d\n", &N);

	char *string = malloc(N * sizeof(char));
	int size = 0, flag = 0;
	//verifica caractere por caractere
	for (int i = 0; i < N; i++) {
		char l;
		fscanf(arqv_de_entrada, "%c", &l);
		if (l == '\n' || l == ' ') {
			flag = 1;
			continue;
		}
		if (flag) {
			flag = 0;
			string[size] = ' ';
			size++;
		}
		string[size] = l;
		size++;
	}

	String *finalString = malloc(sizeof *(finalString));
	finalString->c = malloc(size * sizeof(char));
	finalString->len = size;
	int size2 = 0;
	while (size2 < size) {
		finalString->c[size2] = string[size2];
		size2++;
	}
	int len = finalString->len;

	// print_string(finalString);
	free(string);
	fclose(arqv_de_entrada);

	// -------------- (a) --------------------
	Suffix **suffix = create_suf_array(finalString, len);
	// print_suf_array(suffix, len); //descomentar
	// -------------- (a) --------------------

	// -------------- (o) --------------------
	sort_suf_array(suffix, len);
	// print_suf_array(suffix, len);
	// -------------- (o) --------------------

	// -------------- (r) --------------------
	clock_t init, init2, final, final2;
	init = clock();
	sort_suf_array(suffix, len);  //metodo 1 (qsort)
	final = clock();
	// print_suf_array(suffix, len);
	double time = ((double) final - init) / CLOCKS_PER_SEC;
	printf("\n Ordenação qsort: %.3f\n", time);
	init2 = clock();
	// metodo 2 ainda falta fazer (ainda n sei)
	final2 = clock();
	// print_suf_array(suffix, len);
	double time2 = ((double)final2 - init2) / CLOCKS_PER_SEC;
	printf("\n Ordenação blbla: %.3f\n", time2);
	// -------------- (r) --------------------

	// -------------- (c) --------------------
	int context = atoi(argv[3]);
	String *query = create_string(argv[4]);
	// print_string(query);

	int r = rank(suffix, len, query);
	// printf("%d", r);
	for (int i = r; i < len; i++) {
		int var, var2, var3;
		if (query->len + suffix[i]->index > len) {
			var = len;
		} else {
			var = query->len + suffix[i]->index > len;
		}
		if (!equals_substring(finalString, suffix[i]->index, var, query)) {
			break;
		}

		if (suffix[i]->index - context < 0) {
			var2 = 0;
		} else {
			var2 = suffix[i]->index - context;
		}
		if ((query->len + context + suffix[i]->index) > len) {
			var3 = len;
		} else {
			var3 = (query->len + context + suffix[i]->index);
		}
		print_substring(finalString, var2, var3);
	}
	// destroy_string(finalString);
	destroy_string(query);
	// destroy_suf_array(suffix, N);
	// -------------- (c) --------------------

	// -------------- (s) --------------------
	char q[50];
	scanf("%s", q);
	String *queryScan = create_string(q);
	while (queryScan->len > 0) {
		int r = rank(suffix, len, queryScan);
		// printf("%d", r);
		for (int i = r; i < len; i++) {
			int var, var2, var3;
			if (queryScan->len + suffix[i]->index > len) {
				var = len;
			} else {
				var = queryScan->len + suffix[i]->index > len;
			}
			if (!equals_substring(finalString, suffix[i]->index, var, queryScan)) {
				break;
			}

			if (suffix[i]->index - context < 0) {
				var2 = 0;
			} else {
				var2 = suffix[i]->index - context;
			}
			if ((queryScan->len + context + suffix[i]->index) > len) {
				var3 = len;
			} else {
				var3 = (queryScan->len + context + suffix[i]->index);
			}
			print_substring(finalString, var2, var3);
		}
		destroy_string(queryScan);
		scanf("%s", q);
		queryScan = create_string(q);
	}
	// destroy_string(finalString);
	// destroy_suf_array(suffix, N);
	// -------------- (s) --------------------

	return 0;
}
