#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

typedef struct Aresta{
    int v_destino;
    int peso;
    struct Aresta* prox;
} Aresta;

typedef struct{
    int num_vertices;
    int num_arestas;
    bool eh_direcionado;
    Aresta** lista_adj;
} Grafo;

Grafo* criar_grafo(int num_vertices, bool eh_direcionado);
bool inserir_aresta(Grafo* gr, int origem, int destino, int peso);
bool remover_aresta(Grafo* gr, int origem, int destino);
void imprimir_grafo(Grafo* gr);
void destruir_grafo(Grafo* gr);
long long calcular_soma_pesos(Grafo* gr);
void exibir_amostra_matriz(Grafo* gr, int tamanho);

#endif