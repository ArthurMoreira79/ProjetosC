#include <stdio.h>

int comecaComA(char nomes[][21], int n);
int maioresQue6(char nomes[][21], int n);
void maisLongo(char nomes[][21], int n, char *destino);

int main() {
    char nomes[10][21]; 
    char maior[21];
    int i;

    printf("Digite os nomes de 10 sensores:\n");
    for (i = 0; i < 10; i++) {
        printf("Sensor %d: ", i + 1);
        scanf("%s", nomes[i]);
    }

    printf("\n--- Estatisticas dos Sensores ---\n");
    printf("Nomes que comecam com 'A': %d\n", comecaComA(nomes, 10));
    printf("Nomes com mais de 6 caracteres: %d\n", maioresQue6(nomes, 10));
    
    maisLongo(nomes, 10, maior);
    printf("O nome mais longo e: %s\n", maior);

    return 0;
}

int comecaComA(char nomes[][21], int n) {
    int cont = 0;
    for (int i = 0; i < n; i++) {
        if (*(*(nomes + i)) == 'A') {
            cont++;
        }
    }
    return cont;
}

int maioresQue6(char nomes[][21], int n) {
    int contGeral = 0;
    for (int i = 0; i < n; i++) {
        int tamanho = 0;
        char *p = *(nomes + i);
        
        while (*p != '\0') {
            tamanho++;
            p++;
        }
        
        if (tamanho > 6) {
            contGeral++;
        }
    }
    return contGeral;
}

void maisLongo(char nomes[][21], int n, char *destino) {
    int max = -1;
    char *origemMaior = NULL;

    for (int i = 0; i < n; i++) {
        int tamanho = 0;
        char *p = *(nomes + i);
        
        while (*p != '\0') {
            tamanho++;
            p++;
        }

        if (tamanho > max) {
            max = tamanho;
            origemMaior = *(nomes + i);
        }
    }

    if (origemMaior != NULL) {
        while (*origemMaior != '\0') {
            *destino = *origemMaior;
            destino++;
            origemMaior++;
        }
        *destino = '\0'; 
    }
}