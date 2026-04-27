#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool validarCPF(char cpf[]) {
    int i, soma, resto;
    int num[11];
    int j = 0;

    for (i = 0; cpf[i] != '\0' && j < 11; i++) {
        if (isdigit(cpf[i])) {
            num[j] = cpf[i] - '0';
            j++;
        }
    }

    if (j != 11) return false;

    bool todosIguais = true;
    for (i = 1; i < 11; i++) {
        if (num[i] != num[0]) {
            todosIguais = false;
            break;
        }
    }
    if (todosIguais) return false;

    soma = 0;
    for (i = 0; i < 9; i++) {
        soma += num[i] * (10 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != num[9]) return false;

    soma = 0;
    for (i = 0; i < 10; i++) {
        soma += num[i] * (11 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != num[10]) return false;

    return true;
}

int main() {
    char entrada[20]; 

    printf("=== ANALISADOR DE CPF ===\n");
    printf("Digite o CPF (apenas numeros ou com pontuacao): ");
    
    scanf("%s", entrada);

    printf("\nAnalisando: %s...\n", entrada);

    if (validarCPF(entrada)) {
        printf("RESULTADO: O CPF informado e VALIDO!\n");
    } else {
        printf("RESULTADO: O CPF informado e INVALIDO.\n");
    }

    printf("=========================\n");

    return 0;
}