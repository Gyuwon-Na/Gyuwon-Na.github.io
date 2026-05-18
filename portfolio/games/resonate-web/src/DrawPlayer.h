/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef DRAWPLAYER_H
#define DRAWPLAYER_H

#include <raylib.h>

class DrawPlayer
{
public:
	void load();
	void draw_Moving();
	void draw_Attacking();
	void unload();

private:
	Texture2D front;
	Texture2D back;
	Texture2D left;
	Texture2D right;
	float frameWidth_moving;
	float frameHeight_moving;
	int currentFrame_moving = 0;
	int framesCounter_moving = 0;
	Rectangle frameRec_moving;
	int totalFrames_moving = 4;

	Texture2D attackF;
	Texture2D attackL;
	Texture2D attackB;
	Texture2D attackR;
	float frameWidth_attack;
	float frameHeight_attack;
	int currentFrame_attack = 0;
	int framesCounter_attack = 0;
	Rectangle frameRec_attack;
	int totalFrames_attack = 6;

	void update_Moving();
	void update_Attacking();
};

#endif