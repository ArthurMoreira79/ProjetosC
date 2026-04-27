#include <stdio.h>

int main(){

    int num;

    printf("Insira um numero inteiro: \n");
    scanf("%d", &num);

    if(num % 2 == 0){
        printf("Numero Par.");
    } else{
        printf("Numero Impar.");
    }

    return 0;
}