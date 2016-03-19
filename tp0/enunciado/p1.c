#include <stdio.h>

struct X
{
    short s; /* 2 bytes */
             /* 2 padding bytes */
    int   i; /* 4 bytes */
    char  c; /* 1 byte */
             /* 3 padding bytes */
};
int main() {
    char msg[] = "Hola mundo!";
    size_t a = sizeof(int);
    size_t b = sizeof(char);
    struct X i;
    //printf("Int: %zu Char: %zu\n", a, b);
    printf("%s\n", msg);
    return 0;    
}
