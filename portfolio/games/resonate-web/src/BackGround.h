/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <raylib.h>

class BackGround
{
public:
	void load();
	void draw();
	void unload();

public:
	Texture2D backgroundImg;
};

#endif