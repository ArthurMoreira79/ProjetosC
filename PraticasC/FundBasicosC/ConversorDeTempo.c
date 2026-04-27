#include <stdio.h>

int main(){

    int totalSegundos, segundo, minuto, hora;

    printf("Insira uma quantidade de segundos: \n");
    scanf("%d", &totalSegundos);

    hora = totalSegundos/3600;

    int resto = totalSegundos % 3600;

    minuto = resto/60;
    segundo = resto % 60;

    printf("Resultado: %02d:%02d:%02d\n", hora, minuto, segundo);

    return 0;
}