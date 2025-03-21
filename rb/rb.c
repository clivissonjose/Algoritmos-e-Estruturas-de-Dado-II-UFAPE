#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

/*
Inicializa a árvore vazia com a raiz = null e inicializa o nó nulo duplo preto que será utilizado no método remover.
*/
void inicializar(arvore *raiz) {

      *raiz = NULL;
      no_null = (arvore) malloc(sizeof(struct no_bst));
      no_null->cor = DUPLO_PRETO;
      no_null->dado = 0;
      no_null->esq = NULL;
      no_null->dir = NULL;

}

/* Adiciona um novo elemento na árvore.
Parâmetros:
    valor   - elemento a ser adicionado
    raiz    - árvore onde o elemento será adicionado. 
              Observe que este parâmetro é um ponteiro de ponteiro
*/
void adicionar (int valor, arvore *raiz) {
  // posicao é uma variável auxiliar, 
    arvore posicao, pai, novo;
      //utiliza-se *raiz, por ser um ponteiro de ponteiro
    posicao = *raiz;
    pai = NULL;

	/*navega na árvore até encontrar a posição vaga apropriada para o elemento,
		nesta "descida" é necessário manter o ponteiro para o pai, pois após encontrar 
		a posição vaga (NULL) não seria possível navegar para o pai
     com o ponteiro posicao->pai */

	 while(posicao != NULL) {
			pai = posicao;
			if(valor > posicao->dado) 
					posicao = posicao->dir;
			else 
					posicao = posicao->esq;
	 }


      //Após achar a posição, inicializa o novo elemento
    novo = (arvore) malloc(sizeof(struct no_bst));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

      //Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
      //Observe novamente o uso do ponteiro de ponteiro
    if(eh_raiz(novo))	
        *raiz = novo;
    else {
          //Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento
      if(valor > pai->dado)
        pai->dir = novo;
      else
        pai->esq = novo;
    }

      //Após inserir, verifica e ajusta a árvore resultante
    ajustar(raiz, novo);

}

/* Verifica se a árvore está obedecendo todas as regras da RB e aplica as correções necessárias após a inserção.
Parâmetros:
    raiz - raiz (absoluta) da árvore
    elemento - nó recentemente inserido que pode ter causado o desajuste da árvore
*/
void ajustar(arvore *raiz, arvore elemento){

  //A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
  //Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário

    while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {

        //caso 1: Cor do tio é vermelha, desce o preto do avô
        if(cor(tio(elemento)) == VERMELHO) {
          tio(elemento)->cor = PRETO;
          elemento->pai->cor = PRETO;
          elemento->pai->pai->cor = VERMELHO;
          //Continua a verificação a partir do avô, que mudou para vermelho e pode ter 
          //gerado uma sequência vermelho-vermelho				
          elemento = elemento->pai->pai;
          //printf("Elemento: %d \n", elemento->dado);
          continue;
        } 
        //caso 2a: rotação simples direita
        if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
           // printf("Rotacao simples direita 2a\n");
            rotacao_simples_direita(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->dir->cor = VERMELHO;
            // printf("Imprimindo raiz após rotacao simples direita: \n ");
            // imprimir_elemento(*raiz);
            continue;
        }
        //caso 2b: rotação simples esquerda
        if(!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
          //  printf("Rotacao simples esquerda 2b\n");
            rotacao_simples_esquerda(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->esq->cor = VERMELHO;

            // printf("Imprimindo raiz após rotacao simples esquerda: \n ");
            // imprimir_elemento(*raiz);
            continue;
        }
        // //caso 3a: rotação dupla direita

        if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
          //printf("Rotacao dupla direita 3a\n");
          rotacao_simples_esquerda(raiz, elemento->pai);
          rotacao_simples_direita(raiz, elemento->pai);
                // printf("Elemento: %d\n",elemento->dado);
                // int esq = elemento->esq->dado;
                // int dir = elemento->dir->dado;
                // printf("Elemento->esq: %d\n", esq);
                // printf("Elemento->dir: %d\n", dir);
          
         elemento->cor = PRETO;
         elemento->dir->cor = VERMELHO;

         continue;
        
        }

        // //caso 3b: rotação dupla esqurda
        if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
        //  printf("Rotacao dupla esquerda 3b\n");
          rotacao_simples_direita(raiz, elemento->pai);
          rotacao_simples_esquerda(raiz, elemento->pai);
            // printf("Elemento: %d\n",elemento->dado);
            //     int esq = elemento->esq->dado;
            //     int dir = elemento->dir->dado;
            //     printf("Elemento->esq: %d\n", esq);
            //     printf("Elemento->dir: %d\n", dir);
          elemento->cor = PRETO;
          elemento->esq->cor = VERMELHO;
          // elemento->esq->cor = VERMELHO;

          continue;

        }


    }
  //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
  (*raiz)->cor = PRETO;
}

