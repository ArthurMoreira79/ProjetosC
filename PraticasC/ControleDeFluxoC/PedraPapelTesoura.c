#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int escolhaUsuario, escolhaComputador;
    int placarUsuario = 0, placarPC = 0;
    int jogarNovamente;

    srand(time(NULL));

    do{
        printf("\n--- PEDRA, PAPEL E TESOURA ---\n");
        printf("Placar: Voce %d x %d Computador\n", placarUsuario, placarPC);
        printf("1 - Pedra\n2 - Papel\n3 - Tesoura\nEscolha sua jogada: ");
        scanf("%d", &escolhaUsuario);

        escolhaComputador = (rand() % 3) + 1;

        printf("Voce escolheu: %d | Computador escolheu: %d\n", escolhaUsuario, escolhaComputador);

        if(escolhaUsuario == escolhaComputador){
            printf("EMPATE!\n");
        } 
        else if((escolhaUsuario == 1 && escolhaComputador == 3) || 
                 (escolhaUsuario == 2 && escolhaComputador == 1) || 
                 (escolhaUsuario == 3 && escolhaComputador == 2)){
            printf("VOCE VENCEU ESTA RODADA!\n");
            placarUsuario++;
        }
        else{
            printf("COMPUTADOR VENCEU ESTA RODADA!\n");
            placarPC++;
        }

        printf("\nDeseja jogar novamente? (1-SIM / 0-SAIR): ");
        scanf("%d", &jogarNovamente);

    } while(jogarNovamente == 1);

    printf("\nFim de jogo! Placar Final: Voce %d x %d PC\n", placarUsuario, placarPC);

    return 0;
}