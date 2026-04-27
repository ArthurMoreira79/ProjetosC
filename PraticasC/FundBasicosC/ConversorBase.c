#include <stdio.h>

int main(){

    int num;

    printf("Insira um numero decimal: \n");
    scanf("%d", &num);

    printf("O numero %d em binario eh: ", num);

    for(int i = 31; i >= 0; i--){
        int bit = (num >> i) & 1;

        printf("%d", bit);

        if(i % 8 == 0) printf(" "); 
    }

    return 0;
}