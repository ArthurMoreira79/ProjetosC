#include <stdio.h>

int main(){
    int opcao;
    int qtdProd = 150;

    printf("--- Sistema de Controle do EStoque ---");

    do{
        printf("======================================\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Consultar estoque\n");
        printf("0 - Sair\n");
        printf("======================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("\nProduto adicionado ao estoque com sucesso!\n");
                qtdProd++;
                break;
            case 2:
                printf("\nProduto removido do estoque com sucesso!\n");
                qtdProd--;
                break;
            case 3:
                printf("\nConsultando estoque...\n");
                printf("Estoque atual: %d produtos disponiveis.\n", qtdProd);
                break;
            case 0:
                printf("\nEncerrando sistema...\n");
                printf("Obrigado por utilizar o Sistema de Controle do Estoque");
        }
    }while(opcao != 0);
    
    return 0;
}