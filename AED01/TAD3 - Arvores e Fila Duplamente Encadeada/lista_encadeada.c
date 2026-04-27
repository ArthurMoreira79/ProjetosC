#include <stdlib.h>
#include "lista.h"

typedef struct nodo {           //estrutura do nodo
    void* dado;                 //ponteiro generico p dados
    struct nodo* proximo;       //ligação p frente
    struct nodo* anterior;      //ligação p trás
} Nodo;

struct lista {              //estrutura da lista
    Nodo* inicio;           //primeiro e ultimo elemento, controle de tamanho
    Nodo* fim;              //ela percorre pelos dois sentidos.
    int tamanho;
};

Lista* lista_criar(void) {                          //criar lista
    Lista* l = (Lista*)malloc(sizeof(Lista));       //aloca a estrutura da lista
    if (l) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}

int lista_inserir_final(Lista* l, void* dado) {     
    if (l == NULL) return 0;

    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));   //aloca o novo nodo
    if (!novo) return 0;
    
    novo->dado = dado;
    novo->proximo = NULL;
    novo->anterior = l->fim;        //liga ao ultimo nodo

    if (l->fim != NULL) {
        l->fim->proximo = novo;     //atualiza ligação do antigo fim
    } else {
        l->inicio = novo;           //lista estava vazia
    }
    
    l->fim = novo;                  //atualiza o fim
    l->tamanho++;
    return 1;
}

int lista_inserir_inicio(Lista* l, void* dado) {
    if (l == NULL) return 0;

    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));       //aloca o novo nodo
    if (!novo) return 0;

    novo->dado = dado;
    novo->proximo = l->inicio;
    novo->anterior = NULL;                          //liga ao primeiro nodo

    if (l->inicio != NULL) {
        l->inicio->anterior = novo;             //atualiza ligação do antigo inicio
    } else {
        l->fim = novo;                         
    }

    l->inicio = novo;                           //atualiza o inicio
    l->tamanho++;
    return 1;
}

void* lista_buscar(Lista* l, void* chave, int (*comparar)(const void*, const void*)) {
    if (l == NULL || comparar == NULL) return NULL; 

    Nodo* atual = l->inicio;
    while (atual != NULL) {
        if (comparar(atual->dado, chave) == 0) {
            return atual->dado;
        }
        atual = atual->proximo;     //avança para o proximo
    }
    return NULL;                    //não encontrou
}

void lista_percorrer(Lista* l, void (*funcao)(void*)) {
    if (l == NULL || funcao == NULL) return; 

    Nodo* atual = l->inicio;
    while (atual != NULL) {                     //percorre a lista
        funcao(atual->dado);
        atual = atual->proximo;
    }
}

int lista_tamanho(Lista* l) {                   //retorna o tamanho da lista
    return l ? l->tamanho : 0;
}

void lista_destruir(Lista* l, void (*liberar_dado)(void*)) {
    if (l == NULL) return;
    
    Nodo* atual = l->inicio;            
    while (atual != NULL) {
        Nodo* prox = atual->proximo;        //guarda proximo antes de liberar
        if (liberar_dado) {
            liberar_dado(atual->dado);      //libera dado do usuario
        }
        free(atual);                        //libera nodo
        atual = prox;
    }
    free(l);                                //libera estrutura da lista
}   