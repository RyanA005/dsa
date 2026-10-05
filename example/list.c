#include <stdio.h>
#include <stdint.h>

#include "../include/list.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <arg> <arg> ... \n", argv[0]);
        return 0;
    }

    List list = list_new();

    for (int i = 1; i < argc; i++) {
        uint64_t value = strtoull(argv[i], NULL, 10);
        printf("pushing %llu\n", (unsigned long long)value);
        list_push_tail(&list, &value);
    }

    list_print(&list);

    while (!list_empty(&list)) {
        printf("popping %llu\n", (unsigned long long)list_pop_tail(&list));
    }

    list_free(&list);

    return 0;
}
