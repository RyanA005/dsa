#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEY_SIZE 8

typedef struct Pair {
    int data;
    char *key;
} Pair;

typedef struct Hashmap {
    int size;
    Pair *pairs;
} Hashmap;

int hash(Hashmap *map, char *key) {
    int sum = 0;
    for (int i = 0; i < MAX_KEY_SIZE && key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % map->size;
}

void hashmap_init(Hashmap *map, int size) {
    map->size = size;
    map->pairs = malloc(sizeof(Pair) * size);
    return;
}

Pair *hashmap_put(Hashmap *map, Pair *pair) {
    int id = hash(map, pair->key);
    map->pairs[id] = *pair;
    return &(map->pairs[id]);
}

Pair *hashmap_get(Hashmap *map, char *key) {
    int id = hash(map, key);
    return &(map->pairs[id]);
}

void hashmap_pair_print(Pair *pair) {
    printf("\"%s\" => %d\n", pair->key, pair->data);
    return;
}
