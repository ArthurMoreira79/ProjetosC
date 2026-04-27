#include <stdio.h>
#include "arvore.h"

void imprimir_id(void* dado) {

    printf("[Nodo presente] ");
}

int main() {
    printf("--- TESTE DO TAD ARVORE ---\n");

    Arvore* minha_arvore = arvore_criar();      //cria arvore

    printf("Inserindo chaves: 50, 30, 70, 20, 40...\n");    //inserção de chaves
    arvore_inserir(minha_arvore, 50, NULL);
    arvore_inserir(minha_arvore, 30, NULL);
    arvore_inserir(minha_arvore, 70, NULL);
    arvore_inserir(minha_arvore, 20, NULL);
    arvore_inserir(minha_arvore, 40, NULL);

    printf("\nPercurso em ordem (deve ser crescente): \n"); //percursão in order
    arvore_percorrer_em_ordem(minha_arvore, imprimir_id);
    printf("\n");

    int busca_ok = 30;
    void* res1 = arvore_buscar(minha_arvore, busca_ok);     //busca na árvore pela chave
    if (res1 == NULL) {
        printf("\nBusca pela chave %d: Nodo encontrado (sucesso).\n", busca_ok);
    }

    int busca_fail = 100;                               //busca na árvore pela chave(falha)
    void* res2 = arvore_buscar(minha_arvore, busca_fail);
    if (res2 == NULL) {
        printf("Busca pela chave %d: Chave nao encontrada (correto).\n", busca_fail);
    }

    arvore_destruir(minha_arvore);  //destruir arvore
    printf("\n--- Teste de Arvore concluido! ---\n");

    return 0;
}