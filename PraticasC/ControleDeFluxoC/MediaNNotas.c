#include <stdio.h>

int main(){

    int n;
    float media, nota, somaNotas;

    printf("Insira a quantidade de Notas: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        printf("Insira a nota %d: ", i+1);
        scanf("%f", &nota);
        somaNotas += nota;
    }

    media = somaNotas / n;

    printf("A media de notas eh: %.2f\n", media);

    return 0;
}