#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Insertion Sort

void insertionSort(int *A, int n){
    for(int i = 1; i < n; i++){
        int chave =A[i];
        int j = i -1;
        while(j >= 0 && A[j] > chave){
            j--;
        }
        A[j + 1] = chave;
    }
}

//Merge Sort

void merge(int *A, int p, int q, int r){
    int n1 = q - p + 1; //tamanho subvetor esq
    int n2 = r - q;     //tamanho subvetor dir

    //criaçãod os vetores auxiliares
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    //Copia os dados p os vetores auxiliares
    for(int i = 0; i < n1; i++){
        L[i] = A[p + i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = A[q + 1 + j];
    }

    //intercala os dois vets de volta em A[p..r]
    int i = 0, j = 0, k = p;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i++;
        } else{
            A[k] = R[j];
            j++;
        }
        k++;
    }

    //copia os elementos restantes de L e R (se houver)
    while(i < n1){
        A[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        A[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// função principal do Merge Sort (recursiva)

void mergeSort(int *A, int p, int r){
    if(p < r){
        int q = (p + r)/2;      //divide ao meio
        mergeSort(A, p, q);     //Conquista: ordena metade esq
        mergeSort(A, q + 1, r); //Conquista: Ordena metade dir
        merge(A, p, q, r);      //Combina os resultados
    }
}

//Funções auxiliares

void imprimeVet(int *A, int n){
    if(n > 20){
        printf("[Vetor Grande - Exibindo primeiros e ultimos 5 elementos]\n");
        printf("Inicio: ");
        for(int i = 0; i < 5; i++){
            printf("%d ", A[i]);
            printf("... Fim: ");
        }
        for(int i = n - 5; i < n; i++){
            printf("%d ", A[i]);
            printf("\n");
        }
    } else{
        for(int i = 0; i < n; i++){
            printf("%d ", A[i]);
            printf("\n");
        }
    }
}

void gerarVetRand(int *A, int n, unsigned int seed){
    srand(seed);
    for(int i = 0; i < n; i++){
        A[i] = rand() % 10000;
    }
}

double medeTempo(void (*sort_fn)(int *, int), int *A, int n){
    clock_t inicio = clock();
    sort_fn(A, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)/CLOCKS_PER_SEC) * 1000.0;
}

void mergeSortWrapper(int *A, int n){
    mergeSort(A, 0, n - 1);
}

//main

int main(){
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int numTestes = sizeof(tamanhos) / sizeof(tamanhos[0]);
    unsigned int seed = 42;

    printf("=======================================================\n");
    printf("   COMPARATIVO: Insertion Sort x Merge Sort\n");
    printf("=======================================================\n\n");

    int nDemo = 10;
    int demo[10];
    gerarVetRand(demo, nDemo, seed);

    printf("--- Demonstracao com vetor de %d elementos ---\n", nDemo);
    printf("Vetor original:\n");
    imprimeVet(demo, nDemo);

    int demoIns[10], demoMrg[10];
    memcpy(demoIns, demo, nDemo * sizeof(int));
    memcpy(demoMrg, demo, nDemo * sizeof(int));

    insertionSort(demoIns, nDemo);
    printf("Apos Insertion Sort:\n");
    imprimeVet(demoIns, nDemo);
 
    mergeSort(demoMrg, 0, nDemo - 1);
    printf("Apos Merge Sort:\n");
    imprimeVet(demoMrg, nDemo);
 
    printf("\n=======================================================\n");
    printf("%-12s | %-20s | %-20s\n", "Tamanho (n)", "Insertion Sort (ms)", "Merge Sort (ms)");
    printf("-------------------------------------------------------\n");

    for(int t = 0; t < numTestes; t++){
        int n = tamanhos[t];

        int *vetorOriginal = (int *)malloc(n * sizeof(int));
        int *vetorIns = (int *)malloc(n * sizeof(int));
        int *vetorMrg = (int *)malloc(n * sizeof(int));

        gerarVetRand(vetorOriginal, n, seed);
        memcpy(vetorIns, vetorOriginal, n * sizeof(int));
        memcpy(vetorMrg, vetorOriginal, n * sizeof(int));

        double tempoIns = medeTempo(insertionSort, vetorIns, n);
        double tempoMrg = medeTempo(mergeSortWrapper, vetorMrg, n);

        printf("%-12d | %-20.4f | %-20.4f\n", n, tempoIns, tempoMrg);

        free(vetorOriginal);
        free(vetorIns);
        free(vetorMrg);
    }

    return 0;
}