#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *init(int data) {

    Node *n = malloc(sizeof(Node));

    n->data = data;
    n->next = NULL;

    return n;
}

void append(Node *node, int data) {

    if (!node) return;

    Node *n = malloc(sizeof(Node));

    n->data = data;
    n->next = NULL;

    while (node->next)
        node = node->next;
    node->next = n;

    return;
}
