#include <stdio.h>

int main(){

    double base;
    int expoente;
    double resultado = 1.0;

    printf("Insira a base(x): ");
    scanf("%lf", &base);
    printf("Insira o expoente(n): ");
    scanf("%d", &expoente);

    if(expoente < 0){
        printf("Este progrma suporta apenas expoentes positivos.\n");
    } else{
        for(int i = 0; i < expoente; i++){
            resultado *= base;
        }
        printf("%.3f elevado a %d eh: %.2f\n", base, expoente, resultado);
    }

    return 0;
}