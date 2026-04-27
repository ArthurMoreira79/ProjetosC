#include <stdio.h>
#include <math.h>

int main(){

    int opcao;
    double num1, num2, resultado;

    do{
        printf("\n--- MINI CALCULADORA CIENTIFICA ---\n");
        printf("1. Soma (x + y)\n");
        printf("2. Subtracao (x - y)\n");
        printf("3. Multiplicacao (x * y)\n");
        printf("4. Divisao (x / y)\n");
        printf("5. Potencia (x ^ y)\n");
        printf("6. Raiz Quadrada (sqrt)\n");
        printf("7. Logaritmo Natural (ln)\n");
        printf("8. Seno (radianos)\n");
        printf("0. Sair\n");
        printf("Escolha uma operacao: ");
        scanf("%d", &opcao);

        if(opcao == 0) break;

        switch(opcao){
            case 1:
                printf("Insira dois valores: \n");
                scanf("%lf", &num1);
                scanf("%lf", &num2);
                resultado = num1 + num2;
                printf("Resultado da Soma: %.2f\n", resultado);
                break;
            case 2:
                printf("Insira dois valores: \n");
                scanf("%lf", &num1);
                scanf("%lf", &num2);
                resultado = num1 - num2;
                printf("Resultado da Subtracao: %.2f\n", resultado);
                break;
            case 3:
                printf("Insira dois valores: \n");
                scanf("%lf", &num1);
                scanf("%lf", &num2);
                resultado = num1 * num2;
                printf("Resultado da Multiplicacao: %.2f\n", resultado);
                break;
            case 4:
                printf("Insira dois valores: \n");
                scanf("%lf", &num1);
                scanf("%lf", &num2);
                resultado = num1 / num2;
                printf("Resultado da Divisao: %.2f\n", resultado);
                break;
            case 5:
                printf("Insira a Base e o Expoente: \n");
                scanf("%lf", &num1);
                scanf("%lf", &num2);
                resultado = pow(num1, num2);
                printf("Resultado da Potenciacao: %.2f\n", resultado);
                break;
            case 6:
                printf("Insira um valor: \n");
                scanf("%lf", &num1);
                if(num1 >= 0){
                    resultado = sqrt(num1);
                    printf("Resultado da Radiciacao: %.2f\n", resultado);
                } else{
                    printf("Erro: Nao existe raiz de numero negativo no conjunto real.\n");
                }
                break;
            case 7:
                printf("Insira um valor: \n");
                scanf("%lf", &num1);
                if(num1 > 0){
                    resultado = log(num1);
                    printf("Logaritimo Natural de %f: %.2f\n", num1, resultado);
                } else{
                    printf("Erro: Logaritmo indefinido para zero ou negativos.\n");
                }
                break;
            case 8:
                printf("Insira o angulo em radianos: \n");
                scanf("%lf", &num1);
                resultado = sin(num1);
                printf("Seno do angulo %f: %.2f ", num1, resultado);
                break;
            default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    printf("Calculadora encerrada.\n");

    return 0;
}