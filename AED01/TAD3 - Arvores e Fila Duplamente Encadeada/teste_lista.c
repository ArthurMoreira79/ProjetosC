#include <stdio.h>
#include "lista.h"
#include "lanche.h"

//função de compração customizada

int comparar_por_codigo(const void* lanche_v, const void* codigo_v) {
    Lanche* l = (Lanche*)lanche_v;                   // Cast de void* para tipo específico
    int cod_procurado = *(int*)codigo_v;    
    return (get_codigo(l) == cod_procurado) ? 0 : 1;     // 0 = igual
}


int main() {
    
    Lista* l = lista_criar();       //cria lista e adiciona elementos

    lista_inserir_final(l, criar_lanche(10, "Coxinha", 5.0, "Salgado"));
    lista_inserir_final(l, criar_lanche(20, "Kibe", 6.0, "Salgado"));
    lista_inserir_inicio(l, criar_lanche(5, "Cafe", 3.0, "Bebida"));

    printf("Tamanho da lista: %d\n", lista_tamanho(l));     //printa o tamanho

    int cod = 20;       //busca por codigo
    Lanche* buscado = (Lanche*)lista_buscar(l, &cod, comparar_por_codigo);
    
    if (buscado) {
        printf("Busca encontrou: %s\n", get_nome(buscado));
    } else {
        printf("Lanche nao encontrado.\n");
    }

    lista_destruir(l, (void (*)(void*))liberar_lanche);     //destruir lista
    printf("Lista destruida com sucesso!\n");

    return 0;
}
