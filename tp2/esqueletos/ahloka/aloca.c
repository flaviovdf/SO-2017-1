// Esqueleto de um código de alocação de memória (novo maloc)
// Feito para a disciplina DCC065 - Sistemas Operacionais (UFMG)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Strategia de alocação como variável global. Feio mas funciona dado o
// esqueleto do TP.
static char *STRATEGY = NULL;

// Caso você utilize a lista fora da memória que vamos alocar a mesma
// terá que ser acessada como uma var global. Global vars in C.

void *aloca(size_t size) {
  if (strcmp(STRATEGY, "bf") == 0) {
    // Código de best fit aqui!
  }
  return NULL;
}

void libera(void *ptr) {
  if (strcmp(STRATEGY, "bf") == 0) {
    // Código de best fit aqui!
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage %s <algorithm>\n", argv[0]);
    exit(1);
  }
  STRATEGY = argv[1];
  int nops;
  scanf("%d\n", &nops);

  char *algorithms[] = {"ff", "bf", "wf", "nf"};
  int n_alg = 4;
  int valid = 0;
  for (int i = 0; i < n_alg; i++) {
    if (strcmp(STRATEGY, algorithms[i]) == 0) {
      valid = 1;
      break;
    }
  }
  if (valid == 0) {
    printf("Algoritmo inválido: Usage %s <algorithm>\n", argv[0]);
    printf("--onde o algoritmo vem das opções: {ff, bf, wf, nf}");
    exit(1);
  }

  void **variables = (void **) malloc(nops * sizeof(void**));
  for (int i = 0; i < nops; i++)
    variables[i] = NULL;

  int opid;    // ID da operação
  int memsize; // Tamanho da alocação
  char optype; // Tipo da operação
  void *addr;
  while (scanf("%d", &opid) == 1) {
    getchar();
    scanf("%d", &memsize);
    scanf("%c", &optype);
    if (optype == 'a') {         // Aloca!
      addr = aloca(memsize);
      variables[opid] = addr;
    } else if (optype == 'f') {  // Free!
      addr = variables[opid];
      free(addr);
    } else {
      printf("Erro na entrada");
      exit(1);
    }
  }

  for (int i = 0; i < nops; i++)
    if (variables[i] != NULL)
      free(variables[i]);
  free(variables);
}
