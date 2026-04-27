#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBST.h"

struct NO_BST {
    int info;
    struct NO_BST *esq;
    struct NO_BST *dir;
};

ArvBST* cria_ArvBST() {
    ArvBST *raiz = (ArvBST*) malloc(sizeof(ArvBST));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_ArvBST(ArvBST *raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    libera_ArvBST(&(*raiz)->esq);
    libera_ArvBST(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
}

int insere_ArvBST(ArvBST *raiz, int valor) {
    if (*raiz == NULL) {
        struct NO_BST *novo = (struct NO_BST*) malloc(sizeof(struct NO_BST));
        if (novo == NULL) return 0;
        novo->info = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        *raiz = novo;
        return 1;
    }
    if (valor < (*raiz)->info)
        return insere_ArvBST(&(*raiz)->esq, valor);
    else if (valor > (*raiz)->info)
        return insere_ArvBST(&(*raiz)->dir, valor);
    return 0; // duplicado
}