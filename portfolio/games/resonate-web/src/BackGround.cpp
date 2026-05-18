/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

void BackGround::load()
{
	backgroundImg = LoadTexture("images/ph1_bg.png");
}

void BackGround::draw()
{
	if (UnloadDigiPenLogo)
	{
		DrawTexture(backgroundImg, 0, 0, WHITE);
	}
}

void BackGround::unload()
{
	UnloadTexture(backgroundImg);
}