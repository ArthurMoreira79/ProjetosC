#include <stdio.h>

int main(){

    float peso, altura, imc;

    printf("Insira seu peso (Kg): \n");
    scanf("%f", &peso);
    printf("Insira sua altura (ex: 1.75): \n");
    scanf("%f", &altura);

    imc = peso/(altura * altura);

    printf("\nSeu IMC eh: %.2f\n", imc);

    if(imc < 18.5){
        printf("Classificacao: Abaixo do peso.\n");
    } else if(imc >= 18.5 && imc < 25){
        printf("Classificacao: Peso normal.\n");
    } else if(imc >= 25 && imc < 30){
        printf("Classificacao: Acima do peso.\n");
    } else{
        printf("Classificacao: Obesidade.");
    }

    return 0;
}