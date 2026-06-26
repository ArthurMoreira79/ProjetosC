#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Grafo.h"

void gerar_arquivo_teste(const char* nome_arquivo, int vertices, int arestas) {
    FILE* arq = fopen(nome_arquivo, "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo de testes.\n");
        return;
    }

    fprintf(arq, "%d %d\n", vertices, arestas);

    for (int i = 0; i < arestas; i++) {
        int origem = rand() % vertices;
        int destino = rand() % vertices;

        while (origem == destino) {
            destino = rand() % vertices;
        }

        int peso = (rand() % 30) + 1;

        fprintf(arq, "%d %d %d\n", origem, destino, peso);
    }

    fclose(arq);
    printf("Arquivo '%s' gerado com sucesso (%d vertices, %d arestas).\n", nome_arquivo, vertices, arestas);
}

Grafo* ler_e_converter_grafo(const char* nome_arquivo) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo '%s' para leitura.\n", nome_arquivo);
        return NULL;
    }

    int v_total, a_total;
    if (fscanf(arq, "%d %d", &v_total, &a_total) != 2) {
        printf("Erro ao ler o cabeçalho do arquivo.\n");
        fclose(arq);
        return NULL;
    }

    printf("\n--- PROCESSANDO ARQUIVO ---\n");
    printf("Metadados do Arquivo -> Vertices: %d | Arestas: %d\n", v_total, a_total);

    Grafo* g = criar_grafo(v_total, false);
    if (g == NULL) {
        fclose(arq);
        return NULL;
    }

    int origem, destino, peso;
    while (fscanf(arq, "%d %d %d", &origem, &destino, &peso) == 3) {
        inserir_aresta(g, origem, destino, peso);
    }

    fclose(arq);
    return g;
}

int main() {
    srand(time(NULL));

    const char* arquivo_grafo = "grafo_dados.txt";

    gerar_arquivo_teste(arquivo_grafo, 1000, 5000);

    Grafo* meu_grafo = ler_e_converter_grafo(arquivo_grafo);

    if (meu_grafo != NULL) {
        printf("\n--- RESULTADO DA CONVERSÃO ---\n");
        printf("Vertices no Grafo construído: %d\n", meu_grafo->num_vertices);
        printf("Arestas no Grafo construído: %d\n", meu_grafo->num_arestas);
        
        long long soma_pesos = calcular_soma_pesos(meu_grafo);
        printf("Soma de todos os pesos das arestas: %lld\n", soma_pesos);

        exibir_amostra_matriz(meu_grafo, 20);

        printf("\n--- CORRESPONDENCIA DA LISTA (Primeiros 3 vertices) ---\n");
        for(int i = 0; i < 3; i++) {
            printf("Vértice %d:", i);
            Aresta* arr = meu_grafo->lista_adj[i];
            while(arr != NULL){
                if(arr->v_destino < 20){
                    printf(" ->[M] %d(peso: %d)", arr->v_destino, arr->peso);
                } else{
                    printf(" -> %d(peso: %d)", arr->v_destino, arr->peso);
                }
                arr = arr->prox;
            }
        }

        destruir_grafo(meu_grafo);
    }

    return 0;
}