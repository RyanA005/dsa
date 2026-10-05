#include <stdio.h>

#include "linkedlist.h"
#include "hashmap.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: ./%s <arg> <arg> ... \n", argv[0]);
        return 0;
    }

    Hashmap map;
    hashmap_init(&map, 10);

    for (int i = 1; i < argc; i++) {
        Pair pair = { .data = i, .key = argv[i]};
        hashmap_pair_print(hashmap_put(&map, &pair));
    }

    hashmap_pair_print(hashmap_get(&map, "key1"));

    return 0;
}
