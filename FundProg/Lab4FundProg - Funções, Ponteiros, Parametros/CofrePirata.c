#include <stdio.h>

void trocarSeNecessario(int *azul, int *vermelho, int *houveTroca);
int cofreAbre(int azul, int vermelho);

int main(){

    int cristalAzul, cristalVermelho;
    int houveTroca = 0;

    printf("Insira o valor dos cristais azul e vermelho: ");

    if(scanf("%d %d", &cristalAzul, &cristalVermelho) != 2) return 0;

    trocarSeNecessario(&cristalAzul, &cristalVermelho, &houveTroca);

    if(houveTroca){
        printf("Cristais trocados!\n");
    } else{
        printf("Cristais nao foram trocados.\n");
    }

    printf("Cristal azul: %d\n", cristalAzul);
    printf("Cristal vermelho: %d\n", cristalVermelho);

    int soma = cristalAzul + cristalVermelho;
    printf("Soma: %d\n", soma);

    if(cofreAbre(cristalAzul, cristalVermelho)){
        printf("O cofre foi aberto com sucesso!\n");
    } else{
        printf("O cofre continua trancado.\n");
    }

    return 0;
}

void trocarSeNecessario(int *azul, int *vermelho, int *houveTroca){
    if(*vermelho > *azul){
        int temp = *azul;
        *azul = *vermelho;
        *vermelho = temp;
        *houveTroca = 1;
    } else{
        *houveTroca = 0;
    }
}

int cofreAbre(int azul, int vermelho){
    if((azul + vermelho) % 3 == 0){
        return 1;
    } else{
        return 0;
    }
}