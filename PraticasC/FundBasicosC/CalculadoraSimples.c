#include <stdio.h>

int main(){
    int num1, num2;
    int soma;
    int subt;
    int mult;
    float divis;

    printf("insira dois numeros inteiros: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);

    soma = num1 + num2;
    subt = num1 - num2;
    mult = num1 * num2;
    divis = num1 / num2;

    printf("Resultados:\n");
    printf("soma: %d\n", soma);
    printf("subtracao: %d\n", subt);
    printf("multiplicacao: %d\n", mult);
    printf("divisao: %.2f\n", divis);
    
    return 0;
}