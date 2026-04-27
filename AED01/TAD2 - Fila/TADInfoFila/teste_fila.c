#include <stdio.h>
#include "fila.h"
#include "pedido.h"

int main() {
    fila_t* f = fila_criar();

    pedido_t* p1 = pedido_criar(1, "Joao", "08:00", 1, 120.0, "expressa");
    pedido_t* p2 = pedido_criar(2, "Maria", "09:10", 2, 89.0, "normal");

    // Adicionando itens p1
    pedido_adicionar_item(p1, "Arroz 5kg", 1, 22.99);
    pedido_adicionar_item(p1, "Detergente", 3, 2.79);
    pedido_adicionar_item(p1, "Leite 1L", 2, 4.98);

    // Adicionando itens p2
    pedido_adicionar_item(p2, "Carne bovina 1kg", 2, 34.50);
    pedido_adicionar_item(p2, "Refrigerante 2L", 1, 7.80);
    pedido_adicionar_item(p2, "Macarrão 500g", 1, 4.30);


    printf("Enfileirando pedidos\n");
    fila_enfileirar(f, p1);
    fila_enfileirar(f, p2);

    printf("\nDesenfileirando\n");

    pedido_t* x = fila_desenfileirar(f);
    pedido_imprimir(x);
    pedido_destruir(x);

    x = fila_desenfileirar(f);
    pedido_imprimir(x);
    pedido_destruir(x);

    fila_destruir(f);

    printf("\nPressione ENTER para sair...\n");
    getchar();
    getchar();

    return 0;
}