#include "raylib.h"
#include "lightmanager.h"
#include <math.h>
int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000; //GetMonitorWidth(0);
    const int screenHeight = 600;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "Elyoko ver a0.0 by magnus oblerion");

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //Font f = LoadFont(".ttf");
    
    Camera camera = (Camera){
        (Vector3){ 0, 1.0f, -10.0f }, // Camera position
        (Vector3){ 0.0f, 0.0f, 0.0f },      // Camera looking at point
        (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
        45.0f,                                // Camera field-of-view Y
        CAMERA_PERSPECTIVE
    };

    LM_Init();
    LM_AddDirectionalLight((Vector3){20,50,0},(Vector3){0,0,0},WHITE);
    //LM_AddPointLight((Vector3){10,10,5},(Vector3){0,0,0},WHITE);

    Model mo = LoadModel("asset/mcube.glb");
    LM_AppliShader(&mo);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //if(IsKeyDown(KEY_S))
       
        BeginDrawing();
        ClearBackground(BLUE);

        BeginMode3D(camera);
        UpdateCamera(&camera,CAMERA_FIRST_PERSON);
        DrawGrid(100,0.5f);
        DrawModel(mo,(Vector3){sinf(GetTime())*5,0,0},1,WHITE);
        //DrawCube((Vector3){0,0,0},1,1,1,WHITE);
        EndMode3D();


        EndDrawing();
    }
   // UnloadModel(model);
   UnloadModel(mo);
    LM_Unload();
    CloseWindow();        // Close window and OpenGL
    return 0;
}

