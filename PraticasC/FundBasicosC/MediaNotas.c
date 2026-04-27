#include <stdio.h>

int main(){

    int nota1, nota2, nota3, nota4;
    float media;

    printf("insira a nota 1: \n");
    scanf("%d", &nota1);
    printf("insira a nota 2: \n");
    scanf("%d", &nota2);
    printf("insira a nota 3: \n");
    scanf("%d", &nota3);
    printf("insira a nota 4: \n");
    scanf("%d", &nota4);

    media = (nota1 + nota2 + nota3 + nota4)/4;

    printf("Media do Aluno: %.2f\n", media);

    if(media >= 7){
        printf("Aluno aprovado.");
    } else{
        printf("Aluno reprovado.");
    }

    return 0;
}