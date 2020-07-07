#include "operacoes.h"

int main(int argc, char **argv) {
  int a, b, sum;
  scanf("%d %d", &a, &b);
  sum = add(a, b);

  printf("%d\n", sum);
  // printf("Olá, seja bem vindo ao spell-checker!\n");
  // printf("Digite o nome do arquivo que deverá ser corrigido\n");
  // printf("Ou digite 'T' para digitar no terminal.\n");
  // printf("> ");

  // char fname[128];
  // scanf("%s", fname);

  
  // if (strlen(fname) == 1 && fname[0] == 'T') {
  //   printf("Digite o seu texto:\n");
  //   printf("> ");
  // }
}
