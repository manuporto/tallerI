#include <stdio.h>
#include <stdlib.h>

enum estados {INIT, FAIL, ONE_D, TWO_D, ALPHA, FINISH}; 

int main(int argc, char *argv[]) {
    FILE *fp = fopen("a.bin", "r+");
    int rpos = ftell(fp);
    int wpos = rpos;
    int c, d, x, cant;
    int estado = INIT;
    while (!feof(fp)) {
        c = fgetc(fp);
        ++rpos;
        switch (estado) {
            case INIT:
                if (isdigit(c)){
                    d = c;
                    estado = ONE_D;
                } else estado = FAIL;
                break;
            case FAIL:
                fseek(fp, wpos, SEEK_SET);
                fputc(fp, c);
                wpos = ftell(fp);
                estado = INIT;
                break;
            case ONE_D:
                if (c == d){estado = TWO_D;}
                else estado = FAIL;
                break;
            case TWO_D:
                if (isalpha(c)){
                    x = c;
                    cant = 1;
                    estado = ALPHA;
                } else estado = FAIL;
                break;
            case ALPHA:
                if (c == x) ++cant;
                else estado = FAIL;
                if (cant == 4) estado = FINISH;
                break;
            case FINISH:
                // todo
                break;
        }
    }
    return 0;
}
