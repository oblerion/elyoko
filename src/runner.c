#include "runner.h"
#include "rcamera.h"
#define CAMERA_MOVE_SPEED     0.09f
#define CAMERA_ROTATION_SPEED 0.03f
#define CAMERA_PAN_SPEED      0.2f
#define CAMERA_MOUSE_MOVE_SENSITIVITY                   0.028f     // TODO: it should be independant of framerate

bool _IsMoveInWorldPlane(int mode)
{
    return ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
}
bool _IsRotateAroundTarget(int mode)
{
    return ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
}
bool _IsLockView(int mode)
{
    return ((mode == CAMERA_FREE) || (mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
}
bool _IsRotateUp()
{
    return false;
}

struct srunner _runner={0};

//time
int rlua_deltatime(clua_state* L)
{
    lua_pushnumber(L,GetFrameTime());
    return 1;
}
//input
int rlua_btn(clua_state* L)
{
    int id = lua_tointeger(L,1);
    switch(id)
    {
        case 0:
            if(IsKeyDown(KEY_W) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)>0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 1:
            if(IsKeyDown(KEY_S) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)<0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 2:
            if(IsKeyDown(KEY_A) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)>0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 3:
            if(IsKeyDown(KEY_D) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)<0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 4:
        if(IsKeyDown(KEY_X) || GetGamepadButtonPressed()==GAMEPAD_BUTTON_RIGHT_FACE_LEFT){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        case 5:
        if(IsKeyDown(KEY_C) || GetGamepadButtonPressed()==GAMEPAD_BUTTON_RIGHT_FACE_DOWN){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        default:;
    }
    lua_pushboolean(L,0);
    return 1;
}

int rlua_btnp(clua_state* L)
{
    int id = lua_tointeger(L,1);
    switch(id)
    {
        case 0:
            if(IsKeyPressed(KEY_W) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)>0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 1:
            if(IsKeyPressed(KEY_S) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)<0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 2:
            if(IsKeyPressed(KEY_A) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)>0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 3:
            if(IsKeyPressed(KEY_D) || -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)<0){
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 4:
        if(IsKeyPressed(KEY_X) || GetGamepadButtonPressed()==GAMEPAD_BUTTON_RIGHT_FACE_LEFT){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        case 5:
        if(IsKeyPressed(KEY_C) || GetGamepadButtonPressed()==GAMEPAD_BUTTON_RIGHT_FACE_DOWN){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        default:;
    }
    lua_pushboolean(L,0);
    return 1;
}
int rlua_key(clua_state* L)
{
    int ik = lua_tointeger(L,1);
    char rb = IsKeyDown(ik);
    lua_pushboolean(L,rb);
    return 1;
}

int rlua_keyp(clua_state* L)
{
    int ik = lua_tointeger(L,1);
    char rb = IsKeyPressed(ik);
    lua_pushboolean(L,rb);
    return 1;
}
int rlua_mouse(clua_state* L)
{
    lua_pushinteger(L,GetMouseX());
    lua_pushinteger(L,GetMouseY());
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_LEFT));
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_MIDDLE));
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
    return 5;
}

//camera
int rlua_cameraX(clua_state* L)
{
    Vector3 pos = _runner.cam3d.position;
    lua_pushnumber(L,pos.x);
    return 1;
}
int rlua_cameraY(clua_state* L)
{
    Vector3 pos = _runner.cam3d.position;
    lua_pushnumber(L,pos.y);
    return 1;
}
int rlua_cameraZ(clua_state* L)
{
    Vector3 pos = _runner.cam3d.position;
    lua_pushnumber(L,pos.z);
    return 1;
}
int rlua_cameraMove(clua_state* L)
{
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);
    _runner.cam3d.position = Vector3Add(_runner.cam3d.position,(Vector3){x,y,z});
    return 0;
}
int rlua_cameraSetPos(clua_state* L)
{
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);
    _runner.cam3d.position = (Vector3){x,y,z};
    return 0;
}
int rlua_cameraRotate(clua_state* L)
{
    int mode = _runner.cam3d.projection;
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);

    CameraYaw(&_runner.cam3d,-y
    ,_IsRotateAroundTarget(mode));
    CameraPitch(&_runner.cam3d, -x,_IsLockView(mode),
    _IsRotateAroundTarget(mode), _IsRotateUp());
    CameraRoll(&_runner.cam3d,z);

    return 0;
}
int rlua_cameraMoveTarget(clua_state* L)
{
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);
    _runner.cam3d.target = Vector3Add(
        _runner.cam3d.target,
        (Vector3){x,y,z}
    );
    return 0;
}

