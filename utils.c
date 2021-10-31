#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "utils.h"
#include "config.h"

void must_init(bool test, const char *description) {
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

Game *initGame() {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY *disp = al_create_display(WIDTH, HEIGHT);
    must_init(disp, "display");

    ALLEGRO_FONT *font = al_create_builtin_font();
    must_init(font, "font");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    Game *game = malloc(sizeof(*game));
    game->timer = timer;
    game->queue = queue;
    game->font = font;
    game->disp = disp;

    return game;
}

void destroyGame(Game *game) {
    al_destroy_font(game->font);
    al_destroy_display(game->disp);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);
}

void finishDrawing(ALLEGRO_TRANSFORM *trans) {
    al_identity_transform(trans);
    al_use_transform(trans);
}

void startDrawing(ALLEGRO_TRANSFORM *trans, float angle, float scale, float x, float y) {
    al_identity_transform(trans);
    al_rotate_transform(trans, angle);
    al_scale_transform(trans, scale, scale);
    al_translate_transform(trans, x, y);

    al_use_transform(trans);
}