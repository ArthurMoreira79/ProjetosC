#include <stdio.h>

void saudar(char nome[]){
    printf("Ola, %s!\n", nome);
}

int main(){

    saudar("Mundo"); //chamando a função com uma string direta.

    char meuNome[] = "Arthur"; //chamando a função usando uma variavel.
    saudar(meuNome);

    return 0;
}