/* Realiza a rotação simples direita
Antes da rotação: 
cor(p) = Preto
cor(u) = cor(v) = Vermelho

     p             u
    / \           / \
   u  t2   =>    v   p
  / \               / \
 v  t1             t1 t2

Após aa rotação: 
cor(u) = Preto
cor(v) = cor(p) = Vermelho
*/
void rotacao_simples_direita(arvore *raiz, arvore pivo){
    arvore u, t1;
    u = pivo->esq;
    t1 = u->dir;

    /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito*/
    int posicao_pivo_esq = eh_filho_esquerdo(pivo);
    
    //Atualização dos ponteiros
    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    pivo->esq = t1;
    if(t1 != NULL)
        t1->pai = pivo;

    // u->dir = pivo;

    // u->pai = pivo->pai;
    // pivo->pai = u;

    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if(eh_raiz(u))
      *raiz = u;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if(posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo) {
    arvore u, t1;
    u=  pivo->dir;
    t1 = u->esq;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    pivo->dir = t1;

    if(t1 != NULL) t1->pai = pivo; 

    // u->esq = pivo;

    // u->pai = pivo->pai;
    // pivo->pai = u;

       //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if(eh_raiz(u)) *raiz = u;
    else {
         //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
         if(posicao_pivo_esq)
             u->pai->esq = u;
         else
             u->pai->dir = u;
     }

}

/*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
enum cor cor(arvore elemento) {
    enum cor c;

    if(elemento==NULL)
      return PRETO;
    else
      return elemento->cor;

    return c;
}

/*Verifica se um nó é a raiz da árvore*/
int eh_raiz(arvore elemento) {
    return (elemento->pai == NULL);  
}
/*Verifica se um nó é filho esquerdo*/
int eh_filho_esquerdo(arvore elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvore elemento){
  return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvore tio(arvore elemento) {
   return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {

    if(eh_filho_esquerdo(elemento))
      return elemento->pai->dir;
    else
      return elemento->pai->esq;

}

void imprimir(arvore raiz) {
    printf("(");
    if(raiz != NULL) {
      imprimir_elemento(raiz);
      imprimir(raiz->esq);
      imprimir(raiz->dir);
    }
    printf(")");
}


int altura(arvore raiz) {
    if(raiz == NULL) {
      return 0;
    }
    return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
    if(a > b)
      return a;
    else
      return b;
}

int maior_elemento(arvore raiz) {
    if(raiz == NULL)
        return -1;
    if(raiz->dir == NULL)
        return raiz->dado;
    else
        return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
    if(raiz == NULL)
        return -1;
    if(raiz->esq == NULL)
        return raiz->dado;
    else
        //return maior_elemento(raiz->esq); erro de Igor( ou não hahah)
        return menor_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
    if(raiz != NULL) {
      imprimir_elemento(raiz);
      pre_order(raiz->esq);
      pre_order(raiz->dir);
    }
}

void pos_order(arvore raiz) {
    if(raiz != NULL) {
      pos_order(raiz->esq);
      pos_order(raiz->dir);
      imprimir_elemento(raiz);
    }
}

void in_order(arvore raiz) {
    if(raiz != NULL) {
      in_order(raiz->esq);
      imprimir_elemento(raiz);
      in_order(raiz->dir);
    }
}

// void imprimir_elemento(arvore raiz) {
//     switch(raiz->cor){
//       case PRETO:
//         printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
//         break;
//       case VERMELHO:
//         printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
//         break;
//       case DUPLO_PRETO:
//         printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
//         break;
//     }
// }


// Ajustar o imprimir_elemento para ficar de acordo com 
// o que é pedido na lista de exercícios
void imprimir_elemento(arvore raiz) {
  switch(raiz->cor){
    case PRETO:
      printf("[%d B]", raiz->dado);
      break;
    case VERMELHO:
      printf("[%d R]", raiz->dado);
      break;
   
  }
}


void remover(tipo_dado valor, arvore *raiz) {
	arvore posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado) {
			if(posicao->esq == NULL && posicao->dir == NULL) {
				if(eh_raiz(posicao)) {
					*raiz = NULL;
                    free(posicao);
					break;
				}
				if(posicao->cor == VERMELHO) {
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;

                    free(posicao);
					break;
				}
				else {
                    no_null->cor = DUPLO_PRETO;
                    no_null->pai = posicao->pai;

                    if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = no_null;
                    else
                        posicao->pai->dir = no_null;

                    free(posicao);
                    reajustar(raiz, no_null);
                    break;
				}
			}
			if(posicao->esq == NULL && posicao->dir != NULL) {
				posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;

				if(eh_raiz(posicao))
					*raiz = posicao->dir;
				else {
					if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = posicao->dir;
					else
                        posicao->pai->dir = posicao->dir;
				}
                free(posicao);
				break;
			}
			if(posicao->esq != NULL && posicao->dir == NULL) {
				posicao->esq->cor = PRETO;
                posicao->esq->pai = posicao->pai;

				if(eh_raiz(posicao))
					*raiz = posicao->esq;
				else {
					if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = posicao->esq;
					else
                        posicao->pai->dir = posicao->esq;
				}
                free(posicao);
				break;
			}
            else {
                posicao->dado = maior_elemento(posicao->esq);
                valor = posicao->dado;
            }
		}
		if(valor > posicao->dado)
            posicao = posicao->dir;
		else
            posicao = posicao->esq;
	}
}
/*
Funcao para imprimir  cores dos nós
*/
void imprimir_cor(arvore elemento) {
  enum cor c = cor(elemento);
  
  switch (c) {
      case VERMELHO:
          printf("A cor do nó é VERMELHO\n");
          break;
      case PRETO:
          printf("A cor do nó é PRETO\n");
          break;
      case DUPLO_PRETO:
          printf("A cor do nó é DUPLO_PRETO\n");
          break;
      default:
          printf("Cor desconhecida\n");
  }
}


/*Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, ou seja, 
   elimina o nó null o duplo-preto.*/

void reajustar(arvore *raiz, arvore elemento){
    //	cor(irmao(elemento)->dir), cor(irmao(elemento)->esq));
    //caso 1	
    if(eh_raiz(elemento)) {
    //		printf("caso 1\n");
          elemento->cor = PRETO;
          if(elemento == no_null) {
              *raiz = NULL;
          }
          return;
     }

    //caso 2
    if(cor(elemento->pai) == PRETO && cor(irmao(elemento)) == VERMELHO &&
       cor(irmao(elemento)->dir) == PRETO && cor(irmao(elemento)->esq) == PRETO ) {
           
        //printf("Caso 2\n");
          //Verifica se é o caso 2 esquerdo ou direito
          if(eh_filho_esquerdo(elemento))
              rotacao_simples_esquerda(raiz, elemento->pai);
          else
              rotacao_simples_direita(raiz, elemento->pai);	
          
          elemento->pai->pai->cor = PRETO;
          elemento->pai->cor = VERMELHO;
          
          // Atenção à chamada recursiva do reajustar.
          // O caso 2 não remove o duplo-preto
          reajustar(raiz, elemento);
          return;
    }

    // //caso 3
    if(cor(elemento->pai) == PRETO && cor(irmao(elemento)) == PRETO &&
       cor(irmao(elemento)->dir) == PRETO && cor(irmao(elemento)->esq) == PRETO) {

         irmao(elemento)->cor = VERMELHO;
         elemento->pai->cor = DUPLO_PRETO;
         retira_duplo_preto(raiz, elemento);
          //Verificar e remover o no_null
          //Chamada recursiva para eliminar o duplo preto do elemento P
        reajustar(raiz, elemento->pai);
        return ;
    }	

    // caso 4
    if(cor(elemento->pai) == VERMELHO && cor(irmao(elemento)) == PRETO &&
       cor(irmao(elemento)->dir) == PRETO && cor(irmao(elemento)->esq) == PRETO){
        
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        return;
    }

      // Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
      //caso 5a
      if(eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq)== VERMELHO && cor(irmao(elemento)->dir) == PRETO) {	
        
        rotacao_simples_direita(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->dir->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
      }

      // //caso 5b
      if(!eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->dir) == VERMELHO && cor(irmao(elemento)->esq) ==  PRETO) {	
          // printf("Caso 5b\n");

          rotacao_simples_esquerda(raiz, irmao(elemento));
          irmao(elemento)->cor = PRETO;
          irmao(elemento)->esq->cor = VERMELHO;
          reajustar(raiz, elemento);
          return;
      }

     //caso 6a
	   if(eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->dir) == VERMELHO){
        // printf("Caso 6a\n");

          rotacao_simples_esquerda(raiz, elemento->pai);
          elemento->pai->pai->cor = elemento->pai->cor;

          elemento->pai->cor = PRETO;
          tio(elemento)->cor = PRETO;
          retira_duplo_preto(raiz, elemento);
          return;

      }

    //caso 6b
    // printf("caso 6b antes...\n");
    // printf("Filho esquerdo: %d\n", !eh_filho_esquerdo(elemento));
    // printf("Cor do imao do elemento: ");
    // imprimir_cor(irmao(elemento));
    // printf("\n");
    // printf("Cor do sobrinho esquerdo: ");
    // imprimir_cor(irmao(elemento));
    // printf("\n");
    if(!eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == VERMELHO){

          
          rotacao_simples_direita(raiz, elemento->pai);
       
          elemento->pai->pai->cor = elemento->pai->cor;

          elemento->pai->cor = PRETO;
          tio(elemento)->cor = PRETO;
          retira_duplo_preto(raiz, elemento);
          return;

    }

}


void retira_duplo_preto(arvore *raiz, arvore elemento) {
    if(elemento == no_null)
      if(eh_filho_esquerdo(elemento))
          elemento->pai->esq = NULL;
      else
          elemento->pai->dir = NULL;
    else
      elemento->cor = PRETO;

}
