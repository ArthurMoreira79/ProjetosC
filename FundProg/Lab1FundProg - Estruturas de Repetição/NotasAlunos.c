#include <stdio.h>

int main(){
    float nota, totalAluno, mediaAluno, totalTurma, mediaTurma;

    for(int i=0; i<5; i++){
        printf("Aluno %d\n", i+1);
        for(int j=0; j<3; j++){
            printf("Insira o valor da nota %d: \n", j+1);
            scanf("%f", &nota);
            totalAluno += nota;
        }
        mediaAluno = totalAluno/3;
        totalTurma += mediaAluno;
    }
    mediaTurma = totalTurma/5;

    printf("A media da turma eh: %.2f", mediaTurma);
    return 0;
}