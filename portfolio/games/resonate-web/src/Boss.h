/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef BOSS_H
#define BOSS_H

#include <raylib.h>

extern int frameSecond;

struct Boss
{
public:
	Vector2 position = { 1280 / 2 - 120 , 0 };
	Vector2 direction = { 1,1 };
	void Moving();
	int width = 400; //min bossImg width
	int height = 350; //min bossImg height
	float speed = 1.0f;
};

#endif