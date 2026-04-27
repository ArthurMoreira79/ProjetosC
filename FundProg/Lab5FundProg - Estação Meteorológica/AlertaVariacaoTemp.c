#include <stdio.h>
#include <math.h>

int verificarAlertas(float *d1, float *d2, int n);

int main(){
    float dia1[24], dia2[24];
    int i;

    printf("Digite as 24 Temperaturas do Dia 1:\n");
    for(i = 0; i < 24; i++){
        printf("Hora %02dh: ", i);
        scanf("%f", &dia1[i]);
    }

    printf("Digite as 24 Temperaturas do Dia 2:\n");
    for(i = 0; i < 24; i++){
        printf("Hora %02dh: ", i);
        scanf("%f", &dia2[i]);
    }

    printf("\n--- Verificacao de Alertas ---\n");
    int totalAlertas = verificarAlertas(dia1, dia2, 24);

    printf("\nTotal de Alertas gerados: %d\n", totalAlertas);

    return 0;
}

int verificarAlertas(float *d1, float *d2, int n){
    int cont = 0;

    for(int i = 0; i < n; i++){
        float diferenca = fabs(*(d1 + i) - *(d2 + i));

        if(diferenca > 5.0){
            printf("ALERTA: Variacao de %.1f C as %dh\n", diferenca, i);
            cont++;
        }
    }
    return cont;
}