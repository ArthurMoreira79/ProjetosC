#include <stdio.h>

int main(){

    float area;
    const float pi = 3.14;
    float raio;

    printf("insira o Raio da circunferencia: ");
    scanf("%f", &raio);

    area = pi * (raio * raio);

    printf("A Area da circunferencia eh: %.2f", area);
    
    return 0;
}