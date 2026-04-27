#ifndef LANCHE_H
#define LANCHE_H

typedef struct lanche Lanche;

Lanche* criar_lanche(int codigo, const char* nome, float preco, const char* categoria);

void liberar_lanche(Lanche* l);

void imprimir_lanche(Lanche* l);

int get_codigo(Lanche* l);

float get_preco(Lanche* l);

const char* get_nome(Lanche* l);

const char* get_categoria(Lanche* l);

#endif