#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define VECTOR_DEFAULT_CAPACITY 128ULL

/*

    vector_new ; return new vector
    vector_free ; delete vector

    vector_push ; add item to the end
    vector_pop ; remove item from the end

    vector_insert ; put item at index, shift latter right
    vector_remove ; remove item at index, shift latter left

    vector_get ; get item at index
    vector_set ; set item at index

    vector_size ; return vector size
    vector_empty ; return 1 if vector is empty

 */

typedef struct Vector {
    uint64_t *data;
    uint64_t size;
    uint64_t capacity;
} Vector;


Vector vector_new(void) {

    Vector vec = {
        .data = malloc(VECTOR_DEFAULT_CAPACITY * sizeof(uint64_t)),
        .size = 0ULL,
        .capacity = VECTOR_DEFAULT_CAPACITY,
    };

    return vec;
}

void vector_free(Vector *vec) {

    free(vec->data);
    vec->data = NULL;
    vec->size = 0ULL;
    vec->capacity = 0ULL;

    return;
}

static int vector_grow(Vector *vec) {
    uint64_t capacity = vec->capacity ? vec->capacity * 2ULL : VECTOR_DEFAULT_CAPACITY;
    uint64_t *data = realloc(vec->data, capacity * sizeof(uint64_t));
    if (data == NULL)
        return 0; // fail
    vec->data = data;
    vec->capacity = capacity;
    return 1;
}

void vector_push(Vector *vec, uint64_t *value) {
    if (vec->size >= vec->capacity && !vector_grow(vec))
        return; // fail
    vec->data[vec->size++] = *value;
    return;
}

uint64_t vector_pop(Vector *vec) {
    if (vec->size == 0ULL)
        return 0; // fail
    return vec->data[--vec->size];
}

void vector_insert(Vector *vec, uint64_t index, uint64_t value) {
    if (index > vec->size)
        return; // fail
    if (vec->size >= vec->capacity && !vector_grow(vec))
        return; // fail
    memmove(vec->data + index + 1, vec->data + index, (vec->size - index) * sizeof(uint64_t));
    vec->data[index] = value;
    vec->size++;
    return;
}

void vector_remove(Vector *vec, uint64_t index) {
    if (index >= vec->size)
        return; // fail
    memmove(vec->data + index, vec->data + index + 1, (vec->size - index - 1) * sizeof(uint64_t));
    vec->size--;
    return;
}

void vector_set(Vector *vec, uint64_t index, uint64_t value) {
    if (index >= vec->size)
        return; // fail
    vec->data[index] = value;
    return;
}

uint64_t vector_get(Vector *vec, uint64_t index) {
    if (index >= vec->size)
        return 0; // fail
    return vec->data[index];
}

uint64_t vector_size(Vector *vec) {
    return vec->size;
}

uint64_t vector_empty(Vector *vec) {
    return (vec->size == 0ULL);
}

void vector_print(Vector* vector) {
    if (!vector->size) {
        printf("(empty)\n");
        return;
    }

    for (uint64_t i = 0; i < vector->size - 1; i++) {
        printf("%lu, ", vector->data[i]);
    }
    printf("%lu\n", vector->data[vector->size - 1]);

    return;
}