int rlua_cameraSetTarget(clua_state* L)
{
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);
    _runner.cam3d.target = (Vector3){x,y,z};
    return 0;
}
int rlua_cameraLock(clua_state* L)
{
    char state = lua_toboolean(L,1);
    _runner.iscameralock = state;
    return 0;
}
//3d
int rlua_drawcube(clua_state* L)
{
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);
    float w = lua_tonumber(L,4);
    float h = lua_tonumber(L,5);
    float d = lua_tonumber(L,6);
    Color col = GetColor(lua_tointeger(L,7));
    Vector3 pos = (Vector3){x,y,z};
    DrawCube(pos,w,h,d,col);

    return 0;
}
int rlua_drawsphere(clua_state* L)
{
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float z = lua_tonumber(L,3);
    float r = lua_tonumber(L,4);
    Vector3 pos = (Vector3){x,y,z};
    Color col = GetColor(lua_tointeger(L,5));
    DrawSphere(pos,r,col);
    return 0;
}
int rlua_loadmodel(clua_state* L)
{
    LYO_LoadMesh(lua_tostring(L,1));
    return 0;
}
int rlua_delmodel(clua_state* L)
{
    LYO_DelMesh(lua_tostring(L,1));
    return 0;
}
int rlua_drawmodel(clua_state* L)
{
    const char* name = lua_tostring(L,1);
    float x = lua_tonumber(L,2);
    float y = lua_tonumber(L,3);
    float z = lua_tonumber(L,4);
    float rx = lua_tonumber(L,5);
    float ry = lua_tonumber(L,6);
    float rz = lua_tonumber(L,7);
    float scale = lua_tonumber(L,8);
    LYO_DrawMesh(name,x,y,z,rx,ry,rz,scale);
    return 0;
}
int rlua_clearmodels(clua_state* L)
{
    LYO_ClearMeshes();
    return 0;
}
int rlua_loadplanetexture(clua_state* L)
{
    const char* name = lua_tostring(L,1);
    Texture* t = LYO_GetTexture(name);
    Mesh mp = GenMeshPlane((float)t->width*0.1,(float)t->height*0.1,1,1);
    Model mo = LoadModelFromMesh(mp);
    //mo.materials[0].maps->color=(Color){0,0,0,0};
    mo.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *t;

    //SetMaterialTexture(&mo.materials[0],MATERIAL_MAP_DIFFUSE,*t);
    LYO_LoadMeshData(GetFileName(name),mo);
    return 0;
}

//2d
int rlua_color(clua_state* L)
{
    char r = lua_tointeger(L,1);
    char g = lua_tointeger(L,2);
    char b = lua_tointeger(L,3);
    if( lua_isinteger(L,4))
    {
        char a = lua_tointeger(L,4);
        lua_pushinteger(L,ColorToInt((Color){r,g,b,a}));
    }
    else
    {
        lua_pushinteger(L,ColorToInt((Color){r,g,b,255}));
    }
    return 1;

}
int rlua_text(clua_state* L)
{
    const char* str = lua_tostring(L,1);
    int x = lua_tointeger(L,2);
    int y = lua_tointeger(L,3);
    int scale = lua_tointeger(L,4);
    Color col = GetColor(lua_tointeger(L,5));
    DrawText(str,x,y,scale,col);
    return 0;
}
int rlua_drawpix(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    Color col = GetColor(lua_tointeger(L,3));
    DrawPixel(x,y,col);
    return 0;
}

int rlua_drawrect(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);
    Color col = GetColor(lua_tointeger(L,5));
    DrawRectangle(x,y,w,h,col);
    return 0;
}

