#include "particle.h"
#include "raymath.h"

Particle CreateParticle(Vector2 position, Vector2 velocity, Color color, float radius, float life) {
    Particle p;
    p.position = position;
    p.velocity = velocity;
    p.color = color;
    p.radius = radius;
    p.life = life;
    return p;
}

float DistanceSquared(Vector2 a, Vector2 b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void UpdateParticle(Particle *p, float deltaTime) {
    //Apply gravity
    p->velocity.y += GRAVITY * deltaTime;

    p->position.x += p->velocity.x * deltaTime;
    p->position.y += p->velocity.y * deltaTime;
    if (p->life > 0.0f) {
        p->life -= deltaTime;
    }


    // Check for collision with the left or right screen edges
    if (p->position.x - p->radius <= 0) {
        p->velocity.x = -p->velocity.x;
        p->position.x = p->radius;
    } else if (p->position.x + p->radius >= GetScreenWidth()) {
        p->velocity.x = -p->velocity.x;
        p->position.x = GetScreenWidth() - p->radius;
    }

    if (p->position.y - p->radius <= 0) {
        p->velocity.y = -p->velocity.y;
        p->position.y = p->radius;
    } else if (p->position.y + p->radius >= GetScreenHeight()) {
        p->velocity.y = -p->velocity.y;
        p->position.y = GetScreenHeight() - p->radius;
    }

    // Reduce life of the particle if not infinite
    if (p->life > 0.0f) {
        p->life -= deltaTime;
    }
    
}

void HandleParticleCollisions(Particle *particles, int particleCount) {
    for (int i = 0; i < particleCount; i++) {
        for (int j = i + 1; j < particleCount; j++) {
            Particle *p1 = &particles[i];
            Particle *p2 = &particles[j];

            
            float distSquared = DistanceSquared(p1->position, p2->position);
            float radiusSum = p1->radius + p2->radius;

            if (distSquared < radiusSum * radiusSum) {
                
                Vector2 normal = Vector2Subtract(p2->position, p1->position);
                float dist = sqrtf(distSquared);
                normal = Vector2Scale(normal, 1.0f / dist);

                //calc relative velocity
                Vector2 relativeVelocity = Vector2Subtract(p1->velocity, p2->velocity);
                float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

                if (velocityAlongNormal > 0) continue;

                //calc new velocity
                Vector2 impulse = Vector2Scale(normal, velocityAlongNormal);

                p1->velocity = Vector2Subtract(p1->velocity, impulse);
                p2-> velocity = Vector2Add(p2->velocity, impulse);

                //separate particles overlapping
                float overlap = 0.5f * (radiusSum - dist);
                p1->position = Vector2Subtract(p1->position, Vector2Scale(normal, overlap));
                p2->position = Vector2Add(p2->position, Vector2Scale(normal, overlap));

            }
        }
    }
}
void DrawParticle(Particle p) {

    DrawCircleV(p.position, p.radius, p.color);
    
}