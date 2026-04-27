#include <stdio.h>
#include <stdbool.h>

int main(){

    int num;
    bool ehPrimo = true;

    printf("Insiran um numero inteiro: ");
    scanf("%d", &num);

    if(num <= 1){
        ehPrimo = false;
    } else{
        for(int i = 2; i <= num / 2; i++){
            if(num % i == 0){
                ehPrimo = false;
                break;
            }
        }
    }

    if(ehPrimo){
        printf("%d eh um numero primo.\n", num);
    } else{
        printf("%d nao eh um numero primo.\n", num);
    }

    return 0;
}