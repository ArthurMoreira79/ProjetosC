#include <stdio.h>

void imprimirTabuada(int n){

    int resultado;

    printf("--- TABUADA DO NUMERO %d ---\n", n);

    printf("--- ADICAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = n + i;
        printf("%d + %d = %d\n", n, i, resultado);
    }
    printf("--- SUBTRACAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = n - i;
        printf("%d - %d = %d\n", n, i, resultado);
    }
    printf("--- MULTIPLICACAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = n * i;
        printf("%d X %d = %d\n", n, i, resultado);
    }
    printf("--- DIVISAO ---\n");
    for(int i = 1; i < 11; i++){
        resultado = n / i;
        printf("%d / %d = %d\n", n, i, resultado);
    }
}

int main(){
    
    int numero;

    printf("Digite um numero para ver sua tabuada: ");
    scanf("%d", &numero);

    imprimirTabuada(numero);

    return 0;
}