int rlua_drawrectb(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);
    Color col = GetColor(lua_tointeger(L,5));
    DrawRectangleLines(x,y,w,h,col);
    return 0;
}
int rlua_drawcircle(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    float r = lua_tonumber(L,3);
    Color col = GetColor(lua_tointeger(L,4));
    DrawCircle(x,y,r,col);
    return 0;
}
int rlua_drawcircleb(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    float r = lua_tonumber(L,3);
    Color col = GetColor(lua_tointeger(L,4));
    DrawCircleLines(x,y,r,col);
    return 0;
}
int rlua_loadtexture(clua_state* L)
{
    const char* sfile = lua_tostring(L,1);
    LYO_LoadTexture(sfile);
    return 0;
}
int rlua_deltexture(clua_state* L)
{
    const char* name = lua_tostring(L,1);
    LYO_DelTexture(name);
    return 0;
}
int rlua_drawtexture(clua_state* L)
{
    const char* name = lua_tostring(L,1);
    float x = lua_tonumber(L,2);
    float y = lua_tonumber(L,3);
    LYO_DrawTexture(name,x,y);
    return 0;
}
int rlua_cleartextures(clua_state* L)
{
    LYO_ClearTextures();
    return 0;
}
void Runner_Init()
{
    _runner.cam3d = (Camera){
        (Vector3){ 0, 0, 0 }, // Camera position
        (Vector3){ 0.0f, 0.0f, 0.0f },      // Camera looking at point
        (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
        45.0f,                                // Camera field-of-view Y
        CAMERA_PERSPECTIVE
    };

    _runner.cam2d = (Camera2D){
        Vector2Zero(),
        Vector2Zero(),
        0,1
    };
    _runner.clua=CLUA();
    _runner.isload=1;


    // CLUA_setnumber(&_runner.clua,"BLACK",ColorToInt(BLACK));
    //time
    CLUA_setfunction(&_runner.clua,rlua_deltatime,"deltatime");
    // 3d
    CLUA_setfunction(&_runner.clua,rlua_loadmodel,"loadmodel");
    CLUA_setfunction(&_runner.clua,rlua_delmodel,"delmodel");
    CLUA_setfunction(&_runner.clua,rlua_drawmodel,"drawmodel");
    CLUA_setfunction(&_runner.clua,rlua_drawcube,"cube");
    CLUA_setfunction(&_runner.clua,rlua_drawsphere,"sphere");
    CLUA_setfunction(&_runner.clua,rlua_loadplanetexture,"loadplanetexture");
    CLUA_setfunction(&_runner.clua,rlua_clearmodels,"clearmodels");

    //CLUA_setfunction(&_runner.clua,rlua_drawplanetexture,"drawplanetexture");

    // 2d
    CLUA_setfunction(&_runner.clua,rlua_color,"color");
    CLUA_setfunction(&_runner.clua,rlua_text,"text");
    CLUA_setfunction(&_runner.clua,rlua_drawpix,"pix");
    CLUA_setfunction(&_runner.clua,rlua_drawrect,"rect");
    CLUA_setfunction(&_runner.clua,rlua_drawrectb,"rectb");
    CLUA_setfunction(&_runner.clua,rlua_drawcircle,"circle");
    CLUA_setfunction(&_runner.clua,rlua_drawcircleb,"circleb");
    CLUA_setfunction(&_runner.clua,rlua_loadtexture,"loadtexture");
    CLUA_setfunction(&_runner.clua,rlua_deltexture,"deltexture");
    CLUA_setfunction(&_runner.clua,rlua_drawtexture,"drawtexture");
    CLUA_setfunction(&_runner.clua,rlua_cleartextures,"cleartextures");


    //input
    CLUA_setfunction(&_runner.clua,rlua_key,"key");
    CLUA_setfunction(&_runner.clua,rlua_key,"keyp");
    CLUA_setfunction(&_runner.clua,rlua_btn,"btn");
    CLUA_setfunction(&_runner.clua,rlua_btnp,"btnp");
    CLUA_setfunction(&_runner.clua,rlua_mouse,"mouse");

    //camera
    CLUA_setfunction(&_runner.clua,rlua_cameraX,"camerax");
    CLUA_setfunction(&_runner.clua,rlua_cameraY,"cameray");
    CLUA_setfunction(&_runner.clua,rlua_cameraZ,"cameraz");
    CLUA_setfunction(&_runner.clua,rlua_cameraMove,"cameramove");
    CLUA_setfunction(&_runner.clua,rlua_cameraSetPos,"camerasetpos");
    CLUA_setfunction(&_runner.clua,rlua_cameraRotate,"camerarotate");
    CLUA_setfunction(&_runner.clua,rlua_cameraLock,"cameralock");
    CLUA_setfunction(&_runner.clua,rlua_cameraMoveTarget,"cameramovetarget");
    CLUA_setfunction(&_runner.clua,rlua_cameraSetTarget,"camerasettarget");


}
void Runner_DoFile(const char* slua)
{
    CLUA_dofile(&_runner.clua,slua);
}
void Runner_Draw2d()
{
    if(_runner.isload)
    {
        if(CLUA_iferror(&_runner.clua))
        {
            char* str = CLUA_geterror(&_runner.clua);
            BeginMode2D(_runner.cam2d);
            ClearBackground(RED);
            for(int i=0;i<strlen(str);i+=100)
            DrawText(TextSubtext(str,i,100),5,30,20,WHITE);
            EndMode2D();
        }
        else
        {
            BeginMode2D(_runner.cam2d);
            CLUA_callfunction(&_runner.clua,"ELYOKO2D");
            EndMode2D();
        }
    }
}

void ControlCamera(Camera *camera, int mode)
{
    bool moveInWorldPlane = _IsMoveInWorldPlane(mode);//= ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
    bool rotateAroundTarget = _IsRotateAroundTarget(mode);//((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool lockView = _IsLockView(mode);//((mode == CAMERA_FREE) || (mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool rotateUp = _IsRotateUp();//false;

    float mousedelta_x = ((float)GetMouseX()/(float)GetRenderWidth())-0.5;
    float mousedelta_y = ((float)GetMouseY()/(float)GetRenderHeight())-0.5;
    if(mousedelta_y>0.15 || mousedelta_y<-0.15)
        CameraPitch(camera, -CAMERA_ROTATION_SPEED*mousedelta_y*1.6, lockView, rotateAroundTarget, rotateUp);
    if(mousedelta_x>0.4 || mousedelta_x<-0.4)
        CameraYaw(camera, -CAMERA_ROTATION_SPEED*mousedelta_x*1.8, rotateAroundTarget);
    else if(mousedelta_x>0.15 || mousedelta_x<-0.15)
        CameraYaw(camera, -CAMERA_ROTATION_SPEED*mousedelta_x*1.6, rotateAroundTarget);

    if (IsKeyDown(KEY_W)) CameraMoveForward(camera, CAMERA_MOVE_SPEED, true);
    if (IsKeyDown(KEY_A)) CameraMoveRight(camera, -CAMERA_MOVE_SPEED,
    true);
    if (IsKeyDown(KEY_S)) CameraMoveForward(camera, -CAMERA_MOVE_SPEED, true);
    if (IsKeyDown(KEY_D)) CameraMoveRight(camera, CAMERA_MOVE_SPEED,
    true);

    if (IsKeyDown(KEY_DOWN)) CameraPitch(camera, -CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
    if (IsKeyDown(KEY_UP)) CameraPitch(camera, CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
    if (IsKeyDown(KEY_RIGHT)) CameraYaw(camera, -CAMERA_ROTATION_SPEED, rotateAroundTarget);
    if (IsKeyDown(KEY_LEFT)) CameraYaw(camera, CAMERA_ROTATION_SPEED, rotateAroundTarget);

    if (IsGamepadAvailable(0))
    {
        // Gamepad controller support
        CameraYaw(camera,
                    -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X))*CAMERA_MOUSE_MOVE_SENSITIVITY
                    , rotateAroundTarget);
        CameraPitch(camera, -(
            GetGamepadAxisMovement(0,GAMEPAD_AXIS_RIGHT_Y))*CAMERA_MOUSE_MOVE_SENSITIVITY
            ,lockView, rotateAroundTarget, rotateUp);
        CameraMoveForward(camera, -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)*CAMERA_MOVE_SPEED*1.5, moveInWorldPlane);
        CameraMoveRight(camera, GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)*CAMERA_MOVE_SPEED*1.5, moveInWorldPlane);
    }
}
void Runner_Draw3d()
{
    if(_runner.isload)
    {
        if(!CLUA_iferror(&_runner.clua))
        {
             BeginMode3D(_runner.cam3d);
             if(_runner.iscameralock==0)
             {
                ControlCamera(&_runner.cam3d,CAMERA_FIRST_PERSON);
             }
                DrawGrid(100,0.5f);
                CLUA_callfunction(&_runner.clua,"ELYOKO3D");
            EndMode3D();
        }
    }

}
void Runner_Free()
{
    if(_runner.isload)
        CLUA_free(&_runner.clua);
}
