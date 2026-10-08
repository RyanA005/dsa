#include <stdio.h>
#include <stdint.h>

#include "../include/list.h"

int main(void) {
    List list = list_new();
    uint64_t v;
    list_print(&list);
    printf("empty: %lu, pop on empty: %lu\n", list_empty(&list), list_pop_tail(&list));

    for (v = 1; v <= 3; v++)
        list_push_tail(&list, &v);
    v = 0; list_push_head(&list, &v);
    list_print(&list);

    v = 9; list_insert(&list, 2, &v);
    v = 8; list_insert(&list, list_size(&list), &v);
    v = 7; list_insert(&list, 99, &v);
    list_print(&list);

    list_remove(&list, 2);
    list_remove(&list, 0);
    list_remove(&list, 99);
    list_print(&list);

    v = 5; list_set(&list, 0, &v);
    uint64_t *got = list_get(&list, 0);
    printf("get 0: %lu, get 99: %s\n", got ? *got : 0, list_get(&list, 99) ? "found" : "NULL");

    printf("pop tail: %lu\n", list_pop_tail(&list));
    printf("pop head: %lu\n", list_pop_head(&list));
    printf("size: %lu\n", list_size(&list));
    list_print(&list);

    list_free(&list);
    list_print(&list);

    return 0;
}
