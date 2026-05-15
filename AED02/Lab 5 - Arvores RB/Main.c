#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ArvoreRB.h"

#define REPETICOES  10
#define N_PEQUENO   1000000
#define N_GRANDE    5000000

//Auxiliares

static double tempo_seg(void) {
    return (double)clock() / CLOCKS_PER_SEC;
}

static int* gera_lista(int n) {
    int *v = (int*) malloc(n * sizeof(int));
    if (!v) { perror("malloc"); exit(1); }
    for (int i = 0; i < n; i++)
        v[i] = rand();
    return v;
}
//Estrutura de Resultado de uma Rodada

typedef struct {
    double    t_total;
    double    t_fixup;
    long long n_rot_esq;
    long long n_rot_dir;
    long long n_recolor;
    long long n_rot_total;
    int       altura;
} ResultadoRB;

//Mede uma rodada completa

static ResultadoRB mede_rb(int *v, int n) {
    ResultadoRB r;

    reset_contadores_RB();

    ArvRB *arv = cria_ArvRB();
    double ini = tempo_seg();
    for (int i = 0; i < n; i++)
        insere_ArvRB(arv, v[i]);
    double fim = tempo_seg();

    r.t_total      = fim - ini;
    r.t_fixup      = tempo_fixup_RB;
    r.n_rot_esq    = cnt_rot_esq_RB;
    r.n_rot_dir    = cnt_rot_dir_RB;
    r.n_recolor    = cnt_recolor_RB;
    r.n_rot_total  = cnt_rot_esq_RB + cnt_rot_dir_RB;
    r.altura       = altura_ArvRB(arv);

    libera_ArvRB(arv);
    free(arv);
    return r;
}

//Stats

static double media_v(double *v, int n) {
    double s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return s / n;
}

static double dp_v(double *v, int n, double m) {
    double s = 0;
    for (int i = 0; i < n; i++) s += (v[i] - m) * (v[i] - m);
    return sqrt(s / (n - 1));
}

static double media_ll(long long *v, int n) {
    double s = 0;
    for (int i = 0; i < n; i++) s += (double)v[i];
    return s / n;
}

//Experimento

static void executa_experimento(int N, const char *rotulo) {

    double    t_total[REPETICOES], t_fixup[REPETICOES];
    long long n_re[REPETICOES], n_rd[REPETICOES];
    long long n_rc[REPETICOES], n_rtot[REPETICOES];
    int       h_rb[REPETICOES];

    printf("\n##########################################################\n");
    printf("  %s  (N=%d, %d repeticoes)\n", rotulo, N, REPETICOES);
    printf("##########################################################\n");

    //Cabeçalho – mesmo estilo da tabela AVL/BST
    printf("\n%-4s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-9s | %-6s\n",
           "Rep", "RB(s)", "Fixup(s)", "Rot.Esq", "Rot.Dir",
           "Recolor", "Total R", "Rot/Ins(%)", "H_RB");
    printf("-----|----------|----------|----------|----------|"
           "----------|----------|------------|--------\n");

    for (int r = 0; r < REPETICOES; r++) {
        int *lista  = gera_lista(N);
        ResultadoRB rb = mede_rb(lista, N);
        free(lista);

        t_total[r] = rb.t_total;
        t_fixup[r] = rb.t_fixup;
        n_re[r]    = rb.n_rot_esq;
        n_rd[r]    = rb.n_rot_dir;
        n_rc[r]    = rb.n_recolor;
        n_rtot[r]  = rb.n_rot_total;
        h_rb[r]    = rb.altura;

        double pct = (rb.t_total > 0)
                     ? 100.0 * rb.t_fixup / rb.t_total : 0.0;

    printf(" %3d | %8.4f | %8.6f | %8I64d | %8I64d | %8I64d | %8I64d | %9.2f%% | %6d\n",
       r + 1,
       rb.t_total, rb.t_fixup,
       rb.n_rot_esq, rb.n_rot_dir, rb.n_recolor, rb.n_rot_total,
       pct, rb.altura);
    }

    //Médias e DPs
    double m_total = media_v(t_total, REPETICOES);
    double m_fixup = media_v(t_fixup, REPETICOES);
    double dp_total = dp_v(t_total, REPETICOES, m_total);
    double dp_fixup = dp_v(t_fixup, REPETICOES, m_fixup);

    double m_re   = media_ll(n_re,   REPETICOES);
    double m_rd   = media_ll(n_rd,   REPETICOES);
    double m_rc   = media_ll(n_rc,   REPETICOES);
    double m_rtot = media_ll(n_rtot, REPETICOES);

    double soma_h = 0;
    for (int i = 0; i < REPETICOES; i++) soma_h += h_rb[i];
    double m_h = soma_h / REPETICOES;

    printf("-----|----------|----------|----------|----------|"
           "----------|----------|------------|--------\n");
    printf("Media| %8.4f | %8.6f | %8.0f | %8.0f | %8.0f | %8.0f |            | %6.1f\n",
           m_total, m_fixup, m_re, m_rd, m_rc, m_rtot, m_h);
    printf("DP   | %8.4f | %8.6f\n", dp_total, dp_fixup);

    /* Resumo de rotações */
    printf("\n--- Resumo de Rotacoes (medias por rodada) ---\n");
    printf("  Rotacoes esquerda     : %.0f\n",   m_re);
    printf("  Rotacoes direita      : %.0f\n",   m_rd);
    printf("  Recoloracoes          : %.0f\n",   m_rc);
    printf("  Total de rotacoes     : %.0f\n",   m_rtot);
    printf("  Rotacoes por insercao : %.4f\n",   m_rtot / N);
    printf("  Tempo medio fixup     : %.6f s (%.2f%% do tempo RB)\n",
           m_fixup, 100.0 * m_fixup / m_total);

    /* Alturas */
    printf("\n--- Alturas Finais da Arvore RB ---\n");
    printf("  Altura media RB       : %.1f\n", m_h);
    printf("  log2(N)               : %.1f  (altura otima)\n", log2((double)N));
    printf("  2*log2(N)             : %.1f  (limite maximo RB)\n", 2.0 * log2((double)N));
    printf("  Fator RB / log2(N)    : %.2f\n", m_h / log2((double)N));
}

//Main

int main(void) {
    srand((unsigned int) time(NULL));

    printf("==========================================================\n");
    printf("  Atividade VII: Arvore Red-Black - Insercao e Busca\n");
    printf("==========================================================\n");

    executa_experimento(N_PEQUENO, "1.000.000 elementos");
    executa_experimento(N_GRANDE,  "5.000.000 elementos");

    printf("\n==========================================================\n");
    printf("  Experimento Concluido\n");
    printf("==========================================================\n");

    return 0;
}