#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *A, int n){
    for(int j = 1; j < n; j++){
        int key = A[j];
        int i = j - 1;

        while(i >= 0 && A[i] > key){
            A[i + 1] = A[i];
            i = i - 1;
        }

        A[i + 1] = key;
    }
}

void preencherAleatorio(int *A, int n){
    for(int i = 0; i < n; i++){
        A[i] = rand() % 1000000;
    }
}

int estaOrdenado(int *A, int n){
    for(int i = 0; i < n - 1; i++){
        if(A[i] > A[i + 1]) return 0;
    }
    return 1;
}

void teste(int n){
    printf("--------------------------------------------------\n");
    printf("Tamanho do vetor: n = %d\n", n);

    int *A = (int *)malloc(n * sizeof(int));
    if(!A){
        printf("Erro: memoria insuficiente para n = %d\n", n);
        return;
    }

    preencherAleatorio(A, n);

    clock_t inicio = clock();
    insertionSort(A, n);
    clock_t fim = clock();

    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    
    if (estaOrdenado(A, n)) {
    printf("Ordenado corretamente: SIM\n");
    } else {
    printf("Ordenado corretamente: NAO\n");
    }
    printf("Tempo de execucao: %.4f segundos\n", tempo);

    free(A);
}

int main(){
    srand(42);

    printf("==================================================\n");
    printf("  Analise do Insertion Sort - Atividade I\n");
    printf("==================================================\n\n");

    teste(10000000);

    printf("--------------------------------------------------\n");
    printf("\nNota: n = 10.000.000 pode levar muitos minutos,\n");
    printf("pois Insertion Sort eh O(n^2) no caso medio/pior.\n");
 
    return 0;
}



