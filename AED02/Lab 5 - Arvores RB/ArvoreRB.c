#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreRB.h"

//Arvore Red Black .c

#define VERMELHO 0
#define PRETO    1

//Estrutura do nó
struct NO_RB{
    int info;
    int cor;
    struct NO_RB *esq;
    struct NO_RB *dir;
    struct NO_RB *pai;
};

//Sentinela NIL global (nó preto fixo - evita NULL checks por toda parte e espelha a definição clássica da árvore RB do Cormen).
static struct NO_RB NIL_NODE = {0, PRETO, NULL, NULL, NULL};
static struct NO_RB *NIL = &NIL_NODE;

//Contadores e tempo - variáveis globais exportadas pelo header

long long cnt_rot_esq_RB  = 0;
long long cnt_rot_dir_RB  = 0;
long long cnt_recolor_RB  = 0;
double    tempo_fixup_RB  = 0.0;
 
void reset_contadores_RB(void) {
    cnt_rot_esq_RB = 0;
    cnt_rot_dir_RB = 0;
    cnt_recolor_RB = 0;
    tempo_fixup_RB = 0.0;
}

//Auxiliar de tempo

static double agora_RB(void) {
    return (double)clock() / CLOCKS_PER_SEC;
}

//Rotações: O ponteiro para a raiz da árvore inteira é passado para que a raiz possa ser trocada caso a rotação aconteça no topo.

//Rotação à esquerda em torno do nó x

static void rotacao_esquerda(struct NO_RB **raiz, struct NO_RB *x) {
    struct NO_RB *y = x->dir;   //y = filho direito de x
 
    x->dir = y->esq;            //subárvore esquerda de y passa para x
    if (y->esq != NIL)
        y->esq->pai = x;
 
    y->pai = x->pai;            //y sobe para o lugar de x
 
    if (x->pai == NIL) {
        *raiz = y;              //x era a raiz
    } else if (x == x->pai->esq) {
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }
 
    y->esq = x;                 //x desce para filho esquerdo de y
    x->pai = y;
 
    cnt_rot_esq_RB++;
}

//Rotação à direita em torno do nó x

static void rotacao_direita(struct NO_RB **raiz, struct NO_RB *x) {
    struct NO_RB *y = x->esq;   //y = filho esquerdo de x
 
    x->esq = y->dir;
    if (y->dir != NIL)
        y->dir->pai = x;
 
    y->pai = x->pai;
 
    if (x->pai == NIL) {
        *raiz = y;
    } else if (x == x->pai->dir) {
        x->pai->dir = y;
    } else {
        x->pai->esq = y;
    }
 
    y->dir = x;
    x->pai = y;
 
    cnt_rot_dir_RB++;
}

//Fixup pós-inserção (corrige violações das propriedades RB)

static void insere_fixup(struct NO_RB **raiz, struct NO_RB *z) {
    double t0 = agora_RB();
 
    while (z->pai->cor == VERMELHO) {
 
        if (z->pai == z->pai->pai->esq) {
            //Pai é filho ESQUERDO do avô
            struct NO_RB *tio = z->pai->pai->dir;   //tio = filho direito do avô
 
            if (tio->cor == VERMELHO) {
                //Caso 1: tio vermelho -> apenas recoloração
                z->pai->cor       = PRETO;
                tio->cor          = PRETO;
                z->pai->pai->cor  = VERMELHO;
                z = z->pai->pai;    //sobe o problema para o avô
                cnt_recolor_RB++;
 
            } else {
                //Tio preto -> uma ou duas rotações necessárias
 
                if (z == z->pai->dir) {
                    //Caso 2: z é filho DIREITO -> rotação esquerda no pai
                    z = z->pai;
                    rotacao_esquerda(raiz, z);
                }
 
                //Caso 3: z é filho ESQUERDO -> rotação direita no avô
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_direita(raiz, z->pai->pai);
            }
 
        } else {
            //Pai é filho DIREITO do avô (espelho dos casos acima)
            struct NO_RB *tio = z->pai->pai->esq;
 
            if (tio->cor == VERMELHO) {
                //Caso 1 espelhado
                z->pai->cor       = PRETO;
                tio->cor          = PRETO;
                z->pai->pai->cor  = VERMELHO;
                z = z->pai->pai;
                cnt_recolor_RB++;
 
            } else {
                if (z == z->pai->esq) {
                    //Caso 2 espelhado
                    z = z->pai;
                    rotacao_direita(raiz, z);
                }
 
                //Caso 3 espelhado
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_esquerda(raiz, z->pai->pai);
            }
        }
    }
 
    (*raiz)->cor = PRETO;   //Propriedade 2: raiz sempre preta
 
    tempo_fixup_RB += agora_RB() - t0;
}

