#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define FILE_NAME "a.txt"

enum states {INIT, OP_PARENTHESIS, SLASH};

int read_char(FILE *fp, size_t *index) {
    fseek(fp, *index, SEEK_SET);
    int c = fgetc(fp);
    *index = ftell(fp);
    return c;
}

void write_char(FILE *fp, int c, size_t *index) {
    fseek(fp, *index, SEEK_SET);
    fputc(c, fp);
    *index = ftell(fp);
}

int main() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    int c;
    int file_length = 0;
    int state = INIT;
    size_t read_index = ftell(fp);
    size_t write_index = read_index;

    while((c = read_char(fp, &read_index)) != EOF) {
        printf("rd: %zu, w: %zu\n", read_index, write_index);
        ++file_length;
        switch (state) {
            case INIT:
                if (c == '/') {
                    state = SLASH;
                } else {
                    write_char(fp, c, &write_index);
                    if (c == '(') state = OP_PARENTHESIS;
                }
                break;
            case OP_PARENTHESIS:
                if (c == ')') {state = INIT;}
                write_char(fp, c, &write_index);
                break;
            case SLASH:
                if (c == '/') {
                    --file_length;
                    write_char(fp, '*', &write_index);
                    state = INIT; 
                } else{
                    state = c == '(' ? OP_PARENTHESIS : INIT;
                    write_char(fp, '/', &write_index);
                    write_char(fp, c, &write_index);
                }
                break;
        }
    }

    fclose(fp);
    truncate(FILE_NAME, file_length);
    return 0;
}
