#ifndef LISTA_H
#define LISTA_H

#include "lanche.h"

#define MAX_CAPACIDADE 20

typedef struct lista Lista;

Lista* criar_lista();

void liberar_lista(Lista* l);

int cheia(Lista* l);

int vazia(Lista* l);

int capacidade(Lista* l);

int inserir(Lista* l, Lanche* item);

Lanche* buscar(Lista* l, int codigo);

int remover(Lista* l, int codigo);

void listar(Lista* l);

#endif