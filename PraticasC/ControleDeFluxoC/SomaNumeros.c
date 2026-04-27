#include <stdio.h>

int main(){

    int num, somaTotal = 0;

    printf("Insira numeros para somar (0 para encerrar).\n");

    do{
        printf("Insira um numero: \n");
        scanf("%d", &num);

        if(num != 0){
            somaTotal += num;
        }
    }while(num != 0);

    printf("A soma total eh: %d\n", somaTotal);

    return 0;
}
