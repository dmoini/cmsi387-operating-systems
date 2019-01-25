#include <stdio.h>

int main() {
    int i = -10;
    char evenOrOdd[4];
    while (i <= 10) {    
        printf("%d\t%d\t", i, i * i);
        if (i % 2 == 0) {
            printf("EVEN\n");
        } else {
            printf("ODD\n");
        }     
        i += 1;
    }
    return 0;
}