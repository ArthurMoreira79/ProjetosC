#ifndef FILA_H
#define FILA_H

// Tipo de dado genérico armazenado na fila
typedef void* dado_t;

// Tipo opaco da fila
typedef struct fila_t fila_t;

// Cria fila vazia
fila_t* fila_criar();

// Insere no final
int fila_enfileirar(fila_t* f, dado_t item);

// Remove do início
dado_t fila_desenfileirar(fila_t* f);

// Retorna 1 se estiver vazia
int fila_vazia(fila_t* f);

// Libera a fila
void fila_destruir(fila_t* f);

#endif