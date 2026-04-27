#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

//Estrutura do nó
struct NO{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

//Funções auxiliares

//Retorna a altura de um nó (NULL = -1)
static int alt_NO(struct NO *no){
    if(no == NULL) return -1;
    return no -> alt;
}

//Retorna o maior entre dois valores
static int maior(int x, int y){
    return(x > y) ? x : y;
}

//Retorna o fator de balanceamento (esq - dir)
static int fatorBalanceamento_NO(struct NO *no){
    return alt_NO(no -> esq) - alt_NO(no -> dir);
}

//Encontra o menor nó da subárvore (mais a esquerda)
static struct NO* procuraMenor(struct NO *atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual -> esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2 -> esq;
    }
    return no1;
}

//ROTAÇÕES

//Rotação Simples Direita (LL)
static void RotacaoLL(ArvAVL *A){
    struct NO *B = (*A) -> esq;
    (*A) -> esq = B -> dir;
    B -> dir = *A;
    (*A) -> alt = maior(alt_NO((*A) -> esq), alt_NO((*A) -> dir)) + 1;
    B -> alt = maior(alt_NO(B -> esq), (*A) -> alt) + 1;
    *A = B;
}

//Rotação Simples Esquerda (RR)
static void RotacaoRR(ArvAVL *A) {
    struct NO *B = (*A)->dir;
    (*A)->dir    = B->esq;
    B->esq       = *A;
    (*A)->alt    = maior(alt_NO((*A)->esq), alt_NO((*A)->dir)) + 1;
    B->alt       = maior(alt_NO(B->dir), (*A)->alt) + 1;
    *A = B;
}

//Rotação Dupla Direita (LR)
static void RotacaoLR(ArvAVL *A){
    RotacaoRR(&(*A) -> esq);
    RotacaoLL(A);
}

//Rotação Dupla Esquerda (RL)
static void RotacaoRL(ArvAVL *raiz){
    RotacaoLL(&(*raiz) -> dir);
    RotacaoRR(raiz);
}

//Funções Principais

ArvAVL* cria_ArvAVL() {
    ArvAVL *raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_ArvAVL(ArvAVL *raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    libera_ArvAVL(&(*raiz)->esq);
    libera_ArvAVL(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
}

int estaVazia_ArvAVL(ArvAVL *raiz) {
    return (*raiz == NULL);
}

int altura_ArvAVL(ArvAVL *raiz) {
    return alt_NO(*raiz);
}

int totalNO_ArvAVL(ArvAVL *raiz) {
    if (*raiz == NULL) return 0;
    return 1 + totalNO_ArvAVL(&(*raiz)->esq) + totalNO_ArvAVL(&(*raiz)->dir);
}

int consulta_ArvAVL(ArvAVL *raiz, int valor) {
    if (*raiz == NULL) return 0;
    if (valor == (*raiz)->info) return 1;
    if (valor < (*raiz)->info) return consulta_ArvAVL(&(*raiz)->esq, valor);
    return consulta_ArvAVL(&(*raiz)->dir, valor);
}

int insere_ArvAVL(ArvAVL *raiz, int valor) {
    int res;
 
    if (*raiz == NULL) {
        struct NO *novo = (struct NO*) malloc(sizeof(struct NO));
        if (novo == NULL) return 0;
        novo->info = valor;
        novo->alt  = 0;
        novo->esq  = NULL;
        novo->dir  = NULL;
        *raiz = novo;
        return 1;
    }
 
    struct NO *atual = *raiz;
 
    if (valor < atual->info) {
        if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (valor < (*raiz)->esq->info)
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    } else if (valor > atual->info) {
        if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1) {
            if (fatorBalanceamento_NO(atual) <= -2) {
                if ((*raiz)->dir->info < valor)
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    } else {
        return 0; // valor duplicado
    }
 
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    return res;
}

int remove_ArvAVL(ArvAVL *raiz, int valor) {
    if (*raiz == NULL) return 0;
 
    int res;
 
    if (valor < (*raiz)->info) {
        if ((res = remove_ArvAVL(&(*raiz)->esq, valor)) == 1) {
            if (fatorBalanceamento_NO(*raiz) <= -2) {
                if (alt_NO((*raiz)->dir->esq) <= alt_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    } else if ((*raiz)->info < valor) {
        if ((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1) {
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (alt_NO((*raiz)->esq->dir) <= alt_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    } else {
        // Nó encontrado
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            struct NO *oldNode = *raiz;
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode);
        } else {
            struct NO *temp = procuraMenor((*raiz)->dir);
            (*raiz)->info   = temp->info;
            remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (alt_NO((*raiz)->esq->dir) <= alt_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        if (*raiz != NULL)
            (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
        return 1;
    }
 
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    return res;
}

void preOrdem_ArvAVL(ArvAVL *raiz) {
    if (*raiz == NULL) return;
    printf("%d ", (*raiz)->info);
    preOrdem_ArvAVL(&(*raiz)->esq);
    preOrdem_ArvAVL(&(*raiz)->dir);
}
 
void emOrdem_ArvAVL(ArvAVL *raiz) {
    if (*raiz == NULL) return;
    emOrdem_ArvAVL(&(*raiz)->esq);
    printf("%d ", (*raiz)->info);
    emOrdem_ArvAVL(&(*raiz)->dir);
}
 
void posOrdem_ArvAVL(ArvAVL *raiz) {
    if (*raiz == NULL) return;
    posOrdem_ArvAVL(&(*raiz)->esq);
    posOrdem_ArvAVL(&(*raiz)->dir);
    printf("%d ", (*raiz)->info);
}