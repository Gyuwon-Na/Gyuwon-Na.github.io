/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef GAMESETTING_H
#define GAMESETTING_H

#include <raylib.h>

class GameSetting
{
public:
	void load();
	void draw();
	void unload();

private:
	Texture2D CreditIcon;
	Texture2D GoBackIcon;
	Texture2D Instruction;
	Texture2D IntroHero;
	Texture2D IntroBoss;
	int frameWidth;
	int frameHeight;
	int totalFrames = 2;
	Rectangle frameRec;
};

#endif