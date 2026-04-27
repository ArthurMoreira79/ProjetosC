#include <Stdio.h>
#include <string.h>

#define MAX 100

typedef struct{
    char nome[100];
    int matricula;
    float notas[3];
    float mediaFinal;
} Aluno;

void calcularMedia(Aluno *aluno);
void cadastrarAlunos(Aluno *vetor, int *qtd, int max);
void listarAlunos(Aluno *vetor, int qtd);
Aluno* buscarAlunoPorMatricula(Aluno *vetor, int qtd, int mat);
void consultarAluno(Aluno *vetor, int qtd);
Aluno* alunoComMaiorMedia(Aluno *vetor, int qtd);
float calcularMediaGeral(Aluno *vetor, int qtd);
void exibirMenu();

int main(){
    Aluno turma[MAX];
    int quantidadeAlunos = 0;
    int opcao;

    do{
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                cadastrarAlunos(turma, &quantidadeAlunos, MAX);
                break;
            case 2:
                listarAlunos(turma, quantidadeAlunos);
                break;
             case 3:
                consultarAluno(turma, quantidadeAlunos);
                break;
            case 4: {
                Aluno *destaque = alunoComMaiorMedia(turma, quantidadeAlunos);
                if(destaque != NULL){
                    printf("\n--- Destaque Academico ---\n");
                    printf("Aluno: %s | Media: %.2f\n", destaque -> nome, destaque -> mediaFinal);
                } else{
                    printf("\nNenhum aluno cadastrado.\n");
                }
                break;
            }
            case 5:
                if (quantidadeAlunos > 0) {
                    printf("\nMedia Geral da Turma: %.2f\n", calcularMediaGeral(turma, quantidadeAlunos));
                } else {
                    printf("\nNenhum aluno para calcular media.\n");
                }
                break;
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }while(opcao != 6);

    return 0;
}

void exibirMenu() {
    printf("\n=== SISTEMA ACADEMICO IFMA ===\n");
    printf("1. Cadastrar alunos\n");
    printf("2. Listar todos os alunos\n");
    printf("3. Consultar aluno por matricula\n");
    printf("4. Mostrar aluno com maior media\n");
    printf("5. Calcular media geral da turma\n");
    printf("6. Sair\n");
    printf("==============================\n");
}

void calcularMedia(Aluno *aluno){
    float soma = 0;
    for(int i = 0; i < 3; i++){
        soma += aluno -> notas[i];
    }
    aluno -> mediaFinal = soma / 3.0;
}

void cadastrarAlunos(Aluno *vetor, int *qtd, int max){
    if (*qtd >= max) {
        printf("Capacidade maxima atingida!\n");
        return;
    }

    Aluno *novo = &vetor[*qtd];

    printf("Nome do aluno: ");
    fgets(novo -> nome, 100, stdin);
    novo -> nome[strcspn(novo -> nome, "\n")] = 0;

    printf("Matricula: ");
    scanf("%d", &novo -> matricula);

    for (int i = 0; i < 3; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &novo -> notas[i]);
    }

    calcularMedia(novo);
    (*qtd)++;
    printf("Aluno cadastrado com sucesso!\n");
}

void listarAlunos(Aluno *vetor, int qtd){
    printf("\n--- Lista de Alunos ---\n");
    for(int i = 0; i < qtd; i++){
        printf("Mat: %d | Nome: %-20s | Media: %.2f\n", 
                (vetor + i) -> matricula, (vetor + i) -> nome, (vetor + i) -> mediaFinal);
    }
}

Aluno* buscarAlunoPorMatricula(Aluno *vetor, int qtd, int mat) {
    for (int i = 0; i < qtd; i++) {
        if ((vetor + i) -> matricula == mat) {
            return (vetor + i);
        }
    }
    return NULL;
}

void consultarAluno(Aluno *vetor, int qtd) {
    int mat;
    printf("Digite a matricula para busca: ");
    scanf("%d", &mat);

    Aluno *res = buscarAlunoPorMatricula(vetor, qtd, mat);
    if (res != NULL) {
        printf("\nAluno Encontrado: %s | Media: %.2f\n", res -> nome, res -> mediaFinal);
    } else {
        printf("\nMatricula %d nao encontrada.\n", mat);
    }
}

Aluno* alunoComMaiorMedia(Aluno *vetor, int qtd) {
    if (qtd == 0) return NULL;
    
    Aluno *maior = vetor;
    for (int i = 1; i < qtd; i++) {
        if ((vetor + i) -> mediaFinal > maior -> mediaFinal) {
            maior = (vetor + i);
        }
    }
    return maior;
}

float calcularMediaGeral(Aluno *vetor, int qtd) {
    float somaTotal = 0;
    for (int i = 0; i < qtd; i++) {
        somaTotal += (vetor + i) -> mediaFinal;
    }
    return somaTotal / (float)qtd;
}