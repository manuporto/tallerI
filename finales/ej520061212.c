#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "a.txt"

enum states {INIT, OP_PARENTHESIS, SLASH};

void write(FILE *fp, int c, size_t *index) {
    fputc(c, fp);
    *index = ftell(fp);
}

int main() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    int c;
    int state = INIT;
    size_t read_index = ftell(fp);
    size_t write_index = read_index;

    while((c = fgetc(fp)) != EOF) {
        read_index = ftell(fp);
        switch (state) {
            case INIT:
                if (c == '(') {
                    state = OP_PARENTHESIS;
                    write(fp, c, &write_index);
                } else if (c == '/') {
                    state = SLASH;
                } else {
                    write(fp, c, &write_index);
                }
                break;
            case OP_PARENTHESIS:
                if (c == ')') state = INIT;
                write(fp, c, &write_index);
                break;
            case SLASH:
                if (c == '/') {
                    fseek(fp, write_index, SEEK_SET);
                }
                else if (c == '(') state = OP_PARENTHESIS;
                else state = INIT;
                write(fp, c, &write_index);
                break;
        }
    }

    return 0;
}
