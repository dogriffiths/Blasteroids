#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "utils.h"
#include "move_utils.h"
#include "blast.h"

//region Blast
void moveBlast(Blast *blast) {
    MOVE(blast->x, blast->y, blast->heading, blast->speed);
}

void drawBlast(Blast *blast) {
    ALLEGRO_COLOR color = al_map_rgb_f(1.0f, 1.0f, 0);
    float thickness = 3.0f;

    ALLEGRO_TRANSFORM trans;
    startDrawing(&trans, blast->heading, 1.0f, blast->x, blast->y);

    for (int i = 0; i < 15; i += 3) {
        al_draw_line(0.0f, (float) i * 2.0f, 0.0f, (float) (i + 1) * 2.0f, color, thickness);
    }

    finishDrawing(&trans);
}
//endregion
