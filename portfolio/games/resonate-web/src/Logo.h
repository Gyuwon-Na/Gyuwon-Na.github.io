/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef LOGO_H
#define LOGO_H

#include <raylib.h>

class DigiPen
{
public:
	void load();
	void draw();
	void unload();

private:
	Texture2D DigiPenLogo;

	bool DigiPenLogoFadeIn = true;
	bool DigiPenLogoFadeOut = false;
	float FadeInSecond = 0.0f;
	float FrameStaySecond = 0.0f;
	float FadeOutSecond = 0.0f;
};

class StarLink
{
public:
	void load();
	void draw();
	void unload();

	friend class Home;
	friend class BackGround;

private:
	Texture2D TeamLogo;
	float frameWidth;
	float frameHeight;
	int currentFrame_column = 0;
	int currentFrame_row = 0;
	int framesCounter = 0;
	Rectangle frameRec;
	int totalFrames_column = 6;
	int totalFrames_row = 5;

	float FrameSecond = 0.0f;
	bool TeamLogoFadeOut = false;

	void update();
	Color fadeOutColor = { 255, 255, 255, (unsigned char)(255 * (1.0f - (FrameSecond / 120.0f))) };
};

extern bool UnloadDigiPenLogo;
extern bool UnloadTeamLogo;
#endif