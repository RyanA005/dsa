#include <stdio.h>
#include <stdint.h>

#include "../include/map.h"

int main(void) {
    Map map = map_new();
    uint64_t v;
    map_print(&map);
    printf("empty: %lu, get missing: %s\n", map_empty(&map), map_get(&map, "a") ? "found" : "NULL");

    v = 1; map_set(&map, "a", &v);
    v = 2; map_set(&map, "b", &v);
    v = 3; map_set(&map, "", &v);
    v = 10; map_set(&map, "a", &v);
    map_print(&map);
    printf("size: %lu, get a: %lu\n", map_size(&map), *map_get(&map, "a"));

    map_remove(&map, "b");
    map_remove(&map, "missing");
    map_print(&map);

    char key[16];
    for (v = 0; v < 1000; v++) {
        snprintf(key, sizeof(key), "key%lu", v);
        map_set(&map, key, &v);
    }
    printf("set 1000, size: %lu, capacity: %lu, get key500: %lu\n",
           map_size(&map), map.capacity, *map_get(&map, "key500"));

    map_free(&map);
    map_print(&map);

    return 0;
}
