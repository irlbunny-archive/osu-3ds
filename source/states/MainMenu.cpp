#include "MainMenu.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>

namespace states
{
    MainMenu::MainMenu()
    {
        this->background = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-background.jpg"));
        this->osu = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-osu.png"));
        
        this->osuScale = .4;

        this->osuFade = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-osu.png"));
        this->osuFade->Scale(.4);

        this->buttonPlay = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-button-play.png"));
        this->buttonOptions = new graphics::GameSprite(graphics::GameTexture::Load("romfs:/default/menu-button-options.png"));
    }
    
    void MainMenu::Update()
    {
        if (osuScale >= .375) osuScale -= .0005;
        else osuScale = .4;

        buttonPlay->Scale(.6);
        buttonOptions->Scale(.6);
    }
    
    void MainMenu::DrawTop()
    {
        background->Scale(.5);
        background->Draw(200, 120);

        osu->Scale(osuScale);
        osu->Draw(200, 120);

        osuFade->Draw(200, 120, C2D_Color32(0xFF * 0.5f, 0xFF * 0.5f, 0xFF * 0.5f, 0xFF * 0.5f));
    }
    
    void MainMenu::DrawBottom()
    {
        u16 buttonY = 80;
        buttonPlay->Draw(80, buttonY);

        buttonY += 60;
        buttonOptions->Draw(80, buttonY);
    }
}