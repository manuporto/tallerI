#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define READ_SIZE 6
#define COUNT_ALPHA 4
#define FILE_NAME "a.bin"

bool is_sequence(char *buffer) {
    return isdigit(buffer[0]) && buffer[0] == buffer[1] && 
        isalpha(buffer[2]) && buffer[2] == buffer[3] && buffer[3] == buffer[4] && buffer[4] == buffer[5];
}

int main (int argc, char *argv[]) {
    FILE *fp = fopen(FILE_NAME, "rb+");
    char buffer[READ_SIZE];
    int writer = ftell(fp);
    int reader = writer;
    while (!feof(fp)) {
        fread(buffer, sizeof(char), READ_SIZE, fp);
        if (is_sequence(buffer)) {
           printf("%s\n", buffer);
	   reader = ftell(fp);
        } else {
            fseek(fp, writer, SEEK_SET);
            fwrite(buffer, sizeof(char), 1, fp);
            ++reader;
            writer = ftell(fp);
    	    fseek(fp, reader, SEEK_SET);
        }
    }
    char end[] =  "!";
    fwrite(end, sizeof(char), reader-writer, fp);
    fclose(fp);
}
