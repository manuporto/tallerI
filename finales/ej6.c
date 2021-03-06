#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int val(char c) {
    if (c >= '0' && c <= '9') {
        return (int)c - '0';
    }
    return (int)c - 'A' + 10;
}

int main(int argc, char *argv[]) {
    int base = atoi(argv[2]);
    printf("El numero es %s y su base es %d\n", argv[1], base);
    int len = strlen(argv[1]);
    int power = 1;
    int num = 0;
    int i;
    for (i = len - 1; i >= 0; i--) {
        num += val(argv[1][i]) * power;
        power *= base;
    }
    printf("El numero en base decimal es: %d\n", num);
}
