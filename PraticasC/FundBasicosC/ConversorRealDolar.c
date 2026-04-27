#include <stdio.h>

int main(){

    float reais;

    const float cotDolar = 5.17;
    const float cotEuro = 6.14;
    const float cotLibra = 7.06;

    printf("Conversor de Moedas (12/02/2026)\n");
    printf("Insira o valor em Reais (R$): \n");
    scanf("%f", &reais);

    float valorDolar = reais / cotDolar;
    float valorEuro = reais / cotEuro;
    float valorLibra = reais / cotLibra;

    printf("\nResultados da Conversao:\n");
    printf("----------------------------------\n");
    printf("%-15s | %-15s\n", "MOEDA", "VALOR");
    printf("----------------------------------\n");
    printf("%-15s | %10.2f\n", "Dolar", valorDolar);
    printf("%-15s | %10.2f\n", "Euro", valorEuro);
    printf("%-15s | %10.2f\n", "Libra", valorLibra);
    printf("----------------------------------\n");
    
    return 0;
}