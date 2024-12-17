#ifndef avl_h
#define avl_h

typedef struct no_avl{
  int valor;
  int fb;
  struct no_avl *esq, *dir;
} no_avl;

typedef no_avl *arvore;

arvore inserir(arvore raiz, int valor, int *cresceu);
arvore remover(arvore raiz, int valor, int *diminuiu);
int altura(arvore raiz);
arvore rotacionar(arvore raiz);
arvore rotacaoSimplesDireita(arvore raiz);
arvore rotacaoDuplaDireita(arvore raiz);
arvore rotacaoSimplesEsquerda(arvore raiz);
arvore rotacaoDuplaEsquerda(arvore raiz);
void imprimirPreOrdem(arvore a);
void imprimirEmOrdem(arvore a);

#endif