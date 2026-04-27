#include <stdio.h>

int main() {
    int num;
    unsigned long long fatorial = 1;

    printf("Digite un numero inteiro positivo: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Erro: Não existe fatorial de numero negativo.\n");
    } else {
        for (int i = 1; i <= num; i++) {
            fatorial *= i;
        }
        printf("O fatorial de %d eh: %llu\n", num, fatorial);
    }

    return 0;
}