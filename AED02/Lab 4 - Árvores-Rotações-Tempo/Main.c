#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ArvoreAVL.h"
#include "ArvoreBST.h"

// Parametros
#define REPETICOES  10
#define N_PEQUENO   1000000
#define N_GRANDE    5000000

//Tempo geral (insercao total)
static double tempo_seg() {
    return (double)clock() / CLOCKS_PER_SEC;
}

//Gera lista aleatoria
static int* gera_lista(int n) {
    int *v = (int*) malloc(n * sizeof(int));
    if (!v) { perror("malloc"); exit(1); }
    for (int i = 0; i < n; i++)
        v[i] = rand();
    return v;
}

//Estrutura para guardar os resultados de uma rodada
typedef struct {
    double t_total;       // tempo total de insercao AVL
    double t_rotacoes;    // tempo gasto so nas rotacoes 
    long long n_LL;
    long long n_RR;
    long long n_LR;
    long long n_RL;
    long long n_total;
    int altura_avl;
} ResultadoAVL;

typedef struct {
    double t_total;
    int    altura_bst;
} ResultadoBST;

//Mede uma rodada completa de inserção
static ResultadoAVL mede_avl(int *v, int n) {
    ResultadoAVL r;

    reset_contadores_AVL();          // zera contadores e tempo de rotacoes 

    ArvAVL *arv = cria_ArvAVL();
    double ini  = tempo_seg();
    for (int i = 0; i < n; i++)
        insere_ArvAVL(arv, v[i]);
    double fim  = tempo_seg();

    r.t_total    = fim - ini;
    r.t_rotacoes = tempo_rotacoes;   // acumulado dentro das funcoes de rotacao 
    r.n_LL       = cnt_LL;
    r.n_RR       = cnt_RR;
    r.n_LR       = cnt_LR;
    r.n_RL       = cnt_RL;
    r.n_total    = cnt_LL + cnt_RR + cnt_LR + cnt_RL;
    r.altura_avl = altura_ArvAVL(arv);

    libera_ArvAVL(arv);
    free(arv);
    return r;
}

static ResultadoBST mede_bst(int *v, int n) {
    ResultadoBST r;

    ArvBST *arv = cria_ArvBST();
    double ini  = tempo_seg();
    for (int i = 0; i < n; i++)
        insere_ArvBST(arv, v[i]);
    double fim  = tempo_seg();

    r.t_total   = fim - ini;
    r.altura_bst = altura_ArvBST(arv);

    libera_ArvBST(arv);
    free(arv);
    return r;
}

//Estatisticas
static double media_v(double *v, int n) {
    double s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return s / n;
}

static double dp_v(double *v, int n, double m) {
    double s = 0;
    for (int i = 0; i < n; i++) s += (v[i]-m)*(v[i]-m);
    return sqrt(s / (n-1));
}

static double media_ll(long long *v, int n) {
    double s = 0;
    for (int i = 0; i < n; i++) s += (double)v[i];
    return s / n;
}

static double teste_t(double *bst, double *avl, int n,
                      double *med_d, double *dp_d) {
    double *d = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) d[i] = bst[i] - avl[i];
    *med_d = media_v(d, n);
    *dp_d  = dp_v(d, n, *med_d);
    double t = (*med_d) / (*dp_d / sqrt((double)n));
    free(d);
    return t;
}

