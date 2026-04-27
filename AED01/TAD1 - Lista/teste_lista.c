#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "lanche.h"

#define NOME_ARQUIVO "cardapio.txt"

int main() {
    printf("--- TESTE TAD LISTA ---\n");
    
    FILE *arquivo;
    int codigo;
    float preco;
    char nome[50];
    char categoria[30];
    int itens_lidos = 0;

    Lista* cardapio = criar_lista();
    
    if (cardapio == NULL) {
        printf("Falha ao criar a lista. Encerrando.\n");
        return 1;
    }
    
    arquivo = fopen(NOME_ARQUIVO, "r");
    
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo %s. Verifique o caminho e o nome.\n", NOME_ARQUIVO);
        liberar_lista(cardapio);
        return 1;
    }

    printf("\n=> Lendo dados do arquivo '%s'...\n", NOME_ARQUIVO);

    while (fscanf(arquivo, "%d, %49[^,], %f, %29[^\n]\n", &codigo, nome, &preco, categoria) == 4) {
        
        Lanche* novo_lanche = criar_lanche(codigo, nome, preco, categoria);
        
        if (inserir(cardapio, novo_lanche)) {
            itens_lidos++;
        } else {
            liberar_lanche(novo_lanche);
            printf("AVISO: Lista Cheia ou erro ao inserir lanche: %s\n", nome);
            break;
        }
    }

    fclose(arquivo);

    printf("\nLeitura concluida. Total de %d item(s) inserido(s).\n", itens_lidos);

    listar(cardapio);
    
    int codigo_busca = 201;
    Lanche* encontrado = buscar(cardapio, codigo_busca);
    if (encontrado) {
        printf("\n=> Busca pelo Codigo %d:\n", codigo_busca);
        printf("ENCONTRADO: %s | Preco: R$ %.2f | Categoria: %s\n", get_nome(encontrado), get_preco(encontrado), get_categoria(encontrado));
    } else {
        printf("\n=> Busca pelo Codigo %d: NAO ENCONTRADO.\n", codigo_busca);
    }
    
    int codigo_remover = 502;
    if (remover(cardapio, codigo_remover)) {
        printf("\n=> Removido o item com Codigo %d com sucesso.\n", codigo_remover);
    }
    
    printf("\n=> Lista apos remocao:\n");
    listar(cardapio);
    
    liberar_lista(cardapio);
    printf("\n--- Teste de lista com leitura de arquivo concluido! ---\n");

    return 0;
}