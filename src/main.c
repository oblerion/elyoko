#include "raylib.h"
#include "elyoko.h"
#include "runner.h"
#include <math.h>


void _Runner_Init(int narg,char** sarg)
{
    if(narg==2)
    {
        Runner_Init();
        Runner_DoFile(sarg[1]);
    }
    else
    {
        FilePathList files = LoadDirectoryFiles(".");
        for(int i=0;i<files.count;i++)
        {
            if(TextIsEqual(GetFileExtension(files.paths[i]),".entry"))
            {
                char flua[50];
                strcpy(flua,GetFileNameWithoutExt(files.paths[i]));
                strcat(flua,".lua");
                Runner_Init();
                Runner_DoFile(flua);
                break;
            }
        }
        UnloadDirectoryFiles(files);
    }
}

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
    LYO_Init();

   _Runner_Init(narg,sarg);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);

        Runner_Draw3d();
        Runner_Draw2d();

        EndDrawing();
    }

    Runner_Free();
    LYO_Free();
    CloseWindow();        // Close window and OpenGL
    return 0;
}

