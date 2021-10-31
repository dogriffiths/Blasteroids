#include <allegro5/allegro_font.h>

#ifndef BLASTEROIDS_UTILS_H
#define BLASTEROIDS_UTILS_H

typedef struct Game {
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_FONT *font;
} Game;

void finishDrawing(ALLEGRO_TRANSFORM *trans);

void startDrawing(ALLEGRO_TRANSFORM *trans, float angle, float scale, float x, float y);

Game *initGame();

void destroyGame(Game *game);
#endif //BLASTEROIDS_UTILS_H
