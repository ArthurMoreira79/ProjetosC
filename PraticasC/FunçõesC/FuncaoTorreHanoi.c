#include <stdio.h>

void torreDeHanoi(int n, char origem, char destino, char auxiliar){
    if(n == 1){
        printf("Mover disco 1 da haste %c para a haste %c\n", origem, destino);
        return;
    }
    torreDeHanoi(n - 1, origem, auxiliar, destino);
    printf("Mover disco %d da haste %c para a haste %c\n", n, origem, destino);
    torreDeHanoi(n - 1, auxiliar, destino, origem);
}

int main(){

    int discos = 3;

    printf("Solucao para %d discos:\n", discos);
    torreDeHanoi(discos, 'A', 'C', 'B');

    return 0;
}