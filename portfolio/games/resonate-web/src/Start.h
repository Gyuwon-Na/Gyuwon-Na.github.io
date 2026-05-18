/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef START_H
#define START_H

#include <raylib.h>

extern bool Win;
extern bool Lose;
extern bool GameFinish;

class Home
{
public:
	void load();
	void draw();
	void EndWhenYouLose();
	void EndWhenYouWin();
	void Initialize();
	void unload();

private:
	Texture2D GameLogo;
	Texture2D StartIcon;
	Texture2D ExitIcon;
	Texture2D SettingIcon;
	Texture2D defeated;
	Texture2D takedown;
	int frameWidth;
	int frameHeight;
	int frameWidth_setting;
	int frameHeight_setting;
	int totalFrames = 2;
	Rectangle frameRec;
	Rectangle frameRec_setting;
};

#endif