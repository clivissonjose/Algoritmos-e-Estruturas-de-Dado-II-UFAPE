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


arvore rotacaoSimplesEsquerda(arvore raiz){

   arvore p, u, t2;
    //inicializar
    p = raiz;
    u = p->dir;
    t2 = u->esq;

        //Atualizar os ponteiros com o estado resultante
    u->esq = p;
    p->dir = t2;

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

arvore rotacionar(arvore raiz){
    arvore p = raiz;
   if (p->fb > 0) {
    // Rotacao simples a esquerda
        arvore u = p->dir;        
      
        if (u->fb >= 0) {
            if (u->fb == 1) {
                p->fb = 0;
                u->fb = 0;
        } else {
                p->fb = 1;
                u->fb = -1;
        }
        return rotacaoSimplesEsquerda(raiz);
            
        } else {
          /// Rotacao dupla a esquerda
            arvore v = u->esq;

            if (v->fb == -1) {
                p->fb = 0;
                u->fb = 1;
                v->fb = 0;
            } else if (v->fb == 0) {
                p->fb = 0;
                u->fb = 0;
                v->fb = 0;
            } else if (v->fb == 1) {
                p->fb = -1;
                u->fb = 0;
                v->fb = 0;
            }

          return rotacaoDuplaEsquerda(raiz);

        }
   }else{
      
        
        arvore u = p->esq;        

        if (u->fb <= 0) {
            if (u->fb == -1) {
                p->fb = 0;
                u->fb = 0;
            } else {
                p->fb = 1;
                u->fb = -1;
            }
            return rotacaoSimplesDireita(raiz);

        } else {
            arvore v = u->dir;

            if (v->fb == -1) {
                p->fb = 1;
                u->fb = 0;
                v->fb = 0;
            } else if (v->fb == 0) {
                p->fb = 0;
                u->fb = 0;
                v->fb = 0;
            } else if (v->fb == 1) {
                p->fb = 0;
                u->fb = -1;
                v->fb = 0;
            }
            return rotacaoDuplaDireita(raiz);
   }
   }
}
void avlRemove(arvore *raiz, int valor, int *diminuiu) {
    if (*raiz == NULL) {
        *diminuiu = 0;
        return;
    } else if (valor == (*raiz)->valor) {
        *diminuiu = 1;

        // Caso 1: Nó a ser removido é uma folha
        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            free(*raiz);
            *raiz = NULL;
        }
        // Caso 2: Nó a ser removido tem apenas o filho esquerdo
        else if ((*raiz)->esq != NULL && (*raiz)->dir == NULL) {
            arvore temp = *raiz;
            *raiz = (*raiz)->esq;
            free(temp);
        }
        // Caso 3: Nó a ser removido tem apenas o filho direito
        else if ((*raiz)->esq == NULL && (*raiz)->dir != NULL) {
            arvore temp = *raiz;
            *raiz = (*raiz)->dir;
            free(temp);
        }
        // Caso 4: Nó a ser removido tem dois filhos
        else {
            arvore esqmost = (*raiz)->esq;
            while (esqmost->dir != NULL) {
                esqmost = esqmost->dir;
            }

            // Substitui o valor do nó a ser removido pelo maior da subárvore esquerda
            (*raiz)->valor = esqmost->valor;

            // Remove o maior da subárvore esquerda
            avlRemove(&(*raiz)->esq, esqmost->valor, diminuiu);

            // Ajuste do fator de balanceamento após a remoção
            if (*diminuiu) {
                if ((*raiz)->fb == -1) {
                    (*raiz)->fb = 0;
                    *diminuiu = 1;
                } else if ((*raiz)->fb == 0) {
                    (*raiz)->fb = 1;
                    *diminuiu = 0;
                } else if ((*raiz)->fb == 1) {
                    *raiz = rotacionar(*raiz);
                }
            }
        }
    }
    // Se o valor a ser removido for menor que o valor do nó atual
    else if (valor < (*raiz)->valor) {
        avlRemove(&(*raiz)->esq, valor, diminuiu);

        // Ajuste do fator de balanceamento após a remoção
        if (*diminuiu) {
            if ((*raiz)->fb == -1) {
                (*raiz)->fb = 0;
                *diminuiu = 1;
            } else if ((*raiz)->fb == 0) {
                (*raiz)->fb = 1;
                *diminuiu = 0;
            } else if ((*raiz)->fb == 1) {
                *raiz = rotacionar(*raiz);
            }
        }
    }
    // Se o valor a ser removido for maior que o valor do nó atual
    else {
        avlRemove(&(*raiz)->dir, valor, diminuiu);

        // Ajuste do fator de balanceamento após a remoção
        if (*diminuiu) {
            if ((*raiz)->fb == -1) {
                *raiz = rotacionar(*raiz);
            } else if ((*raiz)->fb == 0) {
                (*raiz)->fb = -1;
                *diminuiu = 0;
            } else if ((*raiz)->fb == 1) {
                (*raiz)->fb = 0;
                *diminuiu = 1;
            }
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
    printf("[%d fb=%d]", raiz->valor, raiz->fb);
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