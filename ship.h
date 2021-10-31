#ifndef SHIP_H
#define SHIP_H
typedef struct Ship {
    float x;
    float y;
    float speed;
    float heading;
} Ship;

void drawShip(Ship *ship);

void moveShip(Ship *ship);

void turnLeft(Ship *ship);

void turnRight(Ship *ship);

void accelerate(Ship *ship);

void decelerate(Ship *ship);
#endif
