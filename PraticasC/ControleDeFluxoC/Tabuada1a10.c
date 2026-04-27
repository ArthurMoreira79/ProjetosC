#include <stdio.h>

int main(){

    int num, resultado;

    printf("Insira um numero para ver sua tabuada: \n");
    scanf("%d", &num);

    printf("--- TABUADA DO NUMERO %d ---\n", num);

    printf("--- ADICAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = num + i;
        printf("%d + %d = %d\n", num, i, resultado);
    }
    printf("--- SUBTRACAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = num - i;
        printf("%d - %d = %d\n", num, i, resultado);
    }
    printf("--- MULTIPLICACAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = num * i;
        printf("%d X %d = %d\n", num, i, resultado);
    }
    printf("--- DIVISAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = num / i;
        printf("%d / %d = %d\n", num, i, resultado);
    }

    printf("\n");

    return 0;
}