/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <iostream>

class Player
{
public:
	Vector2 position = { 1280 / 2 - 100, 720 / 2 };
	Vector2 direction;
	Vector2 MovingPosition;
	float speed = 4.0f;
	float upspeed = 2.5f;
	void Moving();
	int width = 100;
	int height = 100;
	float diagonalSpeed = speed * 0.7071f;
};

#endif