#include "MainMenu.h"

MainMenu::MainMenu()
{
    this->menuBackground = new GameSprite(GameTexture::Load("romfs:/default/menu-background.jpg"));
    this->menuOsu = new GameSprite(GameTexture::Load("romfs:/default/menu-osu.png"));

    this->menuOsuScale = .4f;

    this->buttonPlay = new GameSprite(GameTexture::Load("romfs:/default/menu-button-play.png"));
    this->buttonOptions = new GameSprite(GameTexture::Load("romfs:/default/menu-button-options.png"));
    this->buttonExit = new GameSprite(GameTexture::Load("romfs:/default/menu-button-exit.png"));

    this->copyright = new GameText("Copyright peppy 2019, osu!3ds by Cyuubi");
    this->copyright->color = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
}

void MainMenu::Update()
{
    if (menuOsuScale >= .35f) menuOsuScale -= .001f;
    else menuOsuScale = .4f;
}

void MainMenu::DrawTop()
{
    menuBackground->Scale(.5f);
    menuBackground->Draw(200, 120);

    menuOsu->Scale(menuOsuScale);
    menuOsu->Draw(200, 120);
}

void MainMenu::DrawBottom()
{
    buttonPlay->Scale(0.6f);
    buttonPlay->Draw(80, 40);

    buttonOptions->Scale(0.6f);
    buttonOptions->Draw(80, 40 + 60);

    buttonExit->Scale(0.6f);
    buttonExit->Draw(80, 40 + 60 + 60);

    copyright->Draw(5, 220);
}