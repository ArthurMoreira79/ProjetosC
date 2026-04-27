#include <stdio.h>

float media(float *v, int n);
float maior(float *v, int n);
float menor(float *v, int n);
int acimaMedia(float *v, int n, float mediaValor);

int main(){

    float temperatura[7];
    int i;

    printf("Digite as 7 temperaturas da semana (Entre -10C e 50C): \n");
    for(i = 0; i < 7; i ++){
        printf("Dia %d: ", i + 1);
        scanf("%f", &temperatura[i]);
    }

    float m = media(temperatura, 7);
    float max = maior(temperatura, 7);
    float min = menor(temperatura, 7);
    int acima = acimaMedia(temperatura, 7, m);

    printf("\n--- Relatorio Semanal ---\n");
    printf("Media semanal: %.2f\n", m);
    printf("Maior temperatura: %.2f\n", max);
    printf("Menor temperatura: %.2f\n", min);
    printf("Dias acima da media: %d\n", acima);

    return 0;
}

float media(float *v, int n){
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += *(v + i);
    }
    return soma / n;
}

float maior(float *v, int n){
    float m = *v;
    for(int i = 1; i < n; i++){
        if(*(v + i) > m){
            m = *(v + i);
        }
    }
    return m;
}

float menor(float *v, int n){
    float m = *v;
    for(int i = 1; i < n; i++){
        if(*(v + i) < m){
            m = *(v + i);
        }
    }
    return m;
}

int acimaMedia(float *v, int n, float mediaValor){
    int cont = 0;
    for(int i = 0; i < n; i++){
        if(*(v + i) > mediaValor){
            cont++;
        }
    }
    return cont;
}