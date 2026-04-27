#include <stdio.h>
#include <math.h>

int main(){

    float a, b, c, delta, x1, x2;

    printf("Insira os valores de a, b e c: \n");
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);

    if(a == 0){
        printf("Se 'a' = 0, a equacao nao eh do segundo grau.\n");
    } else{
        delta = pow(b, 2) - (4 * a * c);
        printf("Delta = %.2f\n", delta);

        if(delta < 0){
            printf("A equacao nao possui raizes reais.\n");
        } else if(delta == 0){
            x1 = -b / (2 * a);
            printf("A equacao possui somente uma raiz real: X = %.2f\n", x1);
        } else{
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            printf("As raizes sao: X1:%.2f e X2:%.2f\n", x1, x2);
        }
    }

    return 0;
}