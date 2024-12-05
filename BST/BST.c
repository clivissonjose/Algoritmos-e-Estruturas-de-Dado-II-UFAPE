#include <stdio.h>
#include <stdlib.h>
#include "BST.H"

arvore inserir(arvore  raiz, int valor){
  // caso base raiz é nula;
  if(raiz == NULL){

    // alocar espaço
    arvore novo = (arvore) malloc(sizeof(no));
    // Adicionar os dados
    novo->valor = valor;
    novo->dir  = NULL;
    novo->esq = NULL;

    // Retornar os dados
    return novo;

  }else{

    if(valor >= raiz->valor){
      raiz->dir = inserir(raiz->dir, valor);
    }else{
      raiz->esq = inserir(raiz->esq, valor);
    }

    return raiz;
  }
}

void imprimirPreOrdem(arvore raiz){
  if(raiz){
    printf("%d ", raiz->valor);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
  }
}

arvore maiorElemento(arvore raiz){
  arvore temp = raiz;

  if(temp == NULL){
    return temp;
  }
  while(temp->dir != NULL){
    temp = temp->dir;
  }

  return temp;
}

arvore remover(arvore raiz, int valor){

  if(raiz == NULL){
      return NULL;
  }else{
   
    // Verificar se o valor foi encontrado
    if(raiz->valor == valor){

      // Caso 1: O valor é uma folha
      if(raiz->dir == NULL && raiz->esq == NULL){
        free(raiz);
        return NULL;  
      }

      // caso 2a: Raiz possui exatamente um filho a direita
      if(raiz->dir != NULL && raiz->esq == NULL ){
         arvore raizResultante = raiz->dir;
         free(raiz);
         return raizResultante;
      }

      // caso 2b: A raiz possui exatemente um filho a esquerda
      if(raiz->esq != NULL && raiz->dir == NULL){
        arvore raizResultante = raiz->esq;
        free(raiz);
        return raizResultante;
      }

      // Caso 3: A raiz possui dois filhos
      if(raiz->dir != NULL && raiz->esq != NULL){

         // Vamos encontrar o maior valor da subarvore a esquerda e substituir-lo no valor da raiz
         raiz->valor = maiorElemento(raiz->esq)->valor;

         // Aqui removemos o maior valor da subarvore a esquerda que está duplicado.
         raiz->esq = remover(raiz->esq, raiz->valor);
         
         return raiz;  
      }

    }else{
      // Procurar pelo valor 

      if(valor >= raiz->valor){
        raiz->dir = remover(raiz->dir, valor);
      }else{
        raiz->esq = remover(raiz->esq, valor);
      }

      return raiz;
    }
     
  }
}