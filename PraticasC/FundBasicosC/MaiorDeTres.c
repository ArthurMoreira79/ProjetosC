#include <stdio.h>

int main(){

    int num1, num2, num3;
    int maior;

    printf("Insira tres numeros inteiros: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    scanf("%d", &num3);

    maior = num1;

    if(num2 > maior){
        maior = num2;
    }
    if(num3 > maior){
        maior = num3;
    }

    printf("O maior numero eh: %d\n", maior);

    return 0;
}