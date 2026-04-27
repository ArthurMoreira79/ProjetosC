#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lanche.h"
#include "lista.h"
#include "arvore.h"

int comparar_lanche_exp(const void* lanche_v, const void* codigo_v) {
    Lanche* l = (Lanche*)lanche_v;
    int cod_procurado = *(int*)codigo_v;
    return (get_codigo(l) == cod_procurado) ? 0 : 1;
}

int main() {
    FILE *file = fopen("dados.csv", "r");
    if (!file) {
        printf("Erro: Arquivo dados.csv nao encontrado na pasta do projeto!\n");
        return 1;
    }

    Lista* minha_lista = lista_criar();
    Arvore* minha_arvore = arvore_criar();

    int cod;
    char nome[50], categoria[30];
    float preco;

    printf("Carregando dados...\n");

    while (fscanf(file, "%d,%49[^,],%f,%29[^,],%*[^,],%*[^\n]\n", &cod, nome, &preco, categoria) == 4) {
        Lanche* novo = criar_lanche(cod, nome, preco, categoria);
        lista_inserir_final(minha_lista, novo);
        arvore_inserir(minha_arvore, cod, novo);
    }
    fclose(file);

    int codigo_busca;
    printf("Digite o codigo para buscar no experimento: ");
    scanf("%d", &codigo_busca);

    clock_t start_lista = clock();
    Lanche* res_lista = (Lanche*)lista_buscar(minha_lista, &codigo_busca, comparar_lanche_exp);
    clock_t end_lista = clock();
    double tempo_lista = ((double)(end_lista - start_lista)) / CLOCKS_PER_SEC;

    clock_t start_arv = clock();
    Lanche* res_arv = (Lanche*)arvore_buscar(minha_arvore, codigo_busca);
    clock_t end_arv = clock();
    double tempo_arv = ((double)(end_arv - start_arv)) / CLOCKS_PER_SEC;

    if (res_arv) {
        printf("\nLanche encontrado: %s\n", get_nome(res_arv));
    } else {
        printf("\nLanche nao encontrado.\n");
    }

    printf("\n--- RESULTADOS ---\n");
    printf("Tempo na Lista (Sequencial): %f s\n", tempo_lista);
    printf("Tempo na Arvore (Binaria):    %f s\n", tempo_arv);

    return 0;
}