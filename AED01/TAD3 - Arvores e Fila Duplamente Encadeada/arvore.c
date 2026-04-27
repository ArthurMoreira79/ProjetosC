#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

typedef struct nodo_arv {               //estrutura do nodo árvore
    int chave;                          //valor p comparação e ordenação
    void* dado_lista;                   //ponteiro p dado real(na lista)
    struct nodo_arv* esq;               // ponteiros p subarvores esq e dir
    struct nodo_arv* dir;
} NodoArv;

struct arvore {
    NodoArv* raiz;                      //ponteiro p nodo raiz(topo da árvore)
}; 

Arvore* arvore_criar() {
    Arvore* a = (Arvore*)malloc(sizeof(Arvore));    //aloca a estrutura da arvore
    if (a) a->raiz = NULL;                          //inicia a raiz como NULL(árvore vazia)
    return a;
}

NodoArv* inserir_recursivo(NodoArv* nodo, int chave, void* dado) {
    if (nodo == NULL) {
        NodoArv* novo = (NodoArv*)malloc(sizeof(NodoArv));          //caso base: chegou em uma posição vazia
        novo->chave = chave;                                        //o novo nodo é uma folha
        novo->dado_lista = dado;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (chave < nodo->chave)                                        //caso recursivo:desce na árvore
        nodo->esq = inserir_recursivo(nodo->esq, chave, dado);      // desce p esq se menor q a chave, e p direita se maior
    else if (chave > nodo->chave)                                   //se a chave == nodo->chave: n faz nada, p evitar duplicatas
        nodo->dir = inserir_recursivo(nodo->dir, chave, dado);
    
    return nodo;
}

void arvore_inserir(Arvore* a, int chave, void* dado_lista) {       //verifica se a arvore existe, chama a função recursiva passando pela raiz
    if (a) a->raiz = inserir_recursivo(a->raiz, chave, dado_lista);     //atualiza a raiz com o retorno
}

void* buscar_recursivo(NodoArv* nodo, int chave) {                          //CASOS:
    if (nodo == NULL) return NULL;                                          //n encontrados(percorreu a arvor e n achou)(volta NULL)
    if (chave == nodo->chave) return nodo->dado_lista;                       //encontrado(retorna o dado associado(ponteiro p lanche))
    if (chave < nodo->chave) return buscar_recursivo(nodo->esq, chave);     //chave procurada é menor(esquerda)
    return buscar_recursivo(nodo->dir, chave);                              //chave procurada é maior(direita)
}

void* arvore_buscar(Arvore* a, int chave) {                 //verificação: se 'a' n é NULL, ele chama o 'buscar_recursivo' começando na raiz
    return (a) ? buscar_recursivo(a->raiz, chave) : NULL;   //se 'a' for NULL, retorna NUll na hora
}

void em_ordem(NodoArv* nodo, void (*funcao)(void*)) {       //percurso em ordem(in order): esq>raiz>dir
    if (nodo != NULL) {                                     //visita nodos em ordem crescente das chaves
        em_ordem(nodo->esq, funcao);                        //torna a árvore em uma sequência ordenada
        funcao(nodo->dado_lista);
        em_ordem(nodo->dir, funcao);
    }
}

void arvore_percorrer_em_ordem(Arvore* a, void (*funcao)(void*)) {      //wrapper publico p função recursiva privada
    if (a) em_ordem(a->raiz, funcao);                                   //só é valida se a árvore existir. Ela inicia pela raiz
}

void destruir_recursivo(NodoArv* nodo) {            //liberamos primeiro as subarvore esq e dir, depoi o nodo atual(filhos antes do pai)
    if (nodo != NULL) {                             //usamos isso p evitar vazamento de memoria
        destruir_recursivo(nodo->esq);
        destruir_recursivo(nodo->dir);
        free(nodo);
    }
}

void arvore_destruir(Arvore* a) {               //liberamos primeiro todos os nodos, depois a estrutura da árvore
    if (a) {
        destruir_recursivo(a->raiz);
        free(a);
    }
}