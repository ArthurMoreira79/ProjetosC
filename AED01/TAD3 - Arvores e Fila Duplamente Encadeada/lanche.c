#include "lanche.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lanche {         //estrutura do lanche
    int codigo;         //codigo é a chave primaria
    char nome[50];
    float preco;
    char categoria[30];
};

Lanche* criar_lanche(int codigo, const char* nome, float preco, const char* categoria) {
    Lanche* novo_lanche = (Lanche*)malloc(sizeof(Lanche));      //aloca memória
    if (novo_lanche == NULL) {                                  //trata erro de alocação
        printf("Erro ao alocar memoria para o lanche.\n");
        return NULL;
    }
    
    novo_lanche->codigo = codigo;
    strncpy(novo_lanche->nome, nome, 49);
    novo_lanche->nome[49] = '\0';
    strncpy(novo_lanche->categoria, categoria, 29);
    novo_lanche->categoria[29] = '\0';
    novo_lanche->preco = preco;
    
    return novo_lanche;
}

void liberar_lanche(Lanche* l) {            //libera o lanche
    if (l != NULL) {
        free(l);
    }
}

void imprimir_lanche(Lanche* l) {
    if (l == NULL) {
        printf("Lanche invalido/nulo.\n");          //impressão dos atributos de lanche
        return;
    }
    printf("--- Lanche ---\n");
    printf("Codigo: %d\n", l->codigo);
    printf("Nome: %s\n", l->nome);
    printf("Preco: R$ %.2f\n", l->preco);
    printf("Categoria: %s\n", l->categoria);
    printf("--------------\n");
}

int get_codigo(Lanche* l) {                 //getters
    if (l == NULL) return -1;
    return l->codigo;
}

float get_preco(Lanche* l) {
    if (l == NULL) return 0.0f;
    return l->preco;
}

const char* get_nome(Lanche* l) {
    if (l == NULL) return "NOME_INVALIDO";
    return l->nome;
}

const char* get_categoria(Lanche* l) {
    if (l == NULL) return "CATEGORIA_INVALIDA";
    return l->categoria;
}