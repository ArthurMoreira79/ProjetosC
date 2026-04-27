#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct lista {
    Lanche* dados[MAX_CAPACIDADE];
    int qtd;
};

Lista* criar_lista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    if (l != NULL) {
        l->qtd = 0;
    }
    return l;
}

void liberar_lista(Lista* l) {
    if (l == NULL) return;
    
    for (int i = 0; i < l->qtd; i++) {
        liberar_lanche(l->dados[i]);
    }
    free(l);
}

int cheia(Lista* l) {
    if (l == NULL) return 1;
    return (l->qtd == MAX_CAPACIDADE);
}

int vazia(Lista* l) {
    if (l == NULL) return 1;
    return (l->qtd == 0);
}

int capacidade(Lista* l) {
    return MAX_CAPACIDADE;
}

int inserir(Lista* l, Lanche* item) {
    if (l == NULL || cheia(l) || item == NULL) {
        return 0;
    }
    
    l->dados[l->qtd] = item;
    l->qtd++;
    return 1;
}

Lanche* buscar(Lista* l, int codigo) {
    if (l == NULL || vazia(l)) {
        return NULL;
    }
    
    for (int i = 0; i < l->qtd; i++) {
        if (get_codigo(l->dados[i]) == codigo) {
            return l->dados[i];
        }
    }
    return NULL;
}

int remover(Lista* l, int codigo) {
    if (l == NULL || vazia(l)) {
        return 0;
    }
    
    int i, j;
    
    for (i = 0; i < l->qtd; i++) {
        if (get_codigo(l->dados[i]) == codigo) {
            break;
        }
    }
    
    if (i == l->qtd) {
        return 0;
    }
    
    liberar_lanche(l->dados[i]);
    
    for (j = i; j < l->qtd - 1; j++) {
        l->dados[j] = l->dados[j+1];
    }
    
    l->qtd--;
    return 1;
}

void listar(Lista* l) {
    if (l == NULL || vazia(l)) {
        printf("A lista de lanches esta vazia.\n");
        return;
    }
    
    printf("\n==== LISTA DE LANCHES (Total: %d/%d) ====\n", l->qtd, MAX_CAPACIDADE);
    for (int i = 0; i < l->qtd; i++) {
        printf("[%d] Cod: %d | Nome: %s | Preco: R$ %.2f | Categoria: %s\n", 
               i, 
               get_codigo(l->dados[i]), 
               get_nome(l->dados[i]), 
               get_preco(l->dados[i]),
               get_categoria(l->dados[i]));
    }
    printf("======================================\n");
}