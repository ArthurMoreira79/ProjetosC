#include "fila.h"
#include <stdlib.h>

typedef struct no {
    dado_t item;
    struct no* prox;
} no_t;

struct fila_t {
    no_t* inicio;
    no_t* fim;
};

fila_t* fila_criar() {
    fila_t* f = malloc(sizeof(fila_t));
    if (!f) return NULL;
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int fila_enfileirar(fila_t* f, dado_t item) {
    no_t* novo = malloc(sizeof(no_t));
    if (!novo) return 0;

    novo->item = item;
    novo->prox = NULL;

    if (f->fim)
        f->fim->prox = novo;
    else
        f->inicio = novo;

    f->fim = novo;
    return 1;
}

dado_t fila_desenfileirar(fila_t* f) {
    if (!f->inicio) return NULL;

    no_t* temp = f->inicio;
    dado_t item = temp->item;

    f->inicio = temp->prox;

    if (!f->inicio)
        f->fim = NULL;

    free(temp);
    return item;
}

int fila_vazia(fila_t* f) {
    return (f->inicio == NULL);
}

void fila_destruir(fila_t* f) {
    while (!fila_vazia(f)) {
        fila_desenfileirar(f); // descarta ponteiros
    }
    free(f);
}