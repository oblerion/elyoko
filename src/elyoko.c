 
#include "elyoko.h"

struct selyoko _elyoko={0};

void LYO_LoadMesh(const char* path)
{
    const char* name = GetFileName(path);
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        if(_elyoko.lmodel_isload[i]==0)
        {
            _elyoko.lmodel_isload[i]=1;
            strcpy(_elyoko.lmodel_name[i],name);
            _elyoko.lmodel[i]=LoadModel(path);
            LM_AppliShader(&_elyoko.lmodel[i]);
            printf("[ELYOKO] : load %s in id %d\n",name,i);
            break;
        }
    }
}
void LYO_LoadMeshData(const char* name,Model model)
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        if(_elyoko.lmodel_isload[i]==0)
        {
            _elyoko.lmodel_isload[i]=1;
            strcpy(_elyoko.lmodel_name[i],name);
            _elyoko.lmodel[i]=model;
            //LM_AppliShader(&_elyoko.lmodel[i]);
            printf("[ELYOKO] : load %s in id %d\n",name,i);
            break;
        }
    }
}
void LYO_DelMesh(const char* name)
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        if(TextIsEqual(_elyoko.lmodel_name[i],name))
        {
            _elyoko.lmodel_isload[i]=0;
            strcpy(_elyoko.lmodel_name[i],"");
            UnloadModel(_elyoko.lmodel[i]);
            printf("[ELYOKO] : delete mesh %s in id %d\n",name,i);
            break;
        }
    }
}
void LYO_DrawMesh(const char* name,float x,float y,float z,float rx,float ry,float rz,float scale)
{
    int id_mesh=-1;
    Model cmodel = {0};
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        if(TextIsEqual(_elyoko.lmodel_name[i],name))
        {
            id_mesh=i;
            break;
        }
    }
    if(id_mesh>-1)
    {
        float lscale = 1;
        if(scale>0) lscale=scale;
        cmodel = _elyoko.lmodel[id_mesh];
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
void LYO_ClearMeshes()
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        if(_elyoko.lmodel_isload[i]==1)
        {
            LYO_DelMesh(_elyoko.lmodel_name[i]);
        }
    }
}
void LYO_LoadTexture(const char* path)
{
    const char* name = GetFileName(path);
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        if(_elyoko.ltexture_isload[i]==0)
        {
            _elyoko.ltexture_isload[i]=1;
            strcpy(_elyoko.ltexture_name[i],name);
            _elyoko.ltexture[i]=LoadTexture(path);
            printf("[ELYOKO] : load texture %s in id %d\n",name,i);
            break;
        }
    }
}
Texture* LYO_GetTexture(const char* name)
{
    Texture* t=NULL;
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        if(TextIsEqual(_elyoko.ltexture_name[i],name))
        {
            t = &_elyoko.ltexture[i];
            break;
        }
    }
    return t;
}
void LYO_DelTexture(const char* name)
{
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        if(TextIsEqual(_elyoko.ltexture_name[i],name))
        {
            _elyoko.ltexture_isload[i]=0;
            strcpy(_elyoko.ltexture_name[i],"");
            UnloadTexture(_elyoko.ltexture[i]);
            printf("[ELYOKO] : delete texture %s in id %d\n",name,i);
            break;
        }
    }
}
void LYO_DrawTexture(const char* name,float x,float y)
{
    int id_text=-1;
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        if(TextIsEqual(_elyoko.ltexture_name[i],name))
        {
            id_text=i;
            break;
        }
    }
    if(id_text>-1)
    {
        DrawTexture(_elyoko.ltexture[id_text],x,y,WHITE);
        //printf("[ELYOKO] : draw mesh id %d\n",id_mesh);
    }
    else
    {
        int ti = floor(GetTime()*60);
        if((ti%65)==0)
        printf("[ELYOKO] : texture %s not found\n",name);
    }

}
void LYO_ClearTextures()
{
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        if(_elyoko.ltexture_isload[i]==1)
        {
            LYO_DelTexture(_elyoko.ltexture_name[i]);
        }
    }
}
void LYO_Init()
{
    LM_Init();
    // LM_AddDirectionalLight((Vector3){0,1300,0},(Vector3){0,0,0},WHITE);
    LM_AddPointLight((Vector3){-1300,1300,0},(Vector3){0,0,0},WHITE);
    LM_AddPointLight((Vector3){1300,1300,0},(Vector3){0,0,0},LIGHTGRAY);
    LM_AddPointLight((Vector3){0,1300,1300},(Vector3){0,0,0},DARKGRAY);
    LM_AddPointLight((Vector3){0,1300,-1300},(Vector3){0,0,0},DARKGRAY);
}
void LYO_Free()
{
    for(int i=0;i<LYO_MAX_MODEL;i++)
    {
        if(_elyoko.lmodel_isload[i])
        UnloadModel(_elyoko.lmodel[i]);
    }
    for(int i=0;i<LYO_MAX_TEXTURE;i++)
    {
        if(_elyoko.ltexture_isload[i])
        UnloadTexture(_elyoko.ltexture[i]);
    }
    LM_Unload();
}
