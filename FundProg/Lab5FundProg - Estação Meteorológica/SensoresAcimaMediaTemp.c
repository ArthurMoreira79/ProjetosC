#include <stdio.h>

float media(float *v, int n);
void exibirAcima(char nomes[][21], float *v, int n, float mediaRef);

int main(){
    char nomes[10][21];
    float temperaturas[10];
    int i;

    printf("Registro de 10 Sensores:\n");
    for(i = 0; i< 10; i++){
        printf("Nome do sensor %d: ", i + 1);
        scanf("%s", nomes[i]);
        printf("Temperatura do sensor %d: ", i + 1);
        scanf("%f", &temperaturas[i]);
    }

    float m = media(temperaturas, 10);

    printf("\n--- Relatorio de Sensores ---\n");
    printf("Temperatura media geral: %.2f\n", m);
    printf("Sensores acima da media:\n");

    exibirAcima(nomes, temperaturas, 10, m);

    return 0;
}

float media(float *v, int n){
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += *(v + i);
    }
    return soma / n;
}

void exibirAcima(char nomes[][21], float *v, int n, float mediaRef){
    for(int i = 0; i < n; i++){
        if(*(v + i) > mediaRef){
            printf("- %s: %.2f\n", nomes[i], *(v + i));
        }
    }
}