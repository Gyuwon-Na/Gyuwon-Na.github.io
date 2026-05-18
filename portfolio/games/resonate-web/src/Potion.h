/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef POTION_H
#define POTION_H

#include <raylib.h>

extern bool IsPotionActive;

class Potion
{
public:
	void load();
	void draw();
	void unload();
	void ApplyPotionEffect();
	friend class Home;

private:
	Vector2 position = { 0, 70 };
	Texture2D potionTextures[6];
	void SetPotionEffectTimer(float duration);
	double PotionEffectDuration;
	double PotionStartTime;
	int PotionCount = 5;
};

#endif