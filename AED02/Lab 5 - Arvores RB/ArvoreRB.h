#ifndef ARVORE_RB_H
#define ARVORE_RB_H

//Arvore Red-Black .h

typedef struct NO_RB* ArvRB;

//Contadores e tempo de recolorações/rotações - acumulados globalmente, zerados por reset_contadores_RB() antes de cada experimento

extern long long cnt_rot_esq_RB; //rotações simples à esquerda
extern long long cnt_rot_dir_RB; //rotações simples à direita
extern long long cnt_recolor_RB; //recolorações (pai + tio + avô)
extern double     tempo_fixup_RB; //tempo total gasto no fixup (s)

void reset_contadores_RB(void);  //zera tudo antes de cada rodada 

//API pública

ArvRB* cria_ArvRB(void);
void   libera_ArvRB(ArvRB *raiz);
 
int    insere_ArvRB(ArvRB *raiz, int valor);
int    consulta_ArvRB(ArvRB *raiz, int valor);
int    altura_ArvRB(ArvRB *raiz);
int    totalNO_ArvRB(ArvRB *raiz);
int    estaVazia_ArvRB(ArvRB *raiz);
 
void   emOrdem_ArvRB(ArvRB *raiz);
void   preOrdem_ArvRB(ArvRB *raiz);
void   posOrdem_ArvRB(ArvRB *raiz);
 
#endif