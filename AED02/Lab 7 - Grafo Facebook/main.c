#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grafo.h"

// LEITURA DO GRAFO DA BASE "SOCIAL CIRCLES: FACEBOOK" (facebook_combined.txt)

Grafo* ler_grafo_facebook(const char* nome_arquivo){
    FILE* arq = fopen(nome_arquivo, "r");
    if(arq == NULL){
        printf("Erro: nao foi possivel abrir o arquivo '%s' .\n", nome_arquivo);
        return NULL;
    }

    int origem, destino;
    int max_vertice = -1;
    int total_arestas = 0;

    while(fscanf(arq, "%d %d", &origem, &destino) == 2){
        if(origem > max_vertice) max_vertice = origem;
        if(destino > max_vertice) max_vertice = destino;
        total_arestas++;
    }

    if(max_vertice < 0){
        printf("Arquivo vazio ou em formato invalido.\n");
        fclose(arq);
        return NULL;
    }

    int num_vertices = max_vertice + 1;

    printf("--- LEITURA DO ARQUIVO '%s' ---\n", nome_arquivo);
    printf("Vertices detectados (usuarios): %d\n", num_vertices);
    printf("Arestas detectadas (amizades):  %d\n", total_arestas);

    Grafo* g = criar_grafo(num_vertices, false);
    if(g == NULL){
        fclose(arq);
        return NULL;
    }

    rewind(arq);
    while(fscanf(arq, "%d %d", &origem, &destino) == 2){
        inserir_aresta(g, origem, destino, 1);
    }

    fclose(arq);
    return g;
}

void consultar_dois_usuarios(Grafo* gr, int v1, int v2){
    if(v1 < 0 || v1 >= gr->num_vertices || v2 < 0 || v2 >= gr->num_vertices){
        printf("Vertice invalido. O grafo nao possui usuarios de 0 a %d.\n", gr->num_vertices - 1);
        return;
    }

    printf("\n--- Numero de amigos ---\n");
    printf("Usuario %d possui %d amigo(s).\n", v1, obter_grau(gr, v1));
    printf("Usuario %d possui %d amigo(s).\n", v2, obter_grau(gr, v2));
 
    printf("\n--- Amigos em comum ---\n");
    exibir_amigos_comuns(gr, v1, v2);
 
    printf("\n--- Caminho de amigos entre %d e %d (busca em largura) ---\n", v1, v2);
    int tam_caminho;
    int* caminho = busca_largura_caminho(gr, v1, v2, &tam_caminho);
    exibir_caminho(caminho, tam_caminho);
    if (caminho != NULL) free(caminho);
}

void menu(Grafo* gr){
    int opcao, v1, v2;
 
    do {
        printf("\n================= MENU =================\n");
        printf("1 - Consultar dois usuarios (amigos, amigos em comum e caminho)\n");
        printf("2 - Consultar apenas o numero de amigos de um usuario\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
 
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            break;
        }
 
        switch (opcao) {
            case 1:
                printf("Digite o usuario de origem: ");
                if (scanf("%d", &v1) != 1) break;
                printf("Digite o usuario de destino: ");
                if (scanf("%d", &v2) != 1) break;
                consultar_dois_usuarios(gr, v1, v2);
                break;
 
            case 2:
                printf("Digite o usuario: ");
                if (scanf("%d", &v1) != 1) break;
                if (v1 < 0 || v1 >= gr->num_vertices) {
                    printf("Vertice invalido.\n");
                } else {
                    printf("Usuario %d possui %d amigo(s).\n", v1, obter_grau(gr, v1));
                }
                break;
 
            case 0:
                printf("Encerrando...\n");
                break;
 
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main(){
    const char* arquivo = "facebook_combined.txt";
 
    Grafo* gr = ler_grafo_facebook(arquivo);
    if (gr == NULL) {
        printf("\nNao foi possivel carregar o grafo.\n");
        printf("Verifique se o arquivo '%s' esta na mesma pasta do executavel.\n", arquivo);
        return 1;
    }
 
    printf("\nGrafo carregado com sucesso!\n");
    printf("Total de vertices (usuarios): %d\n", gr->num_vertices);
    printf("Total de arestas (amizades):  %d\n", gr->num_arestas);
 
    menu(gr);
 
    destruir_grafo(gr);
    return 0;
}