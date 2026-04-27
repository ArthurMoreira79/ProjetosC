#include <stdio.h>

int main(){

    int num, original, reverso = 0, resto;

    printf("Insira um numero inteiro: ");
    scanf("%d", &num);

    original = num;

    while(num != 0){
        resto = num % 10;
        reverso = reverso * 10 + resto;
        num /= 10;
    }

    if(original == reverso && original >= 0){
        printf("%d eh um palindromo.\n", original);
    } else{
        printf("%d nao eh um palindromo.\n", original);
    }

    return 0;
}