//Experimento completo
static void executa_experimento(int N, const char *rotulo) {

    double    t_bst[REPETICOES], t_avl[REPETICOES], t_rot[REPETICOES];
    long long nLL[REPETICOES], nRR[REPETICOES];
    long long nLR[REPETICOES], nRL[REPETICOES], ntot[REPETICOES];
    int       h_avl[REPETICOES], h_bst[REPETICOES];

    printf("\n##########################################################\n");
    printf("  %s  (N=%d, %d repeticoes)\n", rotulo, N, REPETICOES);
    printf("##########################################################\n");

    //Cabecalho da tabela principal
    printf("\n%-4s | %-8s | %-8s | %-8s | %-6s | %-6s | %-6s | %-6s | %-8s | %-8s | %-6s | %-6s\n",
           "Rep","BST(s)","AVL(s)","Rot(s)","LL","RR","LR","RL","Total R","Rot/Ins(%)","H_AVL","H_BST");
    printf("-----|----------|----------|----------|--------|--------|--------|--------|----------|------------|--------|--------\n");

    for (int r = 0; r < REPETICOES; r++) {
        int *lista      = gera_lista(N);
        ResultadoBST rb = mede_bst(lista, N);
        ResultadoAVL ra = mede_avl(lista, N);
        free(lista);

        t_bst[r] = rb.t_total;
        t_avl[r] = ra.t_total;
        t_rot[r] = ra.t_rotacoes;
        nLL[r]   = ra.n_LL;
        nRR[r]   = ra.n_RR;
        nLR[r]   = ra.n_LR;
        nRL[r]   = ra.n_RL;
        ntot[r]  = ra.n_total;
        h_avl[r] = ra.altura_avl;
        h_bst[r] = rb.altura_bst;

        double pct = (ra.t_total > 0)
                     ? 100.0 * ra.t_rotacoes / ra.t_total : 0.0;

        printf(" %3d | %8.4f | %8.4f | %8.6f | %6I64d | %6I64d | %6I64d | %6I64d | %8I64d | %9.2f%% | %6d | %6d\n",
            r+1,
            rb.t_total, ra.t_total, ra.t_rotacoes,
            ra.n_LL, ra.n_RR, ra.n_LR, ra.n_RL,
            ra.n_total, pct,
            ra.altura_avl, rb.altura_bst);
    }

    //Medias e DPs
    double m_bst  = media_v(t_bst, REPETICOES);
    double m_avl  = media_v(t_avl, REPETICOES);
    double m_rot  = media_v(t_rot, REPETICOES);
    double dp_bst = dp_v(t_bst, REPETICOES, m_bst);
    double dp_avl = dp_v(t_avl, REPETICOES, m_avl);
    double dp_rot = dp_v(t_rot, REPETICOES, m_rot);

    double m_LL  = media_ll(nLL,  REPETICOES);
    double m_RR  = media_ll(nRR,  REPETICOES);
    double m_LR  = media_ll(nLR,  REPETICOES);
    double m_RL  = media_ll(nRL,  REPETICOES);
    double m_tot = media_ll(ntot, REPETICOES);

    // Media das alturas
    double soma_havl = 0, soma_hbst = 0;
    for (int i = 0; i < REPETICOES; i++) { soma_havl += h_avl[i]; soma_hbst += h_bst[i]; }
    double m_havl = soma_havl / REPETICOES;
    double m_hbst = soma_hbst / REPETICOES;

    printf("-----|----------|----------|----------|--------|--------|--------|--------|----------|------------|--------|--------\n");
    printf("Media| %8.4f | %8.4f | %8.6f | %6.0f | %6.0f | %6.0f | %6.0f | %8.0f |            | %6.1f | %6.1f\n",
           m_bst, m_avl, m_rot, m_LL, m_RR, m_LR, m_RL, m_tot, m_havl, m_hbst);
    printf("DP   | %8.4f | %8.4f | %8.6f\n", dp_bst, dp_avl, dp_rot);

    //Teste-t Pareado
    double med_d, dp_d;
    double t_stat = teste_t(t_bst, t_avl, REPETICOES, &med_d, &dp_d);
    double t_abs  = (t_stat < 0) ? -t_stat : t_stat;

    printf("\n--- Teste-t Pareado (BST vs AVL - tempo total de insercao) ---\n");
    printf("  Media das diferencas  : %+.6f s\n", med_d);
    printf("  DP das diferencas     : %.6f s\n",  dp_d);
    printf("  Estatistica t         : %.4f\n",     t_stat);
    printf("  Graus de liberdade    : %d\n",        REPETICOES - 1);
    printf("  Valor critico 5%%      : ~2.262 (gl=%d)\n", REPETICOES-1);
    printf("  Valor critico 1%%      : ~3.250 (gl=%d)\n", REPETICOES-1);

    if (t_abs > 3.250)
        printf("  Conclusao: DIFERENCA SIGNIFICATIVA (p < 0.01) - AVL %s que BST\n",
               med_d > 0 ? "mais rapida" : "mais lenta");
    else if (t_abs > 2.262)
        printf("  Conclusao: DIFERENCA SIGNIFICATIVA (p < 0.05) - AVL %s que BST\n",
               med_d > 0 ? "mais rapida" : "mais lenta");
    else
        printf("  Conclusao: Sem diferenca significativa (p >= 0.05)\n");

    //Resumo de rotacoes
    printf("\n--- Resumo de Rotacoes (medias por rodada) ---\n");
    printf("  LL (simples direita)  : %.0f\n",   m_LL);
    printf("  RR (simples esquerda) : %.0f\n",   m_RR);
    printf("  LR (dupla direita)    : %.0f\n",   m_LR);
    printf("  RL (dupla esquerda)   : %.0f\n",   m_RL);
    printf("  Total de rotacoes     : %.0f\n",   m_tot);
    printf("  Rotacoes por insercao : %.4f\n",   m_tot / N);
    printf("  Tempo medio rotacoes  : %.6f s (%.2f%% do tempo AVL)\n",
           m_rot, 100.0 * m_rot / m_avl);

    //Alturas Finais
    printf("\n--- Alturas Finais das Arvores ---\n");
    printf("  Altura media AVL      : %.1f\n", m_havl);
    printf("  Altura media BST      : %.1f\n", m_hbst);
    printf("  log2(N)               : %.1f  (altura otima)\n", log2((double)N));
    printf("  Fator AVL / log2(N)   : %.2f\n", m_havl / log2((double)N));
    printf("  Fator BST / log2(N)   : %.2f\n", m_hbst / log2((double)N));
}

//Main
int main(void) {
    srand((unsigned int) time(NULL));

    printf("==========================================================\n");
    printf("  Atividade IV: Instrumentacao de Rotacoes AVL\n");
    printf("  Algoritmos e Estrutura de Dados II\n");
    printf("==========================================================\n");

    executa_experimento(N_PEQUENO, "1.000.000 elementos");
    executa_experimento(N_GRANDE,  "5.000.000 elementos");

    printf("\n==========================================================\n");
    printf("  Experimento Concluido\n");
    printf("==========================================================\n");

    return 0;
}