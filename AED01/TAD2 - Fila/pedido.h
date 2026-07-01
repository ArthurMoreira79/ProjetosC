#ifndef PEDIDO_H
#define PEDIDO_H

typedef struct pedido {
    int id;
    char cliente[50];
    char hora[10];
    int prioridade;
    float valor;
    char tipo[20];

    char itens[10][50];     // até 10 itens
    int quantidades[10];    // quantidade por item
    float precos[10];       // preço unitário
    int qtd_itens;          // total de itens adicionados
} pedido_t;

// funções principais
pedido_t* pedido_criar(int id, const char* cliente, const char* hora,
                       int prioridade, float valor, const char* tipo);

void pedido_destruir(pedido_t* p);
void pedido_imprimir(const pedido_t* p);

// getters
int pedido_get_id(const pedido_t* p);
const char* pedido_get_cliente(const pedido_t* p);
const char* pedido_get_hora(const pedido_t* p);
int pedido_get_prioridade(const pedido_t* p);
float pedido_get_valor(const pedido_t* p);
const char* pedido_get_tipo(const pedido_t* p);

// FUNÇÕES (supermercado)
void pedido_adicionar_item(pedido_t* p, const char* nome, int qtd, float preco);
float pedido_calcular_total(const pedido_t* p);

#endif
