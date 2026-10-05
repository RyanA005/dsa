#include <stdio.h>
#include <stdint.h>

#include "../include/vector.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <arg> <arg> ... \n", argv[0]);
        return 0;
    }

    Vector vec = vector_new();

    for (int i = 1; i < argc; i++) {
        uint64_t value = strtoull(argv[i], NULL, 10);
        printf("pushing %lu\n", value);
        vector_push(&vec, &value);
    }

    vector_print(&vec);

    while (!vector_empty(&vec)) {
        printf("popping %lu\n", vector_pop(&vec));
    }

    vector_free(&vec);

    return 0;
}
