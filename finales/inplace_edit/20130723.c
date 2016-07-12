/* Escribir un programa ISO C que procese el archivo palabras.txt sobre sí 
 * mismo. El proceso consiste en duplicar las palabras que tengan más de 2 
 * consonantes.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "palabras.txt"
#define LARGO_MAX 20

bool es_vocal(char c) {
    bool vocal_mayus = c == 'A' || c == 'E' || c == 'I' || c == 'O' || 
        c == 'U'; 
    bool vocal_min = c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; 

    return vocal_mayus || vocal_min;
}

bool tiene_dos_consonantes(char *palabra) {
    int largo = strlen(palabra);
    int i;
    int consonantes = 0;
    for (i = 0; i < largo; ++i) {
        if (!es_vocal(palabra[i])) {++consonantes;}
        if (consonantes == 2) {return true;}
    }
    return false;
}

int leer_reversa(FILE *fp, int *seek) {
    fseek(fp, *seek, SEEK_SET);
    int c = fgetc(fp);
    if (*seek == 0) {
        *seek = -1;
    } else {
        fseek(fp, -2, SEEK_CUR);
        *seek = ftell(fp);
    }
    return c;
} 

void escribir_reversa(FILE *fp, char c, int *seek) {
    fseek(fp, *seek, SEEK_SET);
    fputc(c, fp);
    if (*seek == 0) {
        *seek = -1;
    } else {
        fseek(fp, -2, SEEK_CUR);
        *seek = ftell(fp);
    }
}

void escribir_palabra(FILE *fp, char *palabra, int *seek) {
    int largo = strlen(palabra);
    int i;
    for (i = 0; i < largo; ++i) {
        escribir_reversa(fp, palabra[i], seek);
    }
}

int main() {
    FILE *fp = fopen(FILE_NAME, "r");
    int c;
    int nuevo_largo = 0;
    int seek_escritura = 0;
    int seek_lectura = 0;
    char palabra[LARGO_MAX];
    memset(&palabra, 0, sizeof(char) * LARGO_MAX);
    int indice_palabra = 0;
    int largo_palabra;

    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            palabra[indice_palabra++] = c;
        } else {
            int mult = tiene_dos_consonantes(palabra) ? 2 : 1;
            largo_palabra = strlen(palabra);
            // El +1 es por el caracter no alfabetico
            nuevo_largo += largo_palabra * mult + 1; 
            printf("Palabra: %s, Largo: %d\n", palabra, nuevo_largo);
            memset(&palabra, 0, sizeof(char) * LARGO_MAX);
            indice_palabra = 0;
        }
    }
    printf("%d\n", nuevo_largo);

    memset(&palabra, 0, sizeof(char) * LARGO_MAX);
    indice_palabra = 0;
    ungetc(c, fp);
    seek_lectura = ftell(fp);
    fclose(fp);
    truncate(FILE_NAME, sizeof(char) * nuevo_largo);

    fp = fopen(FILE_NAME, "rb+");
    fseek(fp, 0, SEEK_END);
    seek_escritura = ftell(fp);

    while (seek_lectura >= 0) {
        c = leer_reversa(fp, &seek_lectura);
        if (isalpha(c)) {
            palabra[indice_palabra++] = c;
        } else {
            escribir_palabra(fp, palabra, &seek_escritura);
            if (tiene_dos_consonantes(palabra)) {escribir_palabra(fp, palabra, 
                    &seek_escritura);}
            escribir_reversa(fp, c, &seek_escritura);
            memset(&palabra, 0, sizeof(char) * LARGO_MAX);
            indice_palabra = 0;
        }

        if (isalpha(c) && seek_lectura < 0) {
            escribir_palabra(fp, palabra, &seek_escritura);
            if (tiene_dos_consonantes(palabra)) {escribir_palabra(fp, palabra,
                    &seek_escritura);}
        }
    }
    fclose(fp);
    return 0;
}
