#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int dado1, dado2;
    int tentativas = 0;

    srand(time(NULL));

    printf("Iniciando lancamento dos dados...\n");
    printf("---------------------------------\n");

    do{
        tentativas++;
        dado1 = (rand() % 6) + 1;
        dado2 = (rand() % 6) + 1;

        printf("Tentativa %d: [%d] e [%d]\n", tentativas, dado1, dado2);

    }while (dado1 != dado2);

    printf("------------------------\n");
    printf("SAIU UM DUPLO! [%d-%d]\n", dado1, dado2);
    printf("Total de tentativas: %d\n", tentativas);

    return 0;
}