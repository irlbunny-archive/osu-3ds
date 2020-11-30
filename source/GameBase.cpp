#include "GameBase.h"

GameBase::GameBase()
{
    romfsInit();

    gfxInitDefault();

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

    C2D_Prepare();

    this->top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    this->bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    this->mainMenu = new states::MainMenu();
}

GameBase::~GameBase()
{
    C2D_Fini();
    C3D_Fini();

    gfxExit();
}

void GameBase::Run()
{
    while (aptMainLoop())
    {
        Update();
        Draw();
    }
}

void GameBase::Update()
{
    mainMenu->Update();
}

void GameBase::Draw()
{
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    DrawTop();
    DrawBottom();

    C3D_FrameEnd(0);
}

void GameBase::DrawTop()
{
    C2D_TargetClear(top, C2D_Color32(0x00, 0x00, 0x00, 0x00));
    C2D_SceneBegin(top);

    mainMenu->DrawTop();
}

void GameBase::DrawBottom()
{
    C2D_TargetClear(bottom, C2D_Color32(0x40, 0x40, 0x40, 0xFF));
    C2D_SceneBegin(bottom);

    mainMenu->DrawBottom();
}