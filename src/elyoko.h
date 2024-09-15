#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "raymath.h"
#include "lightmanager.h"

#define LYO_VERSION "a0.2"
#define LYO_MAX_MODEL 100
#define LYO_MAX_TEXTURE 100

struct selyoko
{
    char lmodel_isload[LYO_MAX_MODEL];
    char lmodel_name[LYO_MAX_MODEL][30];
    Model lmodel[LYO_MAX_MODEL];
    char ltexture_isload[LYO_MAX_TEXTURE];
    char ltexture_name[LYO_MAX_TEXTURE][30];
    Texture ltexture[LYO_MAX_TEXTURE];
};

void LYO_LoadMesh(const char* path);
void LYO_LoadMeshData(const char* name,Model model);
void LYO_DelMesh(const char* name);
void LYO_DrawMesh(const char* name,float x,float y,float z,float rx,float ry,float rz,float scale);
void LYO_ClearMeshes();
void LYO_LoadTexture(const char* path);
Texture* LYO_GetTexture(const char* name);
void LYO_DelTexture(const char* name);
void LYO_DrawTexture(const char* name,float x,float y);
void LYO_ClearTextures();
void LYO_Init();
void LYO_Free();
