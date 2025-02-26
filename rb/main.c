#include <stdio.h>
#include <stdlib.h>
#include "rb.h"


int  main(){

  arvore a;
  inicializar(&a);

  while(1){
     
    int opcao;
    int valor;
    scanf("%d", &opcao);

    switch(opcao){
      case 1:
         scanf("%d", &valor);
         adicionar(valor, &a);
         break;
      case 2:
         in_order(a);
         printf("\n");
         break;
      case 5:
         scanf("%d", &valor);
         remover(valor, &a);
         break;
      case 99:
          exit(0);

    }
  }

  

}