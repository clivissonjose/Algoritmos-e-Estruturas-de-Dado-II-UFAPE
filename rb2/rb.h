#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef int tipo_dado;

typedef struct no {
	tipo_dado dado;
	enum cor cor;
	struct no *esq, *dir, *pai;
} no;

typedef no *arvore;

void inicializar(arvore *raiz);
void adicionar(tipo_dado dado, arvore *raiz);
void ajustar(arvore *raiz, arvore elemento);
void remover(tipo_dado dado, arvore *raiz);
void reajustar(arvore *raiz, arvore elemento);
void retira_duplo_preto(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);

enum cor cor(arvore elemento);
int maior_elemento(arvore raiz);
int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
int eh_filho_direito(arvore elemento);
arvore tio(arvore elemento);
arvore irmao(arvore elemento);

void pre_order(arvore raiz);
void in_order(arvore raiz);
void pos_order(arvore raiz);
void imprimir_elemento(arvore raiz);

#endif
