#include <stdio.h>

int ehPar(int n){
    if(n % 2 == 0){
        return 1;
    } else{
        return 0;
    }
}

int main(){

    int numero;

    printf("Insira um numero inteiro: ");
    scanf("%d", &numero);

    if(ehPar(numero)){
        printf("%d eh Par!\n", numero);
    } else{
        printf("%d eh Impar!\n", numero);
    }

    return 0;
}