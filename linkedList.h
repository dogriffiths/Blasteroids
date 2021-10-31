//
// Created by David Griffiths on 06/09/2021.
//

#ifndef BLASTEROIDS_LINKEDLIST_H
#define BLASTEROIDS_LINKEDLIST_H

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *previous;
} Node;

Node *insertBefore(void *data, Node *existingNode);

Node *removeNode(Node *node, Node *startOfList);

void freeList(Node *startOfList);

#endif //BLASTEROIDS_LINKEDLIST_H
