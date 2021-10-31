#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "asteroid.h"
#include "asteroid_list.h"

Node *createAsteroidList(int num) {
    Node *start = NULL;
    for (size_t i = 0; i < num; i++) {
        Node *link = malloc(sizeof(*link));

        link->data = createRandomAsteroid();

        link->next = start;
        link->previous = NULL;
        if (start) {
            start->previous = link;
        }
        start = link;
    }

    return start;
}

void splitAsteroid(Node *node, Node* startOfBlastList) {
    Asteroid *newAsteroid = createRandomAsteroid();
    Asteroid *asteroid = (Asteroid *) node->data;
    newAsteroid->x = asteroid->x;
    newAsteroid->y = asteroid->y;
    asteroid->scale = asteroid->scale / 2.0f;
    newAsteroid->scale = asteroid->scale;

    Node *link = insertBefore(newAsteroid, node);
    if (node == startOfBlastList)
        startOfBlastList = link;
}

Node *collisionDetected(float x, float y, float otherRadius, Node* startOfAsteroidList) {
    Node *collision = NULL;
    Node *i = startOfAsteroidList;
    while (i) {
        Asteroid *asteroid = i->data;
        float radius = (asteroid->scale * 20.0f) + otherRadius;
        double diffX = fabs(asteroid->x - x);
        double diffY = fabs(asteroid->y - y);
        if ((diffX * diffX) + (diffY * diffY) < (radius * radius)) {
            collision = i;
            break;
        }
        i = i->next;
    }
    return collision;
}
//endregion


