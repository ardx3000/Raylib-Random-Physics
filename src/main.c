#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

#include "particle.h"

#define FPS 60
#define MAX_PARTICLES 1000
#define SPAWN_INTERVAL 0.1f


int main(void) {
    
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Particle Simulator");

    Particle particles[MAX_PARTICLES];
    int particleCount = 0;

    SetTargetFPS(60);
    bool mouseButtonDown = false;
    float timeSinceLastSpawn = 0.0f;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        timeSinceLastSpawn += deltaTime;

        bool isMouseButtonDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

        if (isMouseButtonDown && !mouseButtonDown) {
            timeSinceLastSpawn = 0.0f;
        }

        if (isMouseButtonDown && timeSinceLastSpawn >= SPAWN_INTERVAL) {
            if (particleCount < MAX_PARTICLES) {
                Vector2 position = { GetMouseX(), GetMouseY() };
                Vector2 velocity = { (float)(rand() % 200 - 100) / 10.0f, (float)(rand() % 200 - 100) / 10.0f };
                Color color = (Color){ rand() % 255, rand() % 255, rand() % 255, 255 };
                float radius = (float)(rand() % 10 + 2);
                float life = -1.0f; 

                particles[particleCount++] = CreateParticle(position, velocity, color, radius, life);
                timeSinceLastSpawn = 0.0f; 
            }
        }

        mouseButtonDown = isMouseButtonDown;

        for (int i = 0; i < particleCount; i++) {
            UpdateParticle(&particles[i], deltaTime);
        }

        HandleParticleCollisions(particles, particleCount);

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < particleCount; i++) {
            DrawParticle(particles[i]);
        }

        // FPS and particle count
        char fpsText[64];
        char particleCountText[64];
        snprintf(fpsText, sizeof(fpsText), "FPS: %d", GetFPS());
        snprintf(particleCountText, sizeof(particleCountText), "Particles: %d", particleCount);

        DrawText(fpsText, 10, 10, 20, RAYWHITE);
        DrawText(particleCountText, 10, 40, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}