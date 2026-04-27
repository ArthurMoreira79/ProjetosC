#include <stdio.h>
#include <math.h>

int main(){

    int num, NTermos, fat;
    float termo, soma;

    printf("Insira um numero inteiro para o valor X: ");
    scanf("%d", &num);
    printf("Insira o numero de termos desejados: ");
    scanf("%d", &NTermos);

    soma = 1;

    for(int i = 2; i <= NTermos; i++){
        fat = 1;
        for(int j = 1; j <= i + 1; j++){
            fat = fat * j;
        }
        termo = pow(num,i) / fat;

        if(i % 2 == 0){
            soma = soma + termo;
        } else{
            soma = soma - termo;
        }
    }
    printf("O valor da sequencia eh: %f", soma);

    return 0;
}