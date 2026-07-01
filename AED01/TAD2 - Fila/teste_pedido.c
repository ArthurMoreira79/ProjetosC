#include <stdio.h>
#include "pedido.h"

int main() {
    pedido_t *p = pedido_criar(
        10,            //id
        "Pedro Lucas", //cliente
        "09:30",       //hora
        2,             //prioridade
        152.70,        //valor
        "expressa"     //tipo
    );

    if (!p) {
        printf("Erro ao criar pedido!\n");
        return 1;
    }

    printf("Teste do TAD Pedido \n");
    pedido_imprimir(p);

    printf("\nTestando getters \n");
    printf("ID: %d\n", pedido_get_id(p));
    printf("Cliente: %s\n", pedido_get_cliente(p));
    printf("Hora: %s\n", pedido_get_hora(p));
    printf("Prioridade: %d\n", pedido_get_prioridade(p));
    printf("Valor: %.2f\n", pedido_get_valor(p));
    printf("Tipo entrega: %s\n", pedido_get_tipo(p));

    pedido_destruir(p);

    printf("\nPressione ENTER para sair...\n");
    getchar();
    getchar();

    return 0;
    
}