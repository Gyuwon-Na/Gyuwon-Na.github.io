/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef DRAWBOSS_H
#define DRAWBOSS_H

#include <raylib.h>

class DrawBoss
{
public:
	void load();
	void draw_Moving();
	void draw_Attacking();
	void unload();
	friend class AttackBoss;

private:
	Texture2D front;
	Texture2D back;
	Texture2D left;
	Texture2D right;
	float frameWidth_moving;
	float frameHeight_moving;
	int currentFrame_moving = 0;
	int framesCounter_moving = 0;
	int totalFrames_moving = 4;
	Rectangle frameRec_moving;

	Texture2D sting_left;
	Texture2D sting_right;
	float frameWidth_sting;
	float frameHeight_sting;
	int currentFrame_sting = 0;
	int framesCounter_sting = 0;
	int totalFrames_sting = 10;
	Rectangle frameRec_sting;

	Texture2D sting_front;
	float frameWidth_stingf;
	float frameHeight_stingf;
	float currentFrame_stingf = 0.0f;
	float framesCounter_stingf = 0.0f;
	int totalFrames_stingf = 11;
	Rectangle frameRec_stingf;

	Texture2D swing_front;
	float frameWidth_swingf;
	float frameHeight_swingf;
	int currentFrame_swingf = 0;
	int framesCounter_swingf = 0;
	int totalFrames_swingf = 10;
	Rectangle frameRec_swingf;

	Texture2D swing_right;
	Texture2D swing_left;
	float frameWidth_swing;
	float frameHeight_swing;
	int currentFrame_swing = 0;
	int framesCounter_swing = 0;
	int totalFrames_swing = 9;
	Rectangle frameRec_swing;

	void update_Moving();
	void update_Sting();
	void update_StingF();
	void update_Swing();
	void update_SwingF();
};

#endif