#include<stdlib.h>

typedef struct array {
    size_t size;
    size_t elements;
    int *data;
} array_t;

void array_init(array_t *self, size_t size);

void array_append(array_t *self, int value);

int array_find(array_t *self, int value);

void array_destroy(array_t *self);
