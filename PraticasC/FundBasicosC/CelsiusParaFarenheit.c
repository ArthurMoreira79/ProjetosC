#include <stdio.h>

int main(){
    
    float tempF;
    float tempC;

    printf("insira a temperatura em graus celcius: \n");
    scanf("%f", &tempC);

    tempF = (tempC * 9/5) + 32;

    printf("Temperatura em Graus Celcius: %.2f\n", tempC);
    printf("Temperatura em Farenheit: %.2f\n", tempF);

    return 0;
}