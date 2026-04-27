#include <stdio.h>

void contagemRegressiva(int n){
    if(n < 0){
        printf("Fim!\n");
        return;
    }
    printf("%d...", n);

    contagemRegressiva(n - 1);
}

int main(){

    int inicio;

    printf("Insira um numero para iniciar a contagem: \n");
    scanf("%d", &inicio);

    printf("Inicio da contagem:\n");
    contagemRegressiva(inicio);

    return 0;
}