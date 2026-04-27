#include <stdio.h>

int main(){

    int time, jogador, jogadoresMenores18 = 0, jogadoresAcima80KG = 0;
    float somaAlturasGeral = 0, somaIdadesTime, idade, peso, altura;
    int totalTimes = 5, jogadoresPorTime = 4, totalJogadores = totalTimes * jogadoresPorTime;

    for (time = 1; time <= totalTimes; time++){
        somaIdadesTime = 0;
        printf("\n--- TIME %d ---\n", time);

        for(jogador = 1; jogador <= jogadoresPorTime; jogador++){
            printf("Jogador %d - Digite idade, peso e altura: ", jogador);
            scanf("%f %f %f", &idade, &peso, &altura);

            if(idade < 18){
                jogadoresMenores18++;
            }

            somaIdadesTime += idade;
            somaAlturasGeral += altura;

            if(peso > 80){
                jogadoresAcima80KG++;
            }
        }

        printf("Media de idade do time %d: %.2f\n", time, somaIdadesTime/jogadoresPorTime);
    }

    float mediaAlturaGeral = somaAlturasGeral/totalJogadores;
    float porcentagem80KG = ((float)jogadoresAcima80KG/totalJogadores) * 100;

    printf("\n========================================");
    printf("\nRELATORIO FINAL DO CAMPEONATO:");
    printf("\nJogadores menores de 18 anos: %d", jogadoresMenores18);
    printf("\nMedia de altura do campeonato: %.2f m", mediaAlturaGeral);
    printf("\nPorcentagem de jogadores > 80kg: %.2f%%\n", porcentagem80KG);
    printf("========================================\n");

    return 0;
}