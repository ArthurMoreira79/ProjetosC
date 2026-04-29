#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

typedef struct NO* ArvAVL;

//Contadores e tempo de rotações (Globais, acessivei pelo Main)
extern long long cnt_LL;        // Rotacoes Simples Direita
extern long long cnt_RR;        // Rotacoes Simples Esquerda
extern long long cnt_LR;        // Rotacoes Duplas Direita
extern long long cnt_RL;        // Rotacoes Duplas Esquerda
extern double tempo_rotacoes;   // Tempo total gasto SÓ nas rotacoes (s)

void reset_contadores_AVL(); //Zera tudo antes de cada experimento

//API Publica
ArvAVL* cria_ArvAVL();
void    libera_ArvAVL(ArvAVL *raiz);
int     insere_ArvAVL(ArvAVL* raiz, int valor);
int     remove_ArvAVL(ArvAVL *raiz, int valor);
int     estaVazia_ArvAVL(ArvAVL *raiz);
int     altura_ArvAVL(ArvAVL *raiz);
int     totalNO_ArvAVL(ArvAVL *raiz);
int     consulta_ArvAVL(ArvAVL *raiz, int valor);
void    preOrdem_ArvAVL(ArvAVL *raiz);
void    emOrdem_ArvAVL(ArvAVL *raiz);
void    posOrdem_ArvAVL(ArvAVL *raiz);

int altura_BST(void *raiz); //Altura da BST(usada no Main para exibir altura final)

#endif