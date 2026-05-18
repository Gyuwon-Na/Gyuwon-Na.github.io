/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern PlayerHeart playerheart;
extern Player player;

bool IsPotionActive = false;

void Potion::load()
{
    potionTextures[0] = LoadTexture("images/Potion_empty.png");
    potionTextures[1] = LoadTexture("images/Potion_1.png");
    potionTextures[2] = LoadTexture("images/Potion_2.png");
    potionTextures[3] = LoadTexture("images/Potion_3.png");
    potionTextures[4] = LoadTexture("images/Potion_4.png");
    potionTextures[5] = LoadTexture("images/Potion_5.png");
}

void Potion::draw()
{
    DrawTexture(potionTextures[PotionCount], position.x, position.y, WHITE);
}

void Potion::SetPotionEffectTimer(float duration)
{
    PotionEffectDuration = duration;
}

void Potion::ApplyPotionEffect()
{
    if (PotionCount > 0 && IsKeyPressed(KEY_LEFT_SHIFT) && frameSecond >= 180 && !GameFinish) {
        IsPotionActive = true;
        if (GameFinish)
        {
            IsPotionActive = false;
        }
        playerheart.Increase(16);
        PotionStartTime = GetTime();
        player.speed *= 0.7f;
        player.upspeed *= 0.7f;
        SetPotionEffectTimer(2.0);

        PotionCount--;
        DrawTexture(potionTextures[PotionCount], position.x, position.y, WHITE);
    }

    if (IsPotionActive) {
        float currentTime = GetTime();
        float elapsedTime = currentTime - PotionStartTime;

        if (elapsedTime >= PotionEffectDuration) {
            IsPotionActive = false;

            player.speed = 4.0f;
            player.upspeed = 2.5f;
        }
    }
}

void Potion::unload()
{
    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(potionTextures[i]);
    }
}