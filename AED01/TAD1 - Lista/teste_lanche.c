#include <stdio.h>
#include "lanche.h"

int main() {
    printf("--- TESTE DO TAD LANCHE ---\n");
    
    Lanche* l1 = criar_lanche(101, "Cheeseburger", 15.50, "Lanche");
    Lanche* l2 = criar_lanche(202, "Suco Natural", 8.50, "Bebida");

    if (l1 == NULL || l2 == NULL) {
        if (l1) liberar_lanche(l1);
        if (l2) liberar_lanche(l2);
        return 1;
    }
    
    printf("\n=> Detalhes do Lanche 1:\n");
    imprimir_lanche(l1);

    printf("\n=> Teste de Getters (Lanche 2):\n");
    printf("Codigo: %d\n", get_codigo(l2));
    printf("Nome: %s\n", get_nome(l2));
    printf("Preco: R$ %.2f\n", get_preco(l2));
    printf("Categoria: %s\n", get_categoria(l2));
    
    liberar_lanche(l1);
    liberar_lanche(l2);
    
    printf("\n--- Teste de TAD Lanche concluido e memoria liberada! ---\n");
    
    return 0;
}