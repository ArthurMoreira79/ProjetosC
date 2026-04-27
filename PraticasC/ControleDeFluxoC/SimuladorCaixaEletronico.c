#include <stdio.h>

int main() {
    float saldo = 1000.00;
    float valor;
    int opcao, sair = 0;

    while (sair == 0) {
        printf("\n======= CAIXA ELETRONICO =======\n");
        printf("Saldo atual: R$ %.2f\n", saldo);
        printf("1. Saque\n");
        printf("2. Deposito\n");
        printf("3. Extrato (Ver Saldo)\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor do saque: ");
                scanf("%f", &valor);
                if (valor > 0 && valor <= saldo) {
                    saldo -= valor;
                    printf("Saque de R$ %.2f realizado com sucesso!\n", valor);
                } else {
                    printf("Saldo insuficiente ou valor invalido.\n");
                }
                break;

            case 2:
                printf("Valor do deposito: ");
                scanf("%f", &valor);
                if (valor > 0) {
                    saldo += valor;
                    printf("Deposito de R$ %.2f realizado!\n", valor);
                } else {
                    printf("Valor de deposito invalido.\n");
                }
                break;

            case 3:
                printf("\n--- EXTRATO ---\n");
                printf("Saldo Disponivel: R$ %.2f\n", saldo);
                printf("---------------\n");
                break;

            case 4:
                printf("Encerrando operacao... Volte sempre!\n");
                sair = 1;
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}