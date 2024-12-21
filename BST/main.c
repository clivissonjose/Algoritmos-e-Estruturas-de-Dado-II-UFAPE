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
        imprimirEmOrdem(a);
        printf("\n");
        break;
      case 4:
       imprimirPosOrdem(a);
       printf("\n");
       break;

      case 5:
        // Imprimir elementos de uma BST em forma decrescente
        reverso(a);

        printf("\n");
        break;
      case 6:
         printf("%d\n", altura(a));
         break;
      case 7:
         //Quantidades de folhas de uma BST
         printf("%d\n", qtdFolhas(a));
         break;
        
      case 8: 
        //  Recebe como parâmetro o ponteiro para uma árvore BST e o valor de uma
        //  chave de procura. A função deve imprimir o caminho do nó raiz até o nó
        //  específico passado como parâmetro, caso a chave não exista, imprima apenas
        //  ‘\n’. Ex: [2][1]
         scanf("%d", &valor);
         caminho(a, valor);
         printf("\n");
         break;
      case 9:
          scanf("%d", &valor);
          a = remover(a, valor);
          break;
      case 10:
         scanf("%d", &valor);
         printf("Soma: %d\n", somaCaminho(a, valor));
         break;

      case 99:
        exit(0);
        break;
    }
  }

  return 0;
}