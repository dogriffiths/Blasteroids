#include "linkedList.h"

struct Node *collisionDetected(float x, float y, float otherRadius, Node* startOfAsteroidList);
Node *createAsteroidList(int num);
void splitAsteroid(Node *node, Node* startOfBlastList);