//Operações públicas

//Aloca e retorna um ponteiro para a raiz (inicialmente NIL)
ArvRB* cria_ArvRB(void) {
    ArvRB *raiz = (ArvRB*) malloc(sizeof(ArvRB));
    if (raiz != NULL) *raiz = NIL;
    return raiz;
}
 
//Libera todos os nós internos recursivamente
static void libera_rec(struct NO_RB *no) {
    if (no == NIL) return;
    libera_rec(no->esq);
    libera_rec(no->dir);
    free(no);
}
 
void libera_ArvRB(ArvRB *raiz) {
    if (raiz == NULL) return;
    libera_rec(*raiz);
    *raiz = NIL;
}
 
//Inserção: retorna 1 se inserido, 0 se duplicado ou sem memória
int insere_ArvRB(ArvRB *raiz, int valor) {
    //BST insert padrão
    struct NO_RB *y = NIL;
    struct NO_RB *x = *raiz;
 
    while (x != NIL) {
        y = x;
        if      (valor < x->info) x = x->esq;
        else if (valor > x->info) x = x->dir;
        else return 0;   //valor duplicado
    }
 
    struct NO_RB *z = (struct NO_RB*) malloc(sizeof(struct NO_RB));
    if (z == NULL) return 0;
 
    z->info = valor;
    z->cor  = VERMELHO;  //todo nó novo é vermelho (não altera bh)
    z->esq  = NIL;
    z->dir  = NIL;
    z->pai  = y;
 
    if (y == NIL) {
        *raiz = z;       //árvore estava vazia
    } else if (valor < y->info) {
        y->esq = z;
    } else {
        y->dir = z;
    }
 
    //Corrige violações das propriedades RB
    insere_fixup(raiz, z);
    return 1;
}
 
//Busca iterativa: retorna 1 se encontrado, 0 caso contrário
int consulta_ArvRB(ArvRB *raiz, int valor) {
    struct NO_RB *x = *raiz;
    while (x != NIL) {
        if      (valor == x->info) return 1;
        else if (valor <  x->info) x = x->esq;
        else                       x = x->dir;
    }
    return 0;
}
 
//Altura da árvore (calculada recursivamente, nó NIL = -1)
static int altura_rec(struct NO_RB *no) {
    if (no == NIL) return -1;
    int he = altura_rec(no->esq);
    int hd = altura_rec(no->dir);
    return 1 + (he > hd ? he : hd);
}
 
int altura_ArvRB(ArvRB *raiz) {
    if (raiz == NULL) return -1;
    return altura_rec(*raiz);
}
 
//Contagem de nós internos
static int conta_rec(struct NO_RB *no) {
    if (no == NIL) return 0;
    return 1 + conta_rec(no->esq) + conta_rec(no->dir);
}
 
int totalNO_ArvRB(ArvRB *raiz) {
    if (raiz == NULL) return 0;
    return conta_rec(*raiz);
}
 
int estaVazia_ArvRB(ArvRB *raiz) {
    return (raiz == NULL || *raiz == NIL);
}
 
//Percursos
void emOrdem_ArvRB(ArvRB *raiz) {
    if (raiz == NULL || *raiz == NIL) return;
    //percurso in-order iterativo simples via recursão
    //(profundidade máxima O(log n), seguro para n razoável)
    struct NO_RB *no = *raiz;
    if (no->esq != NIL) { ArvRB tmp = no->esq; emOrdem_ArvRB(&tmp); }
    printf("%d ", no->info);
    if (no->dir != NIL) { ArvRB tmp = no->dir; emOrdem_ArvRB(&tmp); }
}
 
void preOrdem_ArvRB(ArvRB *raiz) {
    if (raiz == NULL || *raiz == NIL) return;
    struct NO_RB *no = *raiz;
    printf("%d ", no->info);
    if (no->esq != NIL) { ArvRB tmp = no->esq; preOrdem_ArvRB(&tmp); }
    if (no->dir != NIL) { ArvRB tmp = no->dir; preOrdem_ArvRB(&tmp); }
}
 
void posOrdem_ArvRB(ArvRB *raiz) {
    if (raiz == NULL || *raiz == NIL) return;
    struct NO_RB *no = *raiz;
    if (no->esq != NIL) { ArvRB tmp = no->esq; posOrdem_ArvRB(&tmp); }
    if (no->dir != NIL) { ArvRB tmp = no->dir; posOrdem_ArvRB(&tmp); }
    printf("%d ", no->info);
}