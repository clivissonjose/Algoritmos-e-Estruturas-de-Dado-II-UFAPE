#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

arvore inserir(arvore  raiz, int valor, int *cresceu){
  // caso base raiz é nula;
  if(raiz == NULL){

    // alocar espaço
    arvore novo = (arvore) malloc(sizeof(no_avl));
    // Adicionar os dados
    novo->valor = valor;
    novo->fb = 0;
    novo->dir  = NULL;
    novo->esq = NULL;

    *cresceu = 1;
    // Retornar os dados
    return novo;

  }else{

    if(valor >= raiz->valor){
      raiz->dir = inserir(raiz->dir, valor, cresceu);

             //Após adicionar o elemento na direita, 
        //verifica se a sub-árvore da direita cresceu.
        //Em caso afirmativo, ajusta-se o fator de balanço 
        //da raiz relativa

        if(*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacionar(raiz);
                        break;
                    case -1:
                         raiz->fb = 0;
                        *cresceu = 0;
                        break;

                }


            }
    }else{
      raiz->esq = inserir(raiz->esq, valor, cresceu);

      if(*cresceu){
        switch(raiz->fb){
          case -1:
             *cresceu = 0;
             return rotacionar(raiz);
             break;
          case 0:
             raiz->fb = -1;
             *cresceu = 1;
             break;
          case 1:
             raiz->fb = 0;
             *cresceu = 0;
             break;
        }
      }
    }

    return raiz;
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

arvore rotacionar(arvore raiz){
   
   if(raiz->fb>0){
      // rotacao  a esquerda
      if(raiz->dir->fb >= 0){
        return rotacaoSimplesEsquerda(raiz);
      }else{
        return rotacaoDuplaEsquerda(raiz);
      }

   }else{
    // Rotacao Direita - IMPLEMENTAR

      if (raiz->esq->fb <= 0) {
            return rotacaoSimplesDireita(raiz);
      } else {
            return rotacaoDuplaDireita(raiz);
      }
   }
}

/*
     p
    / \
   t1  u
      / \
     t2 t3

     u
    / \
   p   t3
  / \
 t1 t2

*/
arvore rotacaoSimplesEsquerda(arvore raiz){

   arvore p, u, t2;
    //inicializar
    p = raiz;
    u = p->dir;
    t2 = u->esq;

        //Atualizar os ponteiros com o estado resultante
    u->esq = p;
    p->dir = t2;

    if(u->fb == 1) {
      p->fb = 0;
      u->fb = 0;
	  } else {
      p->fb = 1;
      u->fb = -1;
	  }	
    
  /*  if(u->fb == 0 ){
        p->fb = 1;
        u->fb = 0;
      }else{
        p->fb = 0;
        u->fb = 0;
      }  */
    return u;  

}

arvore rotacaoSimplesDireita(arvore raiz){

    arvore p, u, t2;
    // Inicializar os ponteiros
    p = raiz;        // p é o nó desbalanceado (raiz atual)
    u = p->esq;      // u é a subárvore esquerda de p
    t2 = u->dir;     // t2 é a subárvore direita de u

    // Atualizar os ponteiros com o estado resultante
    u->dir = p;      // u se torna a nova raiz
    p->esq = t2;     // t2 se torna a subárvore esquerda de p

    // Atualizar os fatores de balanceamento
      if (u->fb == -1) {
        p->fb = 0;
        u->fb = 0;
      } else {
        p->fb = -1;
        u->fb = 1;
      }

      
    // Retornar a nova raiz
    return u;

}

arvore rotacaoDuplaEsquerda(arvore raiz){

    arvore p = raiz;
    // Primeira rotação: Simples à direita na subárvore direita
    p->dir = rotacaoSimplesDireita(p->dir);
    // Segunda rotação: Simples à esquerda na raiz
    return rotacaoSimplesEsquerda(p);
   
}

arvore rotacaoDuplaDireita(arvore raiz){

  arvore p = raiz;
    // Primeira rotação: Simples à esquerda na subárvore esquerda
  p->esq = rotacaoSimplesEsquerda(p->esq);
    // Segunda rotação: Simples à direita na raiz
  return rotacaoSimplesDireita(p);

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

arvore remover(arvore raiz, int valor, int *diminuiu){

  if(raiz == NULL){
      return NULL;
  }else{
   
    // Verificar se o valor foi encontrado
    if(raiz->valor == valor){

      // Caso 1: O valor é uma folha
      if(raiz->dir == NULL && raiz->esq == NULL){
        *diminuiu = 1;
        free(raiz);
        return NULL;  
      }

      // caso 2a: Raiz possui exatamente um filho a direita
      if(raiz->dir != NULL && raiz->esq == NULL ){
        *diminuiu = 1;
         arvore raizResultante = raiz->dir;
         free(raiz);
         return raizResultante;
      }

      // caso 2b: A raiz possui exatemente um filho a esquerda
      if(raiz->esq != NULL && raiz->dir == NULL){
        *diminuiu = 1;
        arvore raizResultante = raiz->esq;
        free(raiz);
        return raizResultante;
      }

      // Caso 3: A raiz possui dois filhos
      if(raiz->dir != NULL && raiz->esq != NULL){

         // Vamos encontrar o maior valor da subarvore a esquerda e substituir-lo no valor da raiz
         raiz->valor = maiorElemento(raiz->esq)->valor;

         // Aqui removemos o maior valor da subarvore a esquerda que está duplicado.
         raiz->esq = remover(raiz->esq, raiz->valor, diminuiu);
         
         return raiz;  
      }

    }else{
      // Procurar pelo elemento 

      if(valor >= raiz->valor){
        raiz->dir = remover(raiz->dir, valor, diminuiu);

        if(*diminuiu){
          switch(raiz->fb){
            case 0:
               raiz->fb = -1;
               *diminuiu = 0;
               break;
            case 1:
                raiz->fb = 0;
                *diminuiu = 1;
                break;
            case -1:
                //*diminuiu ???
                return rotacionar(raiz);
                break;
          }
        }

        
      }else{
        raiz->esq = remover(raiz->esq, valor, diminuiu);

        if(*diminuiu){
          switch(raiz->fb){
            
          }
        }
      }

      return raiz;
    }
     
  }
}

// Impressões 
void imprimirPreOrdem(arvore raiz){
  if(raiz){
    printf("%d ", raiz->valor);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
  }
}

void imprimirEmOrdem(arvore raiz){
  if(raiz){  
    imprimirEmOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    imprimirEmOrdem(raiz->dir);
  }
}
void imprimirPosOrdem(arvore raiz){

  if(raiz){
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d ", raiz->valor);
  }
}