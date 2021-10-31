#include <allegro5/allegro_primitives.h>
#include "linkedList.h"

Node *insertBefore(void *data, Node *existingNode) {
    Node *link = malloc(sizeof(*link));
    link->data = data;
    link->next = existingNode;
    if (existingNode) {
        struct Node *beforeNode = existingNode->previous;
        link->previous = beforeNode;
        if (beforeNode) {
            beforeNode->next = link;
        }
        existingNode->previous = link;
    } else {
        link->previous = NULL;
    }
    return link;
}

Node *removeNode(Node *node, Node *startOfList) {
    Node *start = startOfList;
    if (node->previous) {
        node->previous->next = node->next;
        if (node->next) {
            node->next->previous = node->previous;
        }
    }
    if (node == startOfList) {
        if (node->next) {
            node->next->previous = NULL;
        }
        start = node->next;
    }
    free(node->data);
    free(node);
    return start;
}

void freeList(Node *startOfList) {
    Node *j = startOfList;
    while (j) {
        Node *n = j->next;
        free(j->data);
        free(j);
        j = n;
    }
}