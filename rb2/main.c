#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int ler_valor() {
    int x;
    printf("Insira o valor: ");
    scanf("%d", &x);
    return x;
}

int main(int argc, char * argv[]) {
    arvore a;
    int opcao;
    inicializar(&a);
    
    while(1) {
        // printf("\n1 - inserir\n2 - preorder\n3 - inorder\n4 - posorder \n5 - remover\n99 - sair\n");
        // printf("\nInsira a opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            int valor;
        case 1:
            scanf("%d", &valor);
            adicionar(valor, &a);
            break;
        case 2:
            in_order(a);
            printf("\n");
            break;

        case 3:
            scanf("%d", &valor);
            remover(valor, &a);
            break;
        case 99:
            exit(0);
        }
    }
}
