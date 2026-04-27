#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gerarNumero();
int calcularDistancia(int chute, int alvo);
void fornecerDica(int chute, int alvo);

int main(){

    srand(time(NULL));

    int numeroSecreto = gerarNumero();
    int chute;
    int acerto = 0;

    for (int i = 1; i <= 5; i++) {
        printf("Tentativa %d/5 - Digite seu chute (1-100): ", i);

        if (scanf("%d", &chute) != 1) break;

        if (chute == numeroSecreto) {
            printf("Parabens! Voce acertou!\n");
            acerto = 1;
            break;
        } else {
            fornecerDica(chute, numeroSecreto);
        }
    }

    if (!acerto) {
        printf("Suas chances acabaram. O numero era %d.\n", numeroSecreto);
    }
    return 0;
}

int gerarNumero(){
    return rand() % 100 + 1;
}

int calcularDistancia(int chute, int alvo){
    return abs(chute - alvo);
}

void fornecerDica(int chute, int alvo){
    int distancia = calcularDistancia(chute, alvo);

    if(alvo > chute){
        printf("Esta a direita.\n");
    } else{
        printf("Esta a esquerda.\n");
    }

    if(distancia < 8){
        printf("ESTA QUENTE!\n");
    } else if(distancia <= 15){
        printf("ESTA MORNO!\n");
    } else{
        printf("ESTA FRIO!\n");
    }
}