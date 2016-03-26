#include<stdlib.h>

typedef struct array {
    size_t size;
    size_t elements;
    int *data;
} array_t;

void array_init(array_t *self, size_t size) {
    self->data = calloc(size, sizeof(int));
    self->size = size;
    self->elements = 0;
}

static void array_resize(array_t *self, size_t new_size) {
    int *new_data = realloc(self->data, sizeof(int) * new_size); 
    self->data = new_data;
    self->size = new_size;
}

void array_append(array_t *self, int value) {
    if (self->elements == self->size) {
        array_resize(self, self->size * 2);
    }
    self->data[self->elements] = value;
    self->elements++;
}

int array_find(array_t *self, int value) {
    for (int i = 0; i < self->elements; i++) {
        if (self->data[i] == value) {
            return i;
        }
    }

    return -1;
}
void array_destroy(array_t *self) {
    free(self->data);
}
