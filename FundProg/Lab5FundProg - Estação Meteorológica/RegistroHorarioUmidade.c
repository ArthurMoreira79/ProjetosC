#include <stdio.h>

float media(float *v, int n);
int indiceMaior(float *v, int n);
int indiceMenor(float *v, int n);
int acimaDe80(float *v, int n);

int main(){

    float umidade[24];
    int i;

    printf("Digite a unidade para cada uma das 24 horas (0 - 100%%): \n");
    for(i = 0; i < 24; i++){
        printf("Hora %02dh: ", i);
        scanf("%f", &umidade[i]);
    }

    float m = media(umidade, 24);
    int hMaior = indiceMaior(umidade, 24);
    int hMenor = indiceMenor(umidade, 24);
    int totalCritico = acimaDe80(umidade, 24);

    printf("\n--- Relatorio de Umidade Diaria ---\n");
    printf("Media de umidade: %.2f%%\n", m);

    printf("Maior umidade as %dh (Valor: %.1f%%)\n", hMaior, *(umidade + hMaior));
    printf("Menor umidade as %dh (Valor: %.1f%%)\n", hMenor, *(umidade + hMenor));
    
    printf("Horarios com umidade acima de 80%%: %d\n", totalCritico);

    return 0;
}

float media(float *v, int n){
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += *(v + i);
    }
    return soma / n;
}

int indiceMaior(float *v, int n){
    int ind = 0;
    float m = *v;
    for(int i = 1; i < n; i++){
        if(*(v + i) > m){
            m = *(v + i);
            ind = i;
        }
    }
    return ind;
}

int indiceMenor(float *v, int n) {
    int ind = 0;
    float m = *v;
    for (int i = 1; i < n; i++) {
        if (*(v + i) < m) {
            m = *(v + i);
            ind = i;
        }
    }
    return ind;
}

int acimaDe80(float *v, int n){
    int cont = 0;
    for(int i = 0; i < n; i++){
        if(*(v + i) > 80.0){
            cont++;
        }
    }
    return cont;
}