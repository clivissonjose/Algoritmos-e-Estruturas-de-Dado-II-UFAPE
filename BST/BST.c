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
    printf("[%d]", raiz->valor);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
  }

}

void imprimirEmOrdem(arvore raiz){
  if(raiz){  
    imprimirEmOrdem(raiz->esq);
    printf("[%d]", raiz->valor);
    imprimirEmOrdem(raiz->dir);
  }
}
void imprimirPosOrdem(arvore raiz){

  if(raiz){
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("[%d]", raiz->valor);
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

int altura(arvore raiz){
  
   if(raiz == NULL){
     return 0;
   }

   int alturaDireita = altura(raiz->dir);
   int alturaEsquerda = altura(raiz->esq);

   return 1 + (alturaDireita > alturaEsquerda ? alturaDireita : alturaEsquerda);
}

int somaCaminho(arvore raiz, int valor){

      if(raiz == NULL){
        return 0;
      }

      if(raiz->valor == valor){
        return valor;
      }

      if(valor >= raiz->valor){
        int soma = 0;
        soma += somaCaminho(raiz->dir, valor);

        if(soma != 0){
          return soma + raiz->valor;
        }

        return 0;
      }else{
        int soma = 0;
        soma += somaCaminho(raiz->esq, valor);

        if(soma != 0){
          return soma + raiz->valor;
        }

        return 0;
      }
}

void caminho(arvore raiz, int valor){

  int valorExistente = valorExiste(raiz, valor);

  if(valorExistente){

        if(raiz->valor == valor){
          printf("[%d]", raiz->valor);
          return ;
        }

        printf("[%d]", raiz->valor);
        if(valor >= raiz->valor){
          caminho(raiz->dir, valor);
        }

        if(valor < raiz->valor){
           caminho(raiz->esq, valor);
        }

  }

}

// Quantidade de folhas em uma arvore BST
int qtdFolhas(arvore raiz){

    if (raiz == NULL)
       return 0;
    if(raiz->esq == NULL && raiz->dir == NULL){
         return 1;
    }

    int folhas = 0;
    folhas += qtdFolhas(raiz->esq);
    folhas += qtdFolhas(raiz->dir);

    return folhas;

}

// Pegar o números de uma BST em ordem decrescente
void reverso(arvore raiz){
  if(raiz == NULL){
    return;
  }

  reverso(raiz->dir);
  printf("[%d]", raiz->valor);
  reverso(raiz->esq);
}

// Se valor existir retorna 1 se não retorna 0
int valorExiste(arvore raiz, int valor){

  if(raiz==NULL){
    return 0;
  }

  if(raiz->valor == valor){
    return 1;
  }

  if(valor >= raiz->valor){
    return valorExiste(raiz->dir, valor);
  }

  return valorExiste(raiz->esq, valor);

}