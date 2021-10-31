#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "config.h"
#include "ship.h"
#include "utils.h"
#include "move_utils.h"

void drawShip(Ship *ship) {
    ALLEGRO_COLOR color = al_map_rgb_f(0.0f, 1.0f, 0);
    float thickness = 2.0f;

    ALLEGRO_TRANSFORM trans;
    startDrawing(&trans, ship->heading, 1.0f, ship->x, ship->y);

    al_draw_line(-8.0f, 9.0f, 0, -11.0f, color, thickness);
    al_draw_line(0, -11.0f, 8.0f, 9.0f, color, thickness);
    al_draw_line(-6.0f, 4.0f, -1.0f, 4.0f, color, thickness);
    al_draw_line(6.0f, 4.0f, 1.0f, 4.0f, color, thickness);

    finishDrawing(&trans);
}

void accelerate(Ship *ship) {
    ship->speed = ship->speed + 1.0f;
    KEEP_WITHIN(ship->speed, 0.0f, 10.0f);
}

void decelerate(Ship *ship) {
    ship->speed = ship->speed - 0.5f;
    KEEP_WITHIN(ship->speed, 0.0f, 10.0f);
}

void turnLeft(Ship *ship) {
    ship->heading = ship->heading - 0.3f;
    WRAP_WITHIN(ship->heading, -M_PI, M_PI);
}

void turnRight(Ship *ship) {
    ship->heading = ship->heading + 0.3f;
    WRAP_WITHIN(ship->heading, -M_PI, M_PI);
}

void moveShip(Ship *ship) {
    MOVE(ship->x, ship->y, ship->heading, ship->speed);
    WRAP_WITHIN(ship->x, 0, WIDTH);
    WRAP_WITHIN(ship->y, 0, HEIGHT);
}

