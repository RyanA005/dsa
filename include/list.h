#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*

    list_new ; return new list
    list_free ; delete list

    list_push_tail ; add item to the end
    list_push_head ; add item to the front

    list_pop_tail ; remove item from the end
    list_pop_head ; remove item from the front

    list_insert ; put item at index, shift latter right
    list_remove ; remove item at index, shift latter left

    list_get ; get item at index
    list_set ; set item at index

    list_size ; return list size
    list_empty ; return 1 if list is empty

 */

typedef struct Node {
    struct Node* next;
    uint64_t data;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    uint64_t size;
} List;

Node *node_new(uint64_t data, Node *next) {
    Node *n = malloc(sizeof(Node));
    if (!n)
        return NULL; // fail

    n->data = data;
    n->next = next;
    return n;
}

Node *node_at(List *list, uint64_t index) {
    Node *curr = list->head;
    for (uint64_t i = 0; i < index; i++)
        curr = curr->next;

    return curr;
}

List list_new(void) {

    List list = {
        .tail = NULL,
        .head = NULL,
        .size = 0ULL
    };

    return list;
}

void list_free(List *list) {
    Node *curr = list->head;
    while (curr) {
        Node *temp = curr->next;
        free(curr);
        curr = temp;
    }
    list->tail = NULL;
    list->head = NULL;
    list->size = 0ULL;

    return;
}

void list_push_tail(List *list, uint64_t *data) {
    Node *n = node_new(*data, NULL);
    if (!n)
        return; // fail

    if (!list->head) {
        list->head = n;
    } else {
        list->tail->next = n;
    }
    list->tail = n;

    list->size++;
    return;
}

void list_push_head(List *list, uint64_t *data) {
    Node *n = node_new(*data, list->head);
    if (!n)
        return; // fail

    if (!list->head)
        list->tail = n;
    list->head = n;

    list->size++;
    return;
}

uint64_t list_pop_tail(List *list) {
    if (!list->head) {
        return 0; // fail

    } else if (list->head == list->tail) {
        uint64_t data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size--;
        return data;

    } else {
        Node *curr = node_at(list, list->size - 2);

        uint64_t data = list->tail->data;
        free(list->tail);
        curr->next = NULL;
        list->tail = curr;
        list->size--;
        return data;

    }
}

uint64_t list_pop_head(List *list) {
    if (!list->head)
        return 0; // fail

    Node *old = list->head;
    uint64_t data = old->data;

    list->head = old->next;
    if (!list->head)
        list->tail = NULL;
    free(old);

    list->size--;
    return data;
}

void list_insert(List *list, uint64_t index, uint64_t *data) {
    if (index > list->size) {
        return; // fail
    } else if (index == 0) {
        list_push_head(list, data);
        return;
    } else if (index == list->size) {
        list_push_tail(list, data);
        return;
    }

    Node *prev = node_at(list, index - 1);
    Node *n = node_new(*data, prev->next);
    if (!n)
        return; // fail

    prev->next = n;
    list->size++;
    return;
}

void list_remove(List *list, uint64_t index) {
    if (index >= list->size) {
        return; // fail
    } else if (index == 0) {
        list_pop_head(list);
        return;
    } else if (index == list->size - 1) {
        list_pop_tail(list);
        return;
    }

    Node *prev = node_at(list, index - 1);
    Node *target = prev->next;
    prev->next = target->next;
    free(target);

    list->size--;
    return;
}

void list_set(List *list, uint64_t index, uint64_t *data) {
    if (index >= list->size)
        return; // fail

    node_at(list, index)->data = *data;
    return;
}

uint64_t *list_get(List *list, uint64_t index) {
    if (index >= list->size)
        return NULL;

    return &node_at(list, index)->data;
}

uint64_t list_size(List *list) {
    return list->size;
}

uint64_t list_empty(List *list) {
    return (!list->head);
}

void list_print(List* list) {
    if (!list->head) {
        printf("(empty)\n");
        return;
    }

    Node *n = list->head;
    while (n->next) {
        printf("%lu -> ", n->data);
        n = n->next;
    }
    printf("%lu\n", n->data);

    return;
}
