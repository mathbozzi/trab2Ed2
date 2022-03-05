#include <stdio.h>
#include <stdlib.h>

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

	Suffix **suffix = create_suf_array(finalString, len);
	// print_suf_array(suffix, len);
	clock_t init, final;
	init = clock();
	sort_suf_array(suffix, len);
	final = clock();
	// print_suf_array(suffix, len);

	String *query = create_string(argv[4]);
	// print_string(query);
	int context = atoi(argv[3]);

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
	destroy_string(finalString);
	destroy_string(query);
	// destroy_suf_array(suffix, N);

	return 0;
}
