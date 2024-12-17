#include <stdio.h>
#include <stdlib.h>
#include "avl.H"

int main(){

  arvore a = NULL;
  int opcao;
  int valor;
  int cresceu;
  int diminuiu;
  
  while(1){
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        scanf("%d", &valor);
        a = inserir(a, valor, &cresceu);
        break;
      case 2:
        imprimirPreOrdem(a);
        printf("\n");
        imprimirEmOrdem(a);
        break;
      case 3:
        scanf("%d", &valor);
        a = remover(a, valor, &diminuiu);
        break;
      case 99:
         exit(0);
         break;
    }
  }
  return 0;
}