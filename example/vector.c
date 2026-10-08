#include <stdio.h>
#include <stdint.h>

#include "../include/vector.h"

int main(void) {
    Vector vec = vector_new();
    vector_print(&vec);
    printf("empty: %lu, pop on empty: %lu\n", vector_empty(&vec), vector_pop(&vec));

    for (uint64_t i = 0; i < 200; i++)
        vector_push(&vec, &i);
    printf("pushed 200, size: %lu, capacity: %lu\n", vector_size(&vec), vec.capacity);

    while (vector_size(&vec) > 3)
        vector_pop(&vec);
    vector_print(&vec);

    vector_insert(&vec, 0, 10);
    vector_insert(&vec, 2, 20);
    vector_insert(&vec, vector_size(&vec), 30);
    vector_insert(&vec, 99, 40);
    vector_print(&vec);

    vector_remove(&vec, 0);
    vector_remove(&vec, vector_size(&vec) - 1);
    vector_remove(&vec, 99);
    vector_print(&vec);

    vector_set(&vec, 1, 7);
    printf("get 1: %lu, get 99: %lu\n", vector_get(&vec, 1), vector_get(&vec, 99));

    vector_free(&vec);
    vector_print(&vec);

    return 0;
}
