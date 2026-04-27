#include <stdio.h>

int main(){

    int semaforo1, semaforo2, mmc;

    printf("Insira o intervalos de tempo(em segundos) de dois semaforos: \n");
    scanf("%d %d", &semaforo1, &semaforo2);

    mmc = semaforo1;

    while(mmc % semaforo2 != 0){
        mmc = mmc + semaforo1;
    }

    printf("O MMC dos intervalos %d e %d: %d", semaforo1, semaforo2, mmc);

    return 0;
}
