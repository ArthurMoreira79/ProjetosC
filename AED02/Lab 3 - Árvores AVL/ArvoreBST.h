#ifndef ARVORE_BST_H
#define ARVORE_BST_H

typedef struct NO_BST* ArvBST;

ArvBST* cria_ArvBST();
void libera_ArvBST(ArvBST *raiz);
int insere_ArvBST(ArvBST *raiz, int valor);

#endif