#include <stdio.h>

int inverterNumero(int n){
    int invertido = 0;

    while(n != 0){
        int resto = n % 10;
        invertido = invertido * 10 + resto;
        n /= 10;
    }

    return invertido;
}

int main(){

    int num;

    printf("Insira um numero inteiro: ");
    scanf("%d", &num);

    printf("Invertido: %d\n", inverterNumero(num));

    return 0;
}