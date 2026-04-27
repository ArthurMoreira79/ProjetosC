#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int palpite, tentativas, opcao;
    int numSecreto;

    srand(time(NULL));

    do{
        numSecreto = (rand() % 100) + 1;

        tentativas = 0;
        printf("\n--- JOGO DA ADVINHACAO ---\n");
        printf("Tente advinhar o numero entre 1 e 100!\n");

        do{
            printf("Seu palpite: ");
            scanf("%d", &palpite);
            tentativas++;

            if(palpite < numSecreto){
                printf("Muito baixo!\n");
            } else if(palpite > numSecreto){
                printf("Muito alto!\n");
            } else{
                printf("Boa! Voce acertou o numero %d em %d tentativas!\n", numSecreto, tentativas);
            }
        } while(palpite != numSecreto);

        printf("\nJogar de novo? (1-SIM / 0-NAO): ");
        scanf("%d", &opcao);

    } while(opcao == 1);

    return 0;
}