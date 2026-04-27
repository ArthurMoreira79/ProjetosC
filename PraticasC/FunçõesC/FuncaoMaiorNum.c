#include <stdio.h>

int maiorNum(int numero1, int numero2){

    if(numero1 > numero2){
        return numero1;
    } else{
        return numero2;
    }
}

int main(){

    int A, B;

    printf("Insira um valor para A e B: ");
    scanf("%d %d", &A, &B);

    int maior = maiorNum(A, B);

    printf("Entre %d e %d, o maior eh: %d\n", A, B, maior);

    return 0;
}