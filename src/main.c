#include "raylib.h"
#include "elyoko.h"
#include <math.h>




int main(int narg,char** sarg)
{
    const char* title = TextFormat("Elyoko ver %s by magnus oblerion",LYO_VERSION);
    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000; //GetMonitorWidth(0);
    const int screenHeight = 600;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, title);

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    LYO_Init(narg,sarg);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);
        LYO_Draw();
        EndDrawing();
    }
    LYO_Free();
    CloseWindow();        // Close window and OpenGL
    return 0;
}

