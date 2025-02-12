 
#include "elyoko.h"

struct selyoko _elyoko={0};
struct selyoko_model* _lyo_getmodel(int id)
{
    if(id>-1 && id<LYO_MAX_MODEL)
        return &_elyoko.models[id];
    return NULL;
}
struct selyoko_texture* _lyo_gettexture(int id)
{
    if(id>-1 && id<LYO_MAX_TEXTURE)
        return &_elyoko.textures[id];
    return NULL;
}
struct selyoko_sound* _lyo_getsound(int id)
{
    if(id>-1 && id<LYO_MAX_SOUND)
        return &_elyoko.sounds[id];
    return NULL;
}
struct selyoko_music* _lyo_getmusic(int id)
{
    if(id>-1 && id<LYO_MAX_MUSIC)
        return &_elyoko.musics[id];
    return NULL;
}

// return 1 if load
char _lyo_loadmodel(struct selyoko_model* smodel,const char* path)
{
    char rc = 0;
    if(smodel == NULL) return rc;
    if(smodel->isload==0)
    {
        smodel->isload=1;
        strcpy(smodel->name,GetFileName(path));
        smodel->model=LoadModel(path);
        LM_AppliShader(&smodel->model);
        printf("[ELYOKO] : load %s\n",smodel->name);
        rc = 1;
    }
    return rc;
}

char _lyo_loadmeshdata(struct selyoko_model* smodel,const char* name,Model model)
{
    char rc = 0;
    if(smodel == NULL) return rc;
    if(smodel->isload==0)
    {
        smodel->isload=1;
        strcpy(smodel->name,name);
        smodel->model = model;
        printf("[ELYOKO] : load %s \n",smodel->name);
        rc = 1;
    }
    return rc;
}

void _lyo_unloadmodel(struct selyoko_model* smodel)
{
    if(smodel == NULL) return;
    if(smodel->isload==1)
    {
        const char* toul_model = TextFormat("%s",smodel->name);
        smodel->isload=0;
        strcpy(smodel->name,"");
        UnloadModel(smodel->model);
        printf("[ELYOKO] : unload %s \n",toul_model);
    }

}

void _lyo_printmodel(struct selyoko_model smodel)
{
    if(smodel.isload)
    {
        printf("%s \n",smodel.name);
    }
}


char _lyo_loadtexture(struct selyoko_texture* stexture,const char* path)
{
    char rc = 0;
    if(stexture == NULL) return rc;
    if(stexture->isload==0)
    {
        stexture->isload=1;
        strcpy(stexture->name,GetFileName(path));
        stexture->texture=LoadTexture(path);
        printf("[ELYOKO] : load texture %s\n",stexture->name);
        rc = 1;
    }
    return rc;
}

void _lyo_unloadtexture(struct selyoko_texture* stexture)
{
    if(stexture == NULL) return;
    if(stexture->isload)
    {
        stexture->isload=0;
        strcpy(stexture->name,"");
        UnloadTexture(stexture->texture);
        printf("[ELYOKO] : unload texture %s\n",stexture->name);
    }
}

void _lyo_printtexture(struct selyoko_texture stexture)
{
    if(stexture.isload)
    {
        printf("%s \n",stexture.name);
    }
}

char _lyo_loadsound(struct selyoko_sound* ssound,const char* path)
{
    char rc = 0;
    if(ssound == NULL) return rc;
    if(ssound->isload==0)
    {
        ssound->isload = 1;
        const char* name = GetFileName(path);
        strncpy(ssound->name,name,30);
        ssound->sound = LoadSound(path);
        printf("[ELYOKO] : load %s\n",ssound->name);
        rc = 1;
    }
    return rc;
}

void _lyo_unloadsound(struct selyoko_sound* ssound)
{
    if(ssound == NULL) return;
    if(ssound->isload)
    {
        ssound->isload=0;
        strcpy(ssound->name,"");
        UnloadSound(ssound->sound);
    }
}

void _lyo_printsound(struct selyoko_sound ssound)
{
    if(ssound.isload)
    {
        printf("%s \n",ssound.name);
    }
}

char _lyo_loadmusic(struct selyoko_music* smusic, const char* path)
{
    char rc = 0;
    if(smusic == NULL) return rc;
    if(smusic->isload==0)
    {
        smusic->isload=1;
        const char* name = GetFileName(path);
        strncpy(smusic->name,name,30);
        smusic->music=LoadMusicStream(path);
        printf("[ELYOKO] : load %s\n",smusic->name);
        rc=1;
    }
    return rc;
}

void _lyo_unloadmusic(struct selyoko_music* smusic)
{
    if(smusic == NULL) return;
    if(smusic->isload)
    {
        smusic->isload=0;
        strcpy(smusic->name,"");
        UnloadMusicStream(smusic->music);
    }
}

void _lyo_printmusic(struct selyoko_music smusic)
{
    if(smusic.isload)
    {
        printf("%s \n",smusic.name);
    }
}

