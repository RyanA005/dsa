#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAP_DEFAULT_CAPACITY 128ULL

/*

    map_new ; return new map
    map_free ; delete map
    
    map_get ; get item from map, NULL if missing
    map_set ; set item in map, overwrite if key exists
    map_remove ; remove item from map

    map_size ; return number of items
    map_empty ; return 1 if map is empty

 */

typedef struct Pair {
    char *key;
    uint64_t data;
    struct Pair *next;
} Pair;

typedef struct Map {
    Pair **data;
    uint64_t size;
    uint64_t capacity;
} Map;

static uint64_t map_hash(const char *s) {

    /* https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function */

    uint64_t hash = 14695981039346656037ULL;

    while (*s) {
        hash ^= (unsigned char)*s++;
        hash *= 1099511628211ULL;
    }

    return hash;
}

static char *map_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (!copy)
        return NULL; // fail

    memcpy(copy, s, len);
    return copy;
}

static int map_resize(Map *map, uint64_t capacity) {

    Pair **data = calloc(capacity, sizeof(Pair *));
    if (!data)
        return 0; // fail

    for (uint64_t i = 0; i < map->capacity; i++) {
        Pair *p = map->data[i];
        while (p) {
            Pair *next = p->next;
            uint64_t id = map_hash(p->key) % capacity;
            p->next = data[id];
            data[id] = p;
            p = next;
        }
    }

    free(map->data);
    map->data = data;
    map->capacity = capacity;
    return 1;
}

Map map_new(void) {

    Map map = {
        .data = calloc(MAP_DEFAULT_CAPACITY, sizeof(Pair *)),
        .size = 0ULL,
        .capacity = MAP_DEFAULT_CAPACITY
    };
    if (!map.data)
        map.capacity = 0ULL;

    return map;
}

void map_free(Map *map) {

    for (uint64_t i = 0; i < map->capacity; i++) {
        Pair *p = map->data[i];
        while (p) {
            Pair *next = p->next;
            free(p->key);
            free(p);
            p = next;
        }
    }

    free(map->data);
    map->data = NULL;
    map->size = 0ULL;
    map->capacity = 0ULL;
    return;
}

void map_set(Map *map, const char *key, uint64_t *data) {

    if (!map->capacity && !map_resize(map, MAP_DEFAULT_CAPACITY))
        return; // fail

    uint64_t id = map_hash(key) % map->capacity;
    for (Pair *p = map->data[id]; p; p = p->next) {
        if (!strcmp(p->key, key)) {
            p->data = *data;
            return;
        }
    }

    // keep load factor at or below 3/4; a failed grow still leaves a valid map
    if ((map->size + 1) * 4 > map->capacity * 3 && map_resize(map, map->capacity * 2))
        id = map_hash(key) % map->capacity;

    Pair *p = malloc(sizeof(Pair));
    if (!p)
        return; // fail

    p->key = map_strdup(key);
    if (!p->key) {
        free(p);
        return; // fail
    }
    p->data = *data;
    p->next = map->data[id];
    map->data[id] = p;

    map->size++;
    return;
}

uint64_t *map_get(Map *map, const char *key) {

    if (!map->capacity)
        return NULL;

    uint64_t id = map_hash(key) % map->capacity;
    for (Pair *p = map->data[id]; p; p = p->next) {
        if (!strcmp(p->key, key))
            return &p->data;
    }

    return NULL;
}

void map_remove(Map *map, const char *key) {

    if (!map->capacity)
        return;

    uint64_t id = map_hash(key) % map->capacity;
    for (Pair **link = &map->data[id]; *link; link = &(*link)->next) {
        Pair *p = *link;
        if (!strcmp(p->key, key)) {
            *link = p->next;
            free(p->key);
            free(p);
            map->size--;
            return;
        }
    }

    return;
}

uint64_t map_size(Map *map) {
    return map->size;
}

uint64_t map_empty(Map *map) {
    return (map->size == 0ULL);
}

void map_print(Map *map) {
    if (!map->size) {
        printf("(empty)\n");
        return;
    }

    for (uint64_t i = 0; i < map->capacity; i++) {
        Pair *bucket = map->data[i];
        if (bucket) {
            printf("\"%s\" => %lu", bucket->key, bucket->data);
            while (bucket->next) {
                bucket = bucket->next;
                printf(", \"%s\" => %lu", bucket->key, bucket->data);
            }
            printf("\n");
        }
    }

    return;
}
