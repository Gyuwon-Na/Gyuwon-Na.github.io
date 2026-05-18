/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef PATTERN1_H
#define PATTERN1_H

#include <raylib.h>
#include <time.h>
#include <stdlib.h>

extern bool ShieldExecuted;
extern bool BeforeStarFall;
extern bool BeforeShield;

class BeforeShieldAnim
{
public:
	friend class Pattern1;

private:
	Texture2D before;
	float frameWidth;
	float frameHeight;
	int currentFrame = 0;
	int framesCounter = 0;
	Rectangle frameRec;
	int totalFrames = 33;
	void load();
	void update();
	void draw();
	void unload();
};

class Star
{
public:
	friend class Pattern1;

private:
	Texture2D star;
	float frameWidth;
	float frameHeight;
	int currentFrame = 0;
	int framesCounter = 0;
	Rectangle frameRec;
	int totalFrames = 10;
	void load();
	void draw();
	void update();
	void unload();
};

class Shield
{
public:
	friend class Pattern1;

private:
	Texture2D shield;
	float frameWidth;
	float frameHeight;
	int currentFrame;
	int framesCounter;
	Rectangle frameRec;
	int totalFrames = 11;
	void load();
	void draw();
	void update();
	void unload();
	int shieldWidth = 200;
};

class AfterStarFallAnim
{
public:
	friend class Pattern1;

private:
	Texture2D after;
	float frameWidth;
	float frameHeight;
	int currentFrame_column = 0;
	int currentFrame_row = 0;
	int framesCounter = 0;
	Rectangle frameRec;
	int totalFrames_column = 6;
	int totalFrames_row = 5;

	void load();
	void update();
	void draw();
	void unload();
};

class Pattern1
{
public:
	void load();
	void pattern1();
	void unload();

private:
	void CollisionWithShield();
};

#endif