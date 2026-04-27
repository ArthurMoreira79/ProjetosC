#include <stdio.h>

int calcularMDC(int a, int b){
    if(b == 0){
        return a;
    }
    return calcularMDC(b, a % b);
}

int calcularMMC(int a, int b){
    if(a == 0 || b == 0) return 0;
    return (a / calcularMDC(a, b)) * b;
}

int main(){

    int n1, n2;

    printf("=== CALCULADORA DE MDC E MMC ===\n");
    printf("Digite o primeiro numero: ");
    scanf("%d", &n1);
    printf("Digite o segundo numero: ");
    scanf("%d", &n2);

    int mdc = calcularMDC(n1, n2);
    int mmc = calcularMMC(n1, n2);

    printf("\nResultados para %d e %d:\n", n1, n2);
    printf("MDC: %d\n", mdc);
    printf("MMC: %d\n", mmc);
    printf("================================\n");

    return 0;
}