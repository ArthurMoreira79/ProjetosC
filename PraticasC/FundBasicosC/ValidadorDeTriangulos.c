#include <stdio.h>

int main(){

    float a, b, c;

    printf("--- Validador de Triangulos ---\n");
    printf("Digite o comprimento do lado A: ");
    scanf("%f", &a);
    printf("Digite o comprimento do lado B: ");
    scanf("%f", &b);
    printf("Digite o comprimento do lado C: ");
    scanf("%f", &c);

    if((a + b > c) && (a + c > b) && (b + c > a)){
        printf("\nOs lados %.2f, %.2f e %.2f formam um triangulo valido.\n", a, b, c);

        if(a == b && b == c){
            printf("Tipo: Equilatero (todos os lados iguais).\n");
        } else if(a == b || a == c || b == c){
            printf("Tipo: Isoceles (dois lados iguais).\n");
        } else{
            printf("Tipo: Escaleno (nenhum lado igual).\n");
        }
    } else{
        printf("\nOs lados informados nao podem formar um trianfulo.\n");
        printf("Motivo: um dos lados eh maior ou igual a soma dos outros dois.\n");
    }

    return 0;
}