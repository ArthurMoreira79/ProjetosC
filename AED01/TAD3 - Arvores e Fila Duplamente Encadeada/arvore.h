#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore* arvore_criar();

void arvore_inserir(Arvore* a, int chave, void* dado_lista);

void* arvore_buscar(Arvore* a, int chave);

void arvore_percorrer_em_ordem(Arvore* a, void (*funcao)(void*));

void arvore_destruir(Arvore* a);

#endif