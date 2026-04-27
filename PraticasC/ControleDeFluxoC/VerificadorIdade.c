#include <stdio.h>

int main(){

    int idade;

    printf("Insira a sua idade: \n");
    scanf("%d", &idade);

    if(idade <= 12){
        printf("Voce eh uma crianca.");
    } else if(idade <= 17 && idade > 12){
        printf("Voce eh um adolescente.");
    } else if(idade <= 59 && idade > 17){
        printf("Voce eh um adulto.");
    } else{
        printf("Voce eh um idoso.");
    }

    return 0;
}