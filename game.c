#include <allegro5/allegro5.h>
#include <stdbool.h>
#include "utils.h"
#include "config.h"
#include "linkedList.h"
#include "move_utils.h"
#include "ship.h"
#include "blast.h"
#include "asteroid.h"
#include "asteroid_list.h"
#include "blast_list.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#define RESERVED_SAMPLES   16
#define MAX_SAMPLE_DATA    10

void moveBlasts();

void moveAsteroids();

void checkHitByAsteroid(Ship *s);

void checkHitAsteroid();

void drawBlasts();

void drawAsteroids();

void loadAudioSamples();

Node *startOfAsteroidList = NULL;

Node *startOfBlastList = NULL;

ALLEGRO_SAMPLE *sample_data[MAX_SAMPLE_DATA] = {NULL};

int main() {
    Game *game = initGame();

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    Ship ship = {.x = (WIDTH / 2.0f), .y = (HEIGHT / 2.0f), .speed = 0.0f};
    startOfAsteroidList = createAsteroidList(50);

    if (!al_install_audio()) {
        exit(1);
    }

    al_init_acodec_addon();

    if (!al_reserve_samples(RESERVED_SAMPLES)) {
        exit(1);
    }

    loadAudioSamples();

    while (1) {
        al_wait_for_event(game->queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_CHAR:
                if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                    accelerate(&ship);
                else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                    decelerate(&ship);
                else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                    turnLeft(&ship);
                else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    turnRight(&ship);
                else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    startOfBlastList = fireBlast(&ship, startOfBlastList);
                    ALLEGRO_SAMPLE_ID new_sample_id;
                    al_play_sample(sample_data[0], 1.0f, 0.0f, 1.0f,
                                   ALLEGRO_PLAYMODE_ONCE, &new_sample_id);
                }

                if (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                    break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(game->queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            moveShip(&ship);
            moveBlasts();
            moveAsteroids();

            checkHitByAsteroid(&ship);
            checkHitAsteroid();

            drawShip(&ship);
            drawBlasts();
            drawAsteroids();

            al_flip_display();

            redraw = false;
        }
    }

    freeList(startOfAsteroidList);
    freeList(startOfBlastList);

    for (int i = 0; i < 3 && i < MAX_SAMPLE_DATA; i++) {
        if (sample_data[i])
            al_destroy_sample(sample_data[i]);
    }

    al_uninstall_audio();

    destroyGame(game);

    return 0;
}

void loadAudioSamples() {
    memset(sample_data, 0, sizeof(sample_data));
    if (!(sample_data[0] = al_load_sample("laser.ogg"))) {
        printf("Could not load sound");
        exit(1);
    }
    if (!(sample_data[1] = al_load_sample("explode.ogg"))) {
        printf("Could not load sound");
        exit(1);
    }
    if (!(sample_data[2] = al_load_sample("split.ogg"))) {
        printf("Could not load sound");
        exit(1);
    }
}

void drawAsteroids() {
    Node *i = startOfAsteroidList;
    while (i) {
        drawAsteroid(i->data);
        i = i->next;
    }
}

void drawBlasts() {
    Node *ib = startOfBlastList;
    while (ib) {
        Blast *blast = ib->data;
        drawBlast(blast);
        ib = ib->next;
    }
}

void checkHitAsteroid() {
    Node *ib = startOfBlastList;
    while (ib) {
        Blast *blast = ib->data;
        Node *next = ib->next;

        Node *pAsteroid = collisionDetected(blast->x, blast->y, 5.0f, startOfAsteroidList);
        if (pAsteroid) {
            if (((Asteroid *) pAsteroid->data)->scale > 0.5f) {
                startOfBlastList = splitAsteroid(pAsteroid, startOfBlastList);
            } else {
                startOfAsteroidList = removeNode(pAsteroid, startOfAsteroidList);
            }
            ALLEGRO_SAMPLE_ID new_sample_id;
            al_play_sample(sample_data[1], 1.0f, 0.0f, 1.0f,
                           ALLEGRO_PLAYMODE_ONCE, &new_sample_id);
            startOfBlastList = removeNode(ib, startOfBlastList);
        }


        ib = next;
    }
}

void checkHitByAsteroid(Ship *s) {
    if (collisionDetected((*s).x, (*s).y, 10.0f, startOfAsteroidList)) {
        (*s).x = WIDTH / 2.0f;
        (*s).y = HEIGHT / 2.0f;
        (*s).speed = 0;
        (*s).heading = 0;
        ALLEGRO_SAMPLE_ID new_sample_id;
        al_play_sample(sample_data[2], 1.0f, 0.0f, 1.0f,
                       ALLEGRO_PLAYMODE_ONCE, &new_sample_id);
    }
}

void moveAsteroids() {
    Node *i = startOfAsteroidList;
    while (i) {
        moveAsteroid(i->data);
        i = i->next;
    }
}

void moveBlasts() {
    Node *ib = startOfBlastList;
    while (ib) {
        Blast *pBlast = ib->data;
        moveBlast(pBlast);
        Node *next = ib->next;
        if ((pBlast->x < 0) || (pBlast->x > WIDTH) || (pBlast->y < 0) || (pBlast->y > HEIGHT)) {
            startOfBlastList = removeNode(ib, startOfBlastList);
        }
        ib = next;
    }
}

