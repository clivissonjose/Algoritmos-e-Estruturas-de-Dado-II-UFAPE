#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

int main(){

  int opcao;
  int valor;

  arvore a = NULL;

  while(1){
    scanf("%d", &opcao);

    switch (opcao){
      case  1:
        scanf("%d", &valor);
        a = inserir(a, valor);
        break;

      case 2:
        imprimirPreOrdem(a);
        printf("\n");
        break;

      case 3:
        scanf("%d", &valor);
        a = remover(a, valor);
        break;
      case 4:
        printf("%d ", maiorElemento(a)->valor);
        break;

      case 5:
        printf("%d ", altura(a));
        break;

      case 99:
        exit(0);
        break;
    }
  }

  return 0;
}