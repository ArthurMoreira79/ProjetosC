#include <stdio.h>
#include <math.h>

float calcularTaxa(float horas);

int main(){

    char nome[5][50];
    float horas[5];
    float taxa[5];
    float totalHoras = 0.0;
    float totalTaxa = 0.0;

    for (int i = 0; i < 5; i++) {
        printf("Digite o nome e as horas do cliente %d: ", i + 1);
        scanf("%s %f", nome[i], &horas[i]);
        taxa[i] = calcularTaxa(horas[i]);
        
        totalHoras += horas[i];
        totalTaxa += taxa[i];
    }

    printf("\n%-15s %-10s %-10s\n", "Cliente", "Horas", "Taxa");

    for (int i = 0; i < 5; i++) {
        printf("%-15s %-10.1f %-10.2f\n", nome[i], horas[i], taxa[i]);
    }

    printf("%-15s %-10.1f %-10.2f\n", "TOTAL", totalHoras, totalTaxa);

    return 0;
}

float calcularTaxa(float horas){
    float taxa = 10.00;

    if(horas > 3.0){
        taxa += ceil(horas - 3.0) * 1.50;
    }
    if(taxa > 20.00){
        taxa = 20.00;
    }
    return taxa;
}