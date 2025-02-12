#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "raymath.h"
#include "lightmanager.h"

#define LYO_VERSION "a0.5"
#define LYO_MAX_MODEL 100
#define LYO_MAX_TEXTURE 100
#define LYO_MAX_SOUND 100
#define LYO_MAX_MUSIC 100

struct selyoko_model
{
    char isload;
    char name[30];
    Model model;
};

struct selyoko_texture
{
    char isload;
    char name[30];
    Texture texture;
};

struct selyoko_sound
{
    char isload;
    char isplay;
    char name[30];
    Sound sound;
};

struct selyoko_music
{
    char isload;
    char isplay;
    char name[30];
    Music music;
};

struct selyoko
{
    struct selyoko_model models[LYO_MAX_MODEL];
    struct selyoko_texture textures[LYO_MAX_TEXTURE];
    struct selyoko_sound sounds[LYO_MAX_SOUND];
    struct selyoko_music musics[LYO_MAX_MUSIC];

    char iseditor;
};

// debug
void LYO_PrintLoaded();

// model
void LYO_LoadMesh(const char* path);
void LYO_LoadMeshData(const char* name,Model model);
void LYO_DelMesh(const char* name);
void LYO_DrawMesh(const char* name,float x,float y,float z,float rx,float ry,float rz,float scale);
// texture
void LYO_LoadTexture(const char* path);
Texture* LYO_GetTexture(const char* name);
void LYO_DelTexture(const char* name);
void LYO_DrawTexture(const char* name,float x,float y);
void LYO_ClearTextures();
// sound
void LYO_LoadSound(const char* path);
void LYO_DelSound(const char* name);
void LYO_PlaySound(const char* name);
void LYO_SetSoundVolume(const char* name,float vol);
void LYO_SetSoundPan(const char* name,float pan);
void LYO_SetSoundPitch(const char* name,float pit);
// music
void LYO_LoadMusic(const char* path);
void LYO_DelMusic(const char* name);
void LYO_PlayMusic(const char* name);
void LYO_PauseMusic(const char* name);
void LYO_StopMusic(const  char* name);
void LYO_SetMusicVolume(const char* name,float vol);
void LYO_SetMusicPan(const char* name,float pan);
void LYO_SetMusicPitch(const char* name,float pit);

// main
void LYO_Init(int narg,char** sarg);
void LYO_Draw();
void LYO_Reset();
void LYO_Free();
