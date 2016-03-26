#include<stdlib.h>

typedef struct array {
    size_t size;
    size_t elements;
    int *data;
} array_t;

void array_init(array_t *self, size_t size) {
    self->data = malloc(sizeof(int) * size);
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
    self->data[self->elements + 1] = value;
    self->elements++;

}
void array_destroy(array_t *self) {
    free(self->data);
}
