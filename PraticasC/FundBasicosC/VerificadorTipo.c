#include <stdio.h>

int main(){

    printf("--- Tamanos dos tipos de dados em C ---\n");

    printf("char: %u byte(s)\n", sizeof(char));
    printf("int: %u byte(s)\n", sizeof(int));
    printf("short int: %u byte(s)\n", sizeof(short int));
    printf("long int: %u byte(s)\n", sizeof(long int));
    printf("long long int: %u byte(s)\n", sizeof(long long int));
    printf("float: %u byte(s)\n", sizeof(float));
    printf("double: %u byte(s)\n", sizeof(double));
    printf("long double: %u byte(s)\n", sizeof(long double));
    printf("void* (ponto): %u byte(s)\n", sizeof(void*));

    return 0;
}