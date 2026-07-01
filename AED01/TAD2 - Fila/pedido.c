#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"

pedido_t* pedido_criar(int id, const char* cliente, const char* hora,
                       int prioridade, float valor, const char* tipo) {
    pedido_t* p = (pedido_t*) malloc(sizeof(pedido_t));
    if (p == NULL) {
        return NULL;
    }

    p->id = id;
    strcpy(p->cliente, cliente);
    strcpy(p->hora, hora);
    p->prioridade = prioridade;
    p->valor = valor;
    strcpy(p->tipo, tipo);

    // Inicializa itens
    p->qtd_itens = 0;

    return p;
}

void pedido_destruir(pedido_t* p) {
    if (p != NULL) {
        free(p);
    }
}

void pedido_imprimir(const pedido_t* p) {
    if (p == NULL) return;

    printf("\nPedido[id=%d, cliente='%s', hora=%s, prioridade=%d, tipo='%s']\n",
        p->id, p->cliente, p->hora, p->prioridade, p->tipo);

    printf("Itens:\n");
    for (int i = 0; i < p->qtd_itens; i++) {
        printf("  - %s (qtd: %d, preco: %.2f)\n",
               p->itens[i],
               p->quantidades[i],
               p->precos[i]);
    }

    float total = pedido_calcular_total(p);
    printf("Total do pedido: R$ %.2f\n", total);
}

int pedido_get_id(const pedido_t* p) {
    return p->id;
}

const char* pedido_get_cliente(const pedido_t* p) {
    return p->cliente;
}

const char* pedido_get_hora(const pedido_t* p) {
    return p->hora;
}

int pedido_get_prioridade(const pedido_t* p) {
    return p->prioridade;
}

float pedido_get_valor(const pedido_t* p) {
    return p->valor;
}

const char* pedido_get_tipo(const pedido_t* p) {
    return p->tipo;
}

// FUNÇÕES: Itens do Pedido

void pedido_adicionar_item(pedido_t* p, const char* nome, int qtd, float preco) {
    if (p == NULL) return;

    if (p->qtd_itens >= 10) {
        printf("Limite de itens atingido!\n");
        return;
    }

    int i = p->qtd_itens;

    strcpy(p->itens[i], nome);
    p->quantidades[i] = qtd;
    p->precos[i] = preco;

    p->qtd_itens++;
}

float pedido_calcular_total(const pedido_t* p) {
    if (p == NULL) return 0.0f;

    float total = 0.0f;

    for (int i = 0; i < p->qtd_itens; i++) {
        total += p->quantidades[i] * p->precos[i];
    }

    return total;
}
