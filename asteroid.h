typedef struct Asteroid {
    float x;
    float y;
    float speed;
    float heading;
    float rotation;
    float spin;
    float scale;
} Asteroid;

void drawAsteroid(Asteroid *asteroid);

void moveAsteroid(Asteroid *asteroid);

Asteroid *createRandomAsteroid();

