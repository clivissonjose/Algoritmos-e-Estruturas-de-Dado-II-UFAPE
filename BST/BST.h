#ifndef BST_H
#define BST_H

typedef struct no {
  int valor;
  struct no *esq, *dir;
} no;

typedef no *arvore;

arvore inserir(arvore raiz, int valor);
void imprimirPreOrdem(arvore raiz);
void imprimirEmOrdem(arvore raiz);
void imprimirPosOrdem(arvore raiz);
arvore remover(arvore raiz, int valor);
arvore maiorElmento(arvore raiz);

#endif