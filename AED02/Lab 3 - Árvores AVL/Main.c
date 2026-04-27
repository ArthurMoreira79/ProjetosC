//Comparação BST vs AVL
//Gera N valores aleatórios UMA vez (mesma lista para ambas)
//Repete o experimento REPETICOES vezes com listas distintas
//Mede o tempo de inserção de cada estrutura em cada rodada
//Aplica o Teste-t Pareado para verificar significado
//Compilação: cd "Lab 3 - Árvores AVL" gcc -O0 -o benchmark main.c ArvoreAVL.c ArvoreBST.c -lm
//Execução:  ./benchmark

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ArvoreAVL.h"
#include "ArvoreBST.h"

//Parâmetros do experimento
#define REPETICOES   10      // amostras para o teste-t (>= 30 recomendado)
#define N_PEQUENO    1000000 // 1 milhão de elementos 
#define N_GRANDE     5000000 // 5 milhões de elementos

//Utilitários de tempo
static double tempo_seg() {
    return(double)clock() / CLOCKS_PER_SEC;
}

//Geração da lista aleatória
static int* gera_lista(int n) {
    int *v = (int*) malloc(n * sizeof(int));
    if (!v) { perror("malloc"); exit(1); }
    for (int i = 0; i < n; i++)
        v[i] = rand();
    return v;
}

//Mede inserção BST
static double mede_bst(int *v, int n) {
    ArvBST *arv = cria_ArvBST();
    double ini = tempo_seg();
    for (int i = 0; i < n; i++)
        insere_ArvBST(arv, v[i]);
    double fim = tempo_seg();
    libera_ArvBST(arv);
    free(arv);
    return fim - ini;
}

//Mede inserção AVL
static double mede_avl(int *v, int n) {
    ArvAVL *arv = cria_ArvAVL();
    double ini = tempo_seg();
    for (int i = 0; i < n; i++)
        insere_ArvAVL(arv, v[i]);
    double fim = tempo_seg();
    libera_ArvAVL(arv);
    free(arv);
    return fim - ini;
}

//Estatísticas
static double media(double *v, int n) {
    double s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return s / n;
}

static double desvio_padrao(double *v, int n, double m) {
    double s = 0;
    for (int i = 0; i < n; i++) s += (v[i] - m) * (v[i] - m);
    return sqrt(s / (n - 1));
}

// Teste-t pareado (Bicaudal)
static double teste_t_pareado(double *bst, double *avl, int n,
                               double *media_d, double *dp_d) {
    double *d = (double*) malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        d[i] = bst[i] - avl[i];

    *media_d = media(d, n);
    *dp_d    = desvio_padrao(d, n, *media_d);

    double t = (*media_d) / (*dp_d / sqrt((double)n));
    free(d);
    return t;
}

// Experimento completo
static void executa_experimento(int N, const char *rotulo) {
    double t_bst[REPETICOES];
    double t_avl[REPETICOES];

    printf("\n==========================================================\n");
    printf("  Experimento: %s  (N = %d, %d repeticoes)\n", rotulo, N, REPETICOES);
    printf("==========================================================\n");
    printf(" Rep  |   BST (s)   |   AVL (s)   | Diferença (s)\n");
    printf("------|-------------|-------------|---------------\n");

    for (int r = 0; r < REPETICOES; r++) {
        int *lista = gera_lista(N);
        t_bst[r] = mede_bst(lista, N);
        t_avl[r] = mede_avl(lista, N);
        printf("  %3d |  %9.4f  |  %9.4f  |  %+9.4f\n",
               r + 1, t_bst[r], t_avl[r], t_bst[r] - t_avl[r]);
        free(lista);
    }

    double m_bst = media(t_bst, REPETICOES);
    double m_avl = media(t_avl, REPETICOES);
    double dp_bst = desvio_padrao(t_bst, REPETICOES, m_bst);
    double dp_avl = desvio_padrao(t_avl, REPETICOES, m_avl);

    double media_d, dp_d;
    double t_stat = teste_t_pareado(t_bst, t_avl, REPETICOES, &media_d, &dp_d);

    printf("------|-------------|-------------|---------------\n");
    printf("Media |  %9.4f  |  %9.4f  |\n", m_bst, m_avl);
    printf("DP    |  %9.4f  |  %9.4f  |\n", dp_bst, dp_avl);

    printf("\n--- Teste-t Pareado ---\n");
    printf("  Media das diferencas  : %.6f s\n", media_d);
    printf("  DP das diferencas     : %.6f s\n", dp_d);
    printf("  Estatistica t         : %.4f\n", t_stat);
    printf("  Graus de liberdade    : %d\n", REPETICOES - 1);
    printf("  Valor critico (5%%, gl=%d): ~2.045\n", REPETICOES - 1);
    printf("  Valor critico (1%%, gl=%d): ~2.756\n", REPETICOES - 1);

    double t_abs = fabs(t_stat);
    if (t_abs > 2.756)
        printf("  Conclusao: DIFERENCA SIGNIFICATIVA (p < 0.01) - AVL %s que BST\n",
               media_d > 0 ? "mais rapida" : "mais lenta");
    else if (t_abs > 2.045)
        printf("  Conclusao: DIFERENCA SIGNIFICATIVA (p < 0.05) - AVL %s que BST\n",
               media_d > 0 ? "mais rapida" : "mais lenta");
    else
        printf("  Conclusao: Sem diferenca significativa (p >= 0.05)\n");
}

//Main
int main(void) {
    srand((unsigned int) time(NULL));

    printf("====================================\n");
    printf("Comparacao de Desempenho: Arvore Binaria vs AVL\n");
    printf("====================================\n");

    executa_experimento(N_PEQUENO, "1.000.000 elementos");
    executa_experimento(N_GRANDE,  "5.000.000 elementos");

    printf("\n====================================\n");
    printf("    Experimento Concluido\n");
    printf("====================================\n");

    return 0;
}