#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define FPS 60
#define CIRCLE_SIZE 10


int main(void)
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physiscs simulator");
    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        //Update
        //Update variables

        //Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Window", 190, 200, 20, RAYWHITE);
        EndDrawing();
    }

    //De-init
    CloseWindow();
    

    return 0;
}