#include <stdio.h>

int ehPrimo(int n){
    if(n <= 1) return 0;

    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int num;

    printf("Insira um numero inteiro, para ver se ele eh primo: ");
    scanf("%d", &num);

    if(ehPrimo(num)){
        printf("%d eh Primo!\n", num);
    } else{
        printf("%d nao eh Primo!\n", num);
    }

    return 0;
}