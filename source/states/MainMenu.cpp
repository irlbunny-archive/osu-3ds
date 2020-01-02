#include "MainMenu.h"

namespace states
{
    MainMenu::MainMenu()
    {
        this->menuBackground = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-background.jpg"));
        this->menuOsu = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-osu.png"));

        this->menuOsuScale = .4;

        this->buttonPlay = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-button-play.png"));
        this->buttonOptions = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-button-options.png"));
        this->buttonExit = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-button-exit.png"));

        this->copyright = new graphics::GameText("Copyright peppy 2019, osu!3ds by Cyuubi");
        this->copyright->color = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    }
    
    void MainMenu::Update()
    {
        if (menuOsuScale >= .35) menuOsuScale -= .002;
        else menuOsuScale = .4;
    }
    
    void MainMenu::DrawTop()
    {
        menuBackground->Scale(.5);
        menuBackground->Draw(200, 120);

        menuOsu->Scale(menuOsuScale);
        menuOsu->Draw(200, 120);
    }
    
    void MainMenu::DrawBottom()
    {
        buttonPlay->Scale(.6);
        buttonPlay->Draw(80, 40);

        buttonOptions->Scale(.6);
        buttonOptions->Draw(80, 40 + 60);

        buttonExit->Scale(.6);
        buttonExit->Draw(80, 40 + 60 + 60);
        
        copyright->Draw(5, 220);
    }
}