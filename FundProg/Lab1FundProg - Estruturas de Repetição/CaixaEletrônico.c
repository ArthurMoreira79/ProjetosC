#include <stdio.h>

int main(){

    int saldo = 1000;
    int valorSaque;

    printf("--- Caixa Eletronico ---\n");
    printf("Saldo atual: R$%d\n", saldo);
    
    printf("\nInsira o valor que deseja sacar (multiplo de 10): ");
    scanf("%d", &valorSaque);

    while(valorSaque % 10 != 0 || valorSaque > saldo || valorSaque <= 0){
        
        if(valorSaque % 10 != 0){
            printf("Valor invalido! Por favor, digite um multiplo de 10.\n");
        }
        else if(valorSaque > saldo){
            printf("Saldo insuficiente! Saldo disponivel: R$%d\n", saldo);
        }
        else if(valorSaque <= 0){
            printf("Valor invalido! Digite um valor positivo.\n");
        }
        
        printf("\nInsira o valor que deseja sacar: ");
        scanf("%d", &valorSaque);
    }

    saldo = saldo - valorSaque;

    printf("\n--- Saque concluido com sucesso! ---\n");
    printf("Valor sacado: R$%d\n", valorSaque);
    printf("Saldo apos saque: R$%d\n", saldo);

    return 0;
}