//----------------------- public function
void LYO_PrintLoaded()
{
    puts("[ELYOKO] : model loaded :");
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        struct selyoko_model* smodel = _lyo_getmodel(i);
        _lyo_printmodel(*smodel);
    }
    puts("[ELYOKO] : texture loaded :");
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        struct selyoko_texture* stexture = _lyo_gettexture(i);
        _lyo_printtexture(*stexture);
    }
    puts("[ELYOKO] : sound loaded :");
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(ssound->isload)
        {
            // _elyoko.lsound_isload[i]=0;
            // UnloadSound(_elyoko.lsound[i]);
        }
    }
    puts("[ELYOKO] : music loaded :");
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(smusic->isload)
        {
            // _elyoko.lmusic_isload[i]=0;
            // UnloadMusicStream(_elyoko.lmusic[i]);
        }
    }
}

void LYO_LoadMesh(const char* path)
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        struct selyoko_model* smodel = _lyo_getmodel(i);
        if( _lyo_loadmodel(smodel,path))
        {
            printf("[ELYOKO] : on id %d\n",i);
            break;
        }
    }
}
void LYO_LoadMeshData(const char* name,Model model)
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        struct selyoko_model* smodel = _lyo_getmodel(i);
        if(_lyo_loadmeshdata(smodel,name,model))
        {
            printf("[ELYOKO] : on id %d\n",i);
            break;
        }
    }
}
void LYO_DelMeshI(int pos)
{
    struct selyoko_model* smodel = _lyo_getmodel(pos);
    if(smodel->isload==1)
    {
        const char* toul_model = TextFormat("%s",smodel->name);
        smodel->isload=0;
        strcpy(smodel->name,"");
        UnloadModel(smodel->model);
        //_lyo_setmodel(pos,smodel);
        printf("[ELYOKO] : unload %s in id %d\n",toul_model,pos);
    }
}
void LYO_DelMesh(const char* name)
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        struct selyoko_model* smodel = _lyo_getmodel(i);
        if(TextIsEqual(smodel->name,name))
        {
            LYO_DelMeshI(i);
            break;
        }
    }
}
void LYO_DrawMesh(const char* name,float x,float y,float z,float rx,float ry,float rz,float scale)
{
    int id_mesh=-1;
    Model cmodel = {0};
    struct selyoko_model* smodel = NULL;
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        smodel = _lyo_getmodel(i);
        if(TextIsEqual(smodel->name,name))
        {
            id_mesh=i;
            break;
        }
    }
    if(id_mesh>-1)
    {
        float lscale = 1;
        if(scale>0) lscale=scale;
        cmodel = smodel->model;
        cmodel.transform = MatrixRotateXYZ((Vector3){rx,ry,rz});
        DrawModel(cmodel,(Vector3){x,y,z},lscale,WHITE);
    }
    else
    {
        int ti = floor(GetTime()*60);
        if((ti%65)==0)
        printf("[ELYOKO] : model %s not found\n",name);
    }

}

void LYO_LoadTexture(const char* path)
{
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        struct selyoko_texture* stexture = _lyo_gettexture(i);
        if(_lyo_loadtexture(stexture,path))
        {
            printf("[ELYOKO] : on id %d\n",i);
            break;
        }
    }
}
Texture* LYO_GetTexture(const char* name)
{
    Texture* t=NULL;
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        struct selyoko_texture* stexture = _lyo_gettexture(i);
        if(TextIsEqual(stexture->name,name))
        {
            t = &stexture->texture;
            break;
        }
    }
    return t;
}
void LYO_DelTexture(const char* name)
{
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        struct selyoko_texture* stexture = _lyo_gettexture(i);
        if(TextIsEqual(name,stexture->name))
        {
            _lyo_unloadtexture(stexture);
            break;
        }
    }
}
void LYO_DrawTexture(const char* name,float x,float y)
{
    int id_text=-1;
    struct selyoko_texture* stexture = NULL;
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        stexture = _lyo_gettexture(i);
        if(TextIsEqual(stexture->name,name))
        {
            id_text=i;
            break;
        }
    }
    if(id_text>-1)
    {
        DrawTexture(stexture->texture,x,y,WHITE);
        //printf("[ELYOKO] : draw mesh id %d\n",id_mesh);
    }
    else
    {
        int ti = floor(GetTime()*60);
        if((ti%65)==0)
        printf("[ELYOKO] : texture %s not found\n",name);
    }

}

void LYO_LoadSound(const char* path)
{
    struct selyoko_sound* ssound = NULL;
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        ssound = _lyo_getsound(i);
        if(_lyo_loadsound(ssound,path))
        {
            //_lyo_setsound(i,ssound);
            SetSoundVolume(ssound->sound,1.0f);
            printf("[ELYOKO] : on id %d\n",i);
            break;
        }
    }
}

