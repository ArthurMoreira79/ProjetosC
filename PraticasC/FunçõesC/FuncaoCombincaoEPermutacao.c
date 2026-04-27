#include <stdio.h>

double fatorial(int n) {
    double f = 1;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

double permutacao(int n, int k) {
    if (k > n) return 0;
    return fatorial(n) / fatorial(n - k);
}

double combinacao(int n, int k) {
    if (k > n) return 0;
    return fatorial(n) / (fatorial(k) * fatorial(n - k));
}

int main() {
    int n, k;

    printf("=== ANALISE COMBINATORIA ===\n");
    printf("Digite o valor de n (total): ");
    scanf("%d", &n);
    printf("Digite o valor de k (escolha): ");
    scanf("%d", &k);

    if (n < 0 || k < 0) {
        printf("Erro: Os valores devem ser positivos.\n");
    } else {
        printf("\nResultados:\n");
        printf("Permutacao P(%d, %d) = %.0f\n", n, k, permutacao(n, k));
        printf("Combinacao C(%d, %d) = %.0f\n", n, k, combinacao(n, k));
    }

    return 0;
}