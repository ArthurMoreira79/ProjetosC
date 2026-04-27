#include <stdio.h>

int main(){

    int totalDias, anos, meses, dias;

    printf("Insira o total de dias vividos: \n");
    scanf("%d", &totalDias);

    anos = totalDias / 365;

    int restoAnos = totalDias % 365;

    meses = restoAnos / 30;

    dias = restoAnos % 30;

    printf("\nVoce viveu aproximadamente:\n");
    printf("%d anos, %d meses e %d dias.\n", anos, meses, dias);

    return 0;
}