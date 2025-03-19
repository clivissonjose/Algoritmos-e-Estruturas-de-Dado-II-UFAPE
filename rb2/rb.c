#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

void inicializar(arvore *raiz) {
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
    no_null->pai = NULL;
}

void adicionar(tipo_dado valor, arvore *raiz) {
	arvore posicao = *raiz;
	arvore pai = NULL;

    while(posicao != NULL) {
        pai = posicao;
        if(valor > posicao->dado)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
	}

	arvore novo = (arvore) malloc(sizeof(struct no));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if(eh_raiz(novo))
        *raiz = novo;
	else {
		if(valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}

	ajustar(raiz, novo);
}

void ajustar(arvore *raiz, arvore elemento) {
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
        //caso 1: Cor do tio é vermelha, descer a cor preta do avô
        if(cor(tio(elemento)) == VERMELHO) {
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            elemento = elemento->pai->pai;
            continue;
        }
        //caso 2a: rotação simples direita
        if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
            rotacao_simples_direita(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->dir->cor = VERMELHO;
            continue;
        }
        //caso 2b: rotação simples esquerda
        if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
            rotacao_simples_esquerda(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->esq->cor = VERMELHO;
            continue;
        }
        //caso 3a: rotação dupla direita
        if(eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
            rotacao_simples_esquerda(raiz, elemento->pai);
            rotacao_simples_direita(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            continue;
        }
        //caso 3b: rotação dupla esquerda
        if(eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
            rotacao_simples_direita(raiz, elemento->pai);
            rotacao_simples_esquerda(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->esq->cor = VERMELHO;
            continue;
        }
	}
	(*raiz)->cor = PRETO;
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

void reajustar(arvore *raiz, arvore elemento) {
	//caso 1
	if(eh_raiz(elemento)) {
		elemento->cor = PRETO;
        if(elemento == no_null)
            *raiz = NULL;
		return;
	}
	//caso 2
	if(cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == VERMELHO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO)
    {
        if(eh_filho_esquerdo(elemento))
            rotacao_simples_esquerda(raiz, elemento->pai);
        else
            rotacao_simples_direita(raiz, elemento->pai);

        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
	}
	//caso 3
	if(cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO)
    {
        irmao(elemento)->cor = VERMELHO;
        elemento->pai->cor = DUPLO_PRETO;
        retira_duplo_preto(raiz, elemento);
        reajustar(raiz, elemento->pai);
        return;
	}
	//caso 4
	if(cor(elemento->pai) == VERMELHO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO)
    {
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        return;
	}
	//caso 5a
	if(eh_filho_esquerdo(elemento) &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == VERMELHO){
            
        rotacao_simples_direita(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->dir->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
	}
	//caso 5b
	if(eh_filho_direito(elemento) &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == VERMELHO &&
        cor(irmao(elemento)->esq) == PRETO)
    {
        rotacao_simples_esquerda(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->esq->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
	}
    //caso 6a
	if(eh_filho_esquerdo(elemento) &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == VERMELHO)
    {
        rotacao_simples_esquerda(raiz, elemento->pai);
        elemento->pai->pai->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        tio(elemento)->cor = PRETO;
        retira_duplo_preto(raiz, elemento);
        return;
	}
    //caso 6b
	if(eh_filho_direito(elemento) &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->esq) == VERMELHO)
    {
        rotacao_simples_direita(raiz, elemento->pai);
        elemento->pai->pai->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        tio(elemento)->cor = PRETO;
        retira_duplo_preto(raiz, elemento);
        return;
	}
}

void retira_duplo_preto(arvore *raiz, arvore elemento) {
    if(elemento == no_null) {
        if(eh_filho_esquerdo(elemento))
            elemento->pai->esq = NULL;
        else
            elemento->pai->dir = NULL;
    }
    else
        elemento->cor = PRETO;
}

void rotacao_simples_direita(arvore *raiz, arvore pivo) {
    arvore u, t2;
    u = pivo->esq;
    t2 = u->dir;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    pivo->esq = t2;

    if(t2 != NULL)
        t2->pai = pivo;

    if(eh_raiz(u))
        *raiz = u;
    else {
        if(posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo) {
    arvore u, t2;
    u = pivo->dir;
    t2 = u->esq;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    pivo->dir = t2;

    if(t2 != NULL)
        t2->pai = pivo;

    if(eh_raiz(u))
        *raiz = u;
    else {
        if(posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
}

enum cor cor(arvore elemento) {
	enum cor c;
	if(elemento == NULL)
		return PRETO;
	else
		return elemento->cor;
	return c;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
        return -1;
	if(raiz->dir == NULL)
        return raiz->dado;
	else
        return maior_elemento(raiz->dir);
}

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvore elemento) {
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

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

// void imprimir_elemento(arvore raiz) {
//     switch(raiz->cor) {
//         case PRETO:
//             // texto preto (para tela de fundo claro)
//             // printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
//             // texto azul (para tela de fundo escuro)
// 			printf("\x1b[34m[%d]\x1b[0m", raiz->dado); 
// 			break;
// 		case VERMELHO:
// 			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
// 			break;
// 		case DUPLO_PRETO:
// 			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
// 			break;
//     }
// }

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
