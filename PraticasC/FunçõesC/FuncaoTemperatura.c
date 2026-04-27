#include <stdio.h>

float celsiusParaFahr(float c){
    return (c * 9.0 / 5.0) + 32.0;
}

float fahrParaCelsius(float f){
    return (f - 32.0) * 5.0 / 9.0;
}

int main(){

    float tempC, tempF;

    printf("Insira uma temperatura em Celsius para ver sua equivalencia em Fahrenheit: ");
    scanf("%f", &tempC);
    printf("Insira uma temperatura em Fahrenheit para ver sua equivalencia em Celsius: ");
    scanf("%f", &tempF);

    printf("%.2f C equivale a %.2f°F\n", tempC, celsiusParaFahr(tempC));
    printf("%.2f F equivale a %.2f°C\n", tempF, fahrParaCelsius(tempF));

    return 0;
}