#include <stdio.h>

int main() {
    int num;
    double t1 = 0, t2 = 1, proximo;

    printf("Insira a quantidade de termos: ");
    scanf("%d", &num);

    printf("--- %d PRIMEIROS TERMOS DA SEQUENCIA DE FIBONACCI ---\n", num);

    for (int i = 1; i <= num; i++) {
        printf("%.0f ", t1);
        proximo = t1 + t2;
        t1 = t2;
        t2 = proximo;
    }
    return 0;
}