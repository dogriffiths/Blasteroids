#ifndef BLAST_H
#define BLAST_H
typedef struct Blast {
    float x;
    float y;
    float speed;
    float heading;
} Blast;

void moveBlast(Blast *blast);

void drawBlast(Blast *blast);

#endif
