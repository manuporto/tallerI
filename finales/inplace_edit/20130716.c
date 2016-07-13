#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "enteros.dat"
#define NUM_SIZE 4

int leer (FILE *fp, int *seek) {
    fseek(fp, *seek, SEEK_SET);
    int c = fgetc(fp);
    *seek = ftell(fp);
    return c;
}

int escribir(FILE *fp, int *seek, int c) {
    fseek(fp, *seek, SEEK_SET);
    int out = fputc(c, fp);
    *seek = ftell(fp);
    return out;
}

void leer_numero(FILE *fp, int *seek, char numero[NUM_SIZE]) {
    int i = 0; 
    while (i < NUM_SIZE && (numero[i++] = leer(fp, seek)) != EOF);
}

void escribir_numero(FILE *fp, int *seek, char numero[NUM_SIZE]) {
    int i = 0;
    int largo = strlen(numero);
    while (i < largo && escribir(fp, seek, numero[i++]) != EOF);
}

void restar(char n1[NUM_SIZE], char n2[NUM_SIZE], char res[NUM_SIZE]) {
    int in1 = atoi(n1);
    int in2 = atoi(n2);
    int ires = in1 - in2;
    snprintf(res, sizeof(char) * NUM_SIZE, "%d", ires);
}
int main() {
    char n1[NUM_SIZE];
    char n2[NUM_SIZE];
    char res[NUM_SIZE];
    int largo_archivo = 0;
    FILE *fp = fopen(FILE_NAME, "rb+");
    int wr = ftell(fp);
    int rd = wr;
    while (feof(fp) == 0) {
        leer_numero(fp, &rd, n1);
        if (feof(fp) != 0) break;
        leer_numero(fp, &rd, n2);
        if (feof(fp) != 0) break;
        memset(&res, 0, sizeof(char) *NUM_SIZE);
        restar(n1, n2, res);
        escribir_numero(fp, &wr, res);
        largo_archivo += NUM_SIZE;
        if (feof(fp) != 0) break;
    }
    fclose(fp);
    truncate(FILE_NAME, largo_archivo);
    return 0;
}
