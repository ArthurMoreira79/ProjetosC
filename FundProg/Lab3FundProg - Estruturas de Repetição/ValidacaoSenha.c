#include <stdio.h>
#include <string.h>

int main(){

    int senhaCorreta = 1234;
    int tentativa;
    int chances = 3;

    while(chances > 0){
        printf("\nDigite a senha(%d tentativas restantes): ", chances);
        fflush(stdout);
        scanf("%d", &tentativa);

        if(tentativa == senhaCorreta){
            printf("Acesso permitido! Bem vindo.\n");
            break;
        } else{
            chances--;
            if(chances > 0){
                printf("Senha incorreta!");
            } else{
                printf("Acesso bloqueado! Voce excedeu o limite de tentativas.\n");
            }
        }
    }

    return 0;
}