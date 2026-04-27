#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pedido.h"

int main() {
    fila_t* fila = fila_criar();
    int opcao = 0;
    int id = 1;

    while (1) {
        printf("\nSISTEMA DE DELIVERY (SIMPLES)\n");
        printf("1. Criar novo pedido\n");
        printf("2. Desenfileirar pedido\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        getchar();

        if (opcao == 1) {
            char cliente[50];
            char hora[10];
            int prioridade;
            char tipo[20];

            printf("Nome do cliente: ");
            fgets(cliente, 50, stdin);
            cliente[strcspn(cliente, "\n")] = '\0';

            printf("Hora (ex: 08:30): ");
            fgets(hora, 10, stdin);
            hora[strcspn(hora, "\n")] = '\0';

            printf("Prioridade (1 = alta, 2 = normal): ");
            scanf("%d", &prioridade);
            getchar();

            printf("Tipo (expressa/normal): ");
            fgets(tipo, 20, stdin);
            tipo[strcspn(tipo, "\n")] = '\0';

            pedido_t* p = pedido_criar(id++, cliente, hora, prioridade, 0.0, tipo);

            pedido_adicionar_item(p, "Item padrão", 1, 9.99);

            fila_enfileirar(fila, p);
            printf("Pedido criado e enfileirado com sucesso!\n");
        }
        else if (opcao == 2) {
            if (fila_vazia(fila)) {
                printf("Fila vazia! Nada para remover.\n");
            } else {
                pedido_t* p = fila_desenfileirar(fila);
                printf("Pedido removido:\n");
                pedido_imprimir(p);
                pedido_destruir(p);
            }
        }
        else if (opcao == 3) {
            printf("Encerrando o sistema...\n");
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }

    fila_destruir(fila);
    return 0;
}
