#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grafo.h"

#define MAX_AMOSTRA 20

Grafo* criar_grafo(int num_vertices, bool eh_direcionado){
    if(num_vertices <= 0) return NULL;

    Grafo* gr = (Grafo*) malloc(sizeof(Grafo));
    if(gr == NULL) return NULL;

    gr->num_vertices = num_vertices;
    gr->num_arestas = 0;
    gr->eh_direcionado = eh_direcionado;
    gr->lista_adj = (Aresta**) malloc(num_vertices * sizeof(Aresta*));
    if(gr->lista_adj == NULL){
        free(gr);
        return NULL;
    }

    for(int i = 0; i < num_vertices; i++){
        gr->lista_adj[i] = NULL;
    }

    return gr;
}

static Aresta* criar_no_aresta(int destino, int peso){
    Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
    if(nova != NULL){
        nova->v_destino = destino;
        nova->peso = peso;
        nova->prox = NULL;
    }
    return nova;
}

bool inserir_aresta(Grafo* gr, int origem, int destino, int peso){
    if(gr == NULL) return false;
    if(origem < 0 || origem >= gr->num_vertices) return false;
    if(destino < 0 || destino >= gr->num_vertices) return false;

    Aresta* nova = criar_no_aresta(destino, peso);
    if(nova == NULL) return false;

    nova->prox = gr->lista_adj[origem];
    gr->lista_adj[origem] = nova;
    gr->num_arestas++;

    if(!gr->eh_direcionado){
        Aresta* nova_volta = criar_no_aresta(origem, peso);
        if(nova_volta == NULL) return false;

        nova_volta->prox = gr->lista_adj[destino];
        gr->lista_adj[destino] = nova_volta;
    }
    return true;
}

bool remover_aresta(Grafo* gr, int origem, int destino){
    if(gr == NULL) return false;
    if(origem < 0 || origem >= gr->num_vertices) return false;
    if(destino < 0 || destino >= gr->num_vertices) return false;

    Aresta* atual = gr->lista_adj[origem];
    Aresta* anterior = NULL;

    while(atual != NULL && atual->v_destino != destino){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) return false;

    if(anterior == NULL){
        gr->lista_adj[origem] = atual->prox;
    } else{
        anterior->prox = atual->prox;
    }

    free(atual);
    gr->num_arestas--;

    if(!gr->eh_direcionado){
        atual = gr->lista_adj[destino];
        anterior = NULL;

        while(atual != NULL && atual->v_destino != origem){
            anterior = atual;
            atual = atual->prox;
        }

        if(atual != NULL){
            if(anterior == NULL){
                gr->lista_adj[destino] = atual->prox;
            } else{
                anterior->prox = atual->prox;
            }
            free(atual);
        }
    }
    return true;
}

void imprimir_grafo(Grafo* gr){
    if(gr == NULL) return;

    printf("Grafo (%s, %d vertices, %d arestas):\n",
        gr->eh_direcionado ? "Direcionado" : "Não direcionado",
        gr->num_vertices, gr->num_arestas);

    for(int i = 0; i < gr->num_vertices; i++){
        printf("Vertice %d:", i);
        Aresta* aresta = gr->lista_adj[i];
        while(aresta != NULL){
            printf(" -> %d( peso:%d)", aresta->v_destino, aresta->peso);
            aresta = aresta->prox;
        }
        printf("\n");
    }
}

void destruir_grafo(Grafo* gr){
    if(gr == NULL) return;

    for(int i = 0; i < gr->num_vertices; i++){
        Aresta* atual = gr->lista_adj[i];
        while(atual != NULL){
            Aresta* aux = atual;
            atual = atual->prox;
            free(aux);
        }
    }

    free(gr->lista_adj);
    free(gr);
}

long long calcular_soma_pesos(Grafo* gr) {
    if (gr == NULL) return 0;
    long long soma = 0;

    for (int i = 0; i < gr->num_vertices; i++) {
        Aresta* atual = gr->lista_adj[i];
        while (atual != NULL) {
            soma += atual->peso;
            atual = atual->prox;
        }
    }
    return gr->eh_direcionado ? soma : (soma / 2);
}

void exibir_amostra_matriz(Grafo* gr, int tamanho) {
    if (gr == NULL) return;
    
    if(tamanho > MAX_AMOSTRA) tamanho = MAX_AMOSTRA;
    if(tamanho > gr->num_vertices) tamanho = gr->num_vertices;

    int matriz[MAX_AMOSTRA][MAX_AMOSTRA] = {0};

    for (int i = 0; i < gr->num_vertices && i < tamanho; i++) {
        Aresta* atual = gr->lista_adj[i];
        while (atual != NULL) {
            if (atual->v_destino < tamanho) {
                matriz[i][atual->v_destino] = atual->peso;
            }
            atual = atual->prox;
        }
    }

    printf("\n--- AMOSTRA DA MATRIZ DE ADJACENCIA (%dx%d) ---\n", tamanho, tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
}
