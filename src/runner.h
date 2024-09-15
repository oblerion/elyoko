#pragma once
#include "elyoko.h"
#include "clua.h"
#include <string.h>

#define RUNNER_MAX_CAMERA 3

struct srunner
{
    int camera_id;
    Camera cam3d;
    Camera2D cam2d;
    struct CLUA clua;
    char isload;
    char iscameralock;
};

void Runner_Init();
void Runner_DoFile(const char*);
void Runner_Draw2d();
void Runner_Draw3d();
void Runner_Free();

