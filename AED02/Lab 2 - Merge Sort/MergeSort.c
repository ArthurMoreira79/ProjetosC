#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Merge - Combina dois subvetores ordenados

void merge(int *A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { A[k] = L[i]; i++; k++; }
    while (j < n2) { A[k] = R[j]; j++; k++; }

    free(L);
    free(R);
}

// Merge Sort - Função recursiva principal

void mergeSort(int *A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

//main

int main() {
    int n = 1000000;

    printf("==============================================\n");
    printf("         Merge Sort - %d elementos\n", n);
    printf("==============================================\n\n");

    // Aloca e preenche o vetor com números aleatórios
    int *vetor = (int *)malloc(n * sizeof(int));
    if (!vetor) {
        printf("Erro: memoria insuficiente!\n");
        return 1;
    }

    srand(42);
    for (int i = 0; i < n; i++)
        vetor[i] = rand() % 1000000;

    // Exibe os primeiros 10 elementos antes
    printf("Primeiros 10 elementos ANTES da ordenacao:\n");
    for (int i = 0; i < 10; i++) printf("%7d ", vetor[i]);
    printf("\n\n");

    // Mede o tempo de execução
    clock_t inicio = clock();
    mergeSort(vetor, 0, n - 1);
    clock_t fim = clock();

    double tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;

    // Exibe os primeiros 10 elementos depois
    printf("Primeiros 10 elementos DEPOIS da ordenacao:\n");
    for (int i = 0; i < 10; i++) printf("%7d ", vetor[i]);
    printf("\n\n");

    // Verifica se o vetor está realmente ordenado
    int ordenado = 1;
    for (int i = 0; i < n - 1; i++) {
        if (vetor[i] > vetor[i + 1]) {
            ordenado = 0;
            break;
        }
    }

    printf("Vetor ordenado corretamente? %s\n", ordenado ? "Sim" : "Nao");
    printf("Tempo de execucao: %.2f ms (%.4f segundos)\n", tempo_ms, tempo_ms / 1000.0);
    printf("\n");

    free(vetor);
    return 0;
}