#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreAVL.h"

//Variaveis globais de instrumentação
//- Contadores incrementados dentro de cada rotacao
//- Tempo medio dentro de cada rotacao (independente da contagem)
long long cnt_LL        = 0;
long long cnt_RR        = 0;
long long cnt_LR        = 0;
long long cnt_RL        = 0;
double    tempo_rotacoes = 0.0;
 
void reset_contadores_AVL() {
    cnt_LL = cnt_RR = cnt_LR = cnt_RL = 0;
    tempo_rotacoes = 0.0;
}

//Estrutura do NO
struct NO{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

//Funções auxiliares
static int alt_NO(struct NO *no) {
    if (no == NULL) return -1;
    return no->alt;
}
 
static int maior(int x, int y) {
    return (x > y) ? x : y;
}
 
static int fatorBalanceamento_NO(struct NO *no) {
    return alt_NO(no->esq) - alt_NO(no->dir);
}
 
static struct NO* procuraMenor(struct NO *atual) {
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}
 
// Leitura de tempo compativel com Windows e Linux
static double agora() {
    return (double)clock() / CLOCKS_PER_SEC;
}

//Rotações - tempo e contagem medidos aqui dentro. Primeiro mede-se o tempo de rotacao em si, depois incrementa-se o contador separadamente.
static void RotacaoLL(ArvAVL *A) {
    double t0 = agora();          /* inicia cronometro da rotacao */
 
    struct NO *B = (*A)->esq;
    (*A)->esq    = B->dir;
    B->dir       = *A;
    (*A)->alt    = maior(alt_NO((*A)->esq), alt_NO((*A)->dir)) + 1;
    B->alt       = maior(alt_NO(B->esq), (*A)->alt) + 1;
    *A = B;
 
    tempo_rotacoes += agora() - t0; // acumula tempo da rotacao 
    cnt_LL++;                       // incrementa contador separadamente
}
 
static void RotacaoRR(ArvAVL *A) {
    double t0 = agora();
 
    struct NO *B = (*A)->dir;
    (*A)->dir    = B->esq;
    B->esq       = *A;
    (*A)->alt    = maior(alt_NO((*A)->esq), alt_NO((*A)->dir)) + 1;
    B->alt       = maior(alt_NO(B->dir), (*A)->alt) + 1;
    *A = B;
 
    tempo_rotacoes += agora() - t0;
    cnt_RR++;
}
 
static void RotacaoLR(ArvAVL *A) {
    double t0 = agora();

    // LR = RR no filho esquerdo + LL no pai. Medimos o tempo da rotacao dupla como um todo aqui, mas chamamos as simples sem re-medir (evita dupla contagem). Por isso usamos versoes inline das rotacoes simples abaixo.
 
    //RR no filho esquerdo (inline)
    struct NO *filho = (*A)->esq;
    struct NO *neto  = filho->dir;
    filho->dir       = neto->esq;
    neto->esq        = filho;
    filho->alt       = maior(alt_NO(filho->esq), alt_NO(filho->dir)) + 1;
    neto->alt        = maior(alt_NO(neto->dir),  filho->alt) + 1;
    (*A)->esq        = neto;
 
    //LL no pai (inline)
    struct NO *B = (*A)->esq;
    (*A)->esq    = B->dir;
    B->dir       = *A;
    (*A)->alt    = maior(alt_NO((*A)->esq), alt_NO((*A)->dir)) + 1;
    B->alt       = maior(alt_NO(B->esq), (*A)->alt) + 1;
    *A = B;
 
    tempo_rotacoes += agora() - t0;
    cnt_LR++;
}
 
static void RotacaoRL(ArvAVL *raiz) {
    double t0 = agora();
 
    //RL = LL no filho direito + RR no pai
 
    //LL no filho direito (inline)
    struct NO *filho = (*raiz)->dir;
    struct NO *neto  = filho->esq;
    filho->esq       = neto->dir;
    neto->dir        = filho;
    filho->alt       = maior(alt_NO(filho->esq), alt_NO(filho->dir)) + 1;
    neto->alt        = maior(alt_NO(neto->esq),  filho->alt) + 1;
    (*raiz)->dir     = neto;
 
    //RR no pai (inline)
    struct NO *B = (*raiz)->dir;
    (*raiz)->dir = B->esq;
    B->esq       = *raiz;
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    B->alt       = maior(alt_NO(B->dir), (*raiz)->alt) + 1;
    *raiz = B;
 
    tempo_rotacoes += agora() - t0;
    cnt_RL++;
}

//Operações principais
ArvAVL* cria_ArvAVL() {
    ArvAVL *raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if (raiz != NULL) *raiz = NULL;
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
        return 0;
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
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            struct NO *oldNode = *raiz;
            *raiz = ((*raiz)->esq != NULL) ? (*raiz)->esq : (*raiz)->dir;
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

