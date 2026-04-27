#include <stdio.h>

int main() {
    int numero;

    printf("Digite um numero (1-3999): ");
    scanf("%d", &numero);

    if (numero < 1 || numero > 3999) {
        printf("Numero fora do intervalo permitido.\n");
        return 1; 
    }

    int valores[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *simbolos[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    printf("Resultado em Romano: ");

    for (int i = 0; i < 13; i++) {

        while (numero >= valores[i]) {
            printf("%s", simbolos[i]);
            numero = numero - valores[i];
        }
    }

    printf("\n");

    return 0;
}