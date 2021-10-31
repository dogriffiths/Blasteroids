#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "move_utils.h"
#include "utils.h"
#include "config.h"
#include "asteroid.h"

//region Asteroid
Asteroid *createRandomAsteroid() {
    Asteroid *asteroid = malloc(sizeof(*asteroid));
    asteroid->x = (float) (rand() % WIDTH),
    asteroid->y = (float) (rand() % HEIGHT),
    asteroid->speed = (float) (rand() % 100) / 30.0f,
    asteroid->spin = -0.1f + (float) (rand() % 100) / 500.0f,
    asteroid->heading = -1.5f + (float) (rand() % 100) / 30.0f,
    asteroid->scale = 0.8f + (float) (rand() % 120) / 100.0f;
    return asteroid;
}

void drawAsteroid(Asteroid *asteroid) {
    ALLEGRO_COLOR color = al_map_rgb_f(1.0f, 1.0f, 1.0f);
    float thickness = 2.0f;

    ALLEGRO_TRANSFORM trans;
    startDrawing(&trans, asteroid->rotation, asteroid->scale, asteroid->x, asteroid->y);

    al_draw_line(-20, 20, -25, 5, color, thickness);
    al_draw_line(-25, 5, -25, -10, color, thickness);
    al_draw_line(-25, -10, -5, -10, color, thickness);
    al_draw_line(-5, -10, -10, -20, color, thickness);
    al_draw_line(-10, -20, 5, -20, color, thickness);
    al_draw_line(5, -20, 20, -10, color, thickness);
    al_draw_line(20, -10, 20, -5, color, thickness);
    al_draw_line(20, -5, 0, 0, color, thickness);
    al_draw_line(0, 0, 20, 10, color, thickness);
    al_draw_line(20, 10, 10, 20, color, thickness);
    al_draw_line(10, 20, 0, 15, color, thickness);
    al_draw_line(0, 15, -20, 20, color, thickness);

    finishDrawing(&trans);
}

void moveAsteroid(Asteroid *asteroid) {
    asteroid->rotation = asteroid->rotation + asteroid->spin;
    MOVE(asteroid->x, asteroid->y, asteroid->heading, asteroid->speed);
    WRAP_WITHIN(asteroid->rotation, -M_PI, M_PI);
    WRAP_WITHIN(asteroid->x, 0, WIDTH);
    WRAP_WITHIN(asteroid->y, 0, HEIGHT);
}
//endregion

