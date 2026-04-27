#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

Lista* lista_criar(void);

void lista_destruir(Lista* l, void (*liberar_dado)(void*));

int lista_inserir_final(Lista* l, void* dado);

int lista_inserir_inicio(Lista* l, void* dado);

void* lista_buscar(Lista* l, void* chave,
                   int (*comparar)(const void*, const void*));

void lista_percorrer(Lista* l, void (*funcao)(void*));

int lista_tamanho(Lista* l);

#endif
