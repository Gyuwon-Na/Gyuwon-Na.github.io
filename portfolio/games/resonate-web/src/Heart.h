/*
*GAM100
*Haneul Lee, Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef HEART_H
#define HEART_H

#include <raylib.h>
#include <string>
#include <iostream>

struct Hearts
{
	int x;
	int y;
	int health;
	Texture2D texture;
};

extern bool bgmchange;
extern bool pattern1start;
extern bool pattern3start;
extern bool DuringShockWave;
extern double InvincibleDuration;

class PlayerHeart
{
public:
	int health = 40;
	bool invincible = false;
	double invincibleTime = 0.0;
	void Decrease(int);
	void Increase(int);
};

class BossHeart
{
public:
	int health = 100;
	bool invincible = false;
	double invincibleTime = 0.0;
	void Decrease(int);
};

class Heart
{
public:
	void load();
	void draw();
	void unload();
};

#endif