#include <stdio.h>
#include <stdbool.h>

bool ehPrimo(int n){
    if(n < 2) return false;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

int inverterNumero(int n){
    int invertido = 0;
    while (n > 0){
        invertido = invertido * 10 + (n % 10);
        n /= 10;
    }
    return invertido;
}

int main(){
    printf("Primos que tambem sao primos quando invertidos (1 - 1000):\n");
    printf("--------------------------------------------------------\n");

    for(int i = 1; i <= 1000; i++){
        if(ehPrimo(i)){
            int invertido = inverterNumero(i);

            if(ehPrimo(invertido)){
                printf("%d ", i);
            }
        }
    }

    printf("--------------------------------------------------------\n");
    return 0;
}