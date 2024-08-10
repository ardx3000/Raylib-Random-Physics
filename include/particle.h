#ifndef PARTICLE_H
#define PARTICLE_H

#include "ranlib.h"

#include "../../../../../opt/homebrew/Cellar/raylib/5.0/include/raylib.h"


typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float radius;
    float life;

} Particle;

Particle CreateParticle(Vector2 position, Vector2 velocity, Color color, float radius, float life);
void UpdateParticle(Particle *p, float deltatime);
void DrawPartilce(Particle p);


#endif