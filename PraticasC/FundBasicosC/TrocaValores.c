#include <stdio.h>

int main(){

    int x, y;

    printf("insira um valor para x: \n");
    scanf("%d", &x);
    printf("insira um valor para y: \n");
    scanf("%d", &y);

    x = x + y;
    y = x - y;
    x = x - y;

    printf("valores alternados: X:%d, Y:%d\n", x, y);
    
    return 0;
}