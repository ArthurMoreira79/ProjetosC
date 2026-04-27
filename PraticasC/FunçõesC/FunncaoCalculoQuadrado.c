#include <stdio.h>

int calcularQuadrado(int numero){

    return numero * numero;
}

int main(){

    int num;

    printf("Insira um numero para ver seu quadrado: ");
    scanf("%d", &num);

    int resultado = calcularQuadrado(num);

    printf("O quadrado de %d eh %d.\n", num, resultado);

    return 0;
}