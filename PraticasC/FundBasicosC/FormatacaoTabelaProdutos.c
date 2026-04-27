#include <stdio.h>


int main(){

    char prod1[] = "Teclado", prod2[] = "Mouse", prod3[] = "Monitor";
    float preco1 = 150, preco2 = 85, preco3 = 1200;
    int qtd1 = 15, qtd2 = 30, qtd3 = 5;

    printf("%-15s | %-10s | %-8s\n", "PRODUTO", "PRECO", "QTD");
    printf("--------------------------------------------\n");

    printf("%-15s | R$ %7.2f | %8d\n", prod1, preco1, qtd1);
    printf("%-15s | R$ %7.2f | %8d\n", prod2, preco2, qtd2);
    printf("%-15s | R$ %7.2f | %8d\n", prod3, preco3, qtd3);

    printf("--------------------------------------------\n");


    return 0;
}