void LYO_DelSound(const char* name)
{
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(TextIsEqual(name,ssound->name))
        {
            _lyo_unloadsound(ssound);
            break;
        }
    }
}
void LYO_PlaySound(const char* name)
{
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(TextIsEqual(name,ssound->name))
        {
            PlaySound(ssound->sound);
            break;
        }
    }
}
void LYO_SetSoundVolume(const char* name,float vol)
{
    if(vol<0 || vol>1) return;
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(TextIsEqual(name,ssound->name))
        {
            SetSoundVolume(ssound->sound,vol);
            break;
        }
    }
}
void LYO_SetSoundPan(const char* name,float pan)
{
    if(pan<0 || pan>1) return;
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(TextIsEqual(name,ssound->name))
        {
            SetSoundPan(ssound->sound,pan);
            break;
        }
    }
}
void LYO_SetSoundPitch(const char* name,float pit)
{
    if(pit<0 || pit>1) return;
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(TextIsEqual(name,ssound->name))
        {
            SetSoundPitch(ssound->sound,pit);
            break;
        }
    }
}

void LYO_LoadMusic(const char* path)
{
    struct selyoko_music* smusic = NULL;
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        smusic = _lyo_getmusic(i);
        if(_lyo_loadmusic(smusic,path))
        {
            SetMusicVolume(smusic->music,1.0f);
            printf("[ELYOKO] : on id %d\n",i);
            break;
        }
    }
}
void LYO_DelMusic(const char* name)
{
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            _lyo_unloadmusic(smusic);
            break;
        }
    }
}
void _LYO_UpdateMusic()
{
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(smusic->isload && smusic->isplay)
            UpdateMusicStream(smusic->music);
    }
}

void LYO_PlayMusic(const char* name)
{
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            PlayMusicStream(smusic->music);
            smusic->isplay=1;
            //_lyo_setmusic(i,smusic);
            break;
        }
    }
}
void LYO_PauseMusic(const char* name)
{
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            PauseMusicStream(smusic->music);
            smusic->isplay=0;
            break;
        }

    }
}
void LYO_StopMusic(const  char* name)
{
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            StopMusicStream(smusic->music);
            smusic->isplay=0;
            break;
        }
    }
}
void LYO_SetMusicVolume(const char* name,float vol)
{
    if(vol<0 || vol>1) return;
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            SetMusicVolume(smusic->music,vol);
            break;
        }
    }
}
void LYO_SetMusicPan(const char* name,float pan)
{
    if(pan<0 || pan>1) return;
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            SetMusicPan(smusic->music,pan);
            break;
        }
    }
}
void LYO_SetMusicPitch(const char* name,float pit)
{
    if(pit<0 || pit>1) return;
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(TextIsEqual(name,smusic->name))
        {
            SetMusicPitch(smusic->music,pit);
            break;
        }
    }
}


#include "elyoko_runner.h"
#include "elyoko_editor.h"

void LYO_Init(int narg,char** sarg)
{
    LM_Init();
    // LM_AddDirectionalLight((Vector3){0,1300,0},(Vector3){0,0,0},WHITE);
    LM_AddPointLight((Vector3){-1300,1300,0},(Vector3){0,0,0},WHITE);
    LM_AddPointLight((Vector3){1300,1300,0},(Vector3){0,0,0},LIGHTGRAY);
    LM_AddPointLight((Vector3){0,1300,1300},(Vector3){0,0,0},DARKGRAY);
    LM_AddPointLight((Vector3){0,1300,-1300},(Vector3){0,0,0},DARKGRAY);

    InitAudioDevice();

    int ientry = Runner_Init(narg,sarg);
    if(ientry)
    {
        _elyoko.iseditor=0;
        Editor_Init(narg);
    }
    else if(!Editor_Init(narg))
    {
        _elyoko.iseditor = 0;
    }
    else
    {
        _elyoko.iseditor=1;
    }
}
void LYO_Draw()
{
    if(!_elyoko.iseditor)
    {
        _LYO_UpdateMusic();
        Runner_Draw3d();
        Runner_Draw2d();
        if(IsKeyPressed(KEY_SPACE))
        {// full reset
            LYO_Reset();
            _elyoko.iseditor=1;
            Runner_Free();
            Runner_Init(1,NULL);
            Editor_Init(1);
        }
    }
    else
    {
        _elyoko.iseditor = Editor_Draw();
    }
}
void LYO_Reset()
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        struct selyoko_model* smodel = _lyo_getmodel(i);
        if(smodel->isload)
        {
            _lyo_unloadmodel(smodel);
        }
    }
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        struct selyoko_texture* stexture = _lyo_gettexture(i);
        if(stexture->isload)
        {
           _lyo_unloadtexture(stexture);
        }
    }
    for(int i=0;i<LYO_MAX_SOUND;i++)
    {
        struct selyoko_sound* ssound = _lyo_getsound(i);
        if(ssound->isload)
        {
            _lyo_unloadsound(ssound);
        }
    }
    for(int i=0;i<LYO_MAX_MUSIC;i++)
    {
        struct selyoko_music* smusic = _lyo_getmusic(i);
        if(smusic->isload)
        {
            _lyo_unloadmusic(smusic);
        }
    }
}
void LYO_Free()
{
    CloseAudioDevice();
    LYO_Reset();
    LM_Unload();
    Runner_Free();
}
