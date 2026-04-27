#include <stdio.h>

float calcularMedia(int notas[], int tamanho){
    if(tamanho <= 0) return 0.0;

    int soma = 0;
    for(int i = 0; i < tamanho; i++){
        soma += notas[i];
    }

    return (float)soma / tamanho;
}

int main(){

    int minhasNotas[] = {8, 7, 9, 10, 6};
    int tam = sizeof(minhasNotas) / sizeof(minhasNotas[0]);
    float media = calcularMedia(minhasNotas, tam);

    printf("A media das notas eh: %.2f\n", media);

    return 0;
}