/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef PATTERN3_H
#define PATTERN3_H

#include <raylib.h>

class ShockWave
{
public:
	void load();
	void pattern3();
	void unload();

private:
	Texture2D wave;
	float frameWidth;
	float frameHeight;
	float currentFrame = 0.0f;
	float framesCounter = 0.0f;
	Rectangle frameRec;
	int totalFrames = 16;

	double hideTime = 0.0;
	void update();
	void draw();

	float pushSpeed = 10.0f;
	bool isPushing = false;
	float pushAway(float);
	float lastDecreaseTime = 0.0f;
};

#endif