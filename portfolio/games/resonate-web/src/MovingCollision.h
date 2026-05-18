/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef MOVINGCOLLISION_H
#define MOVINGCOLLISION_H

#include <raylib.h>

struct
{
	float x;
	float y;
	float width;
	float height;
} PlayerRange;

struct
{
	float x;
	float y;
	float width;
	float height;
} BossRange;

void MovingCollide();

#endif