/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef CREDIT_H
#define CREDIT_H

#include <raylib.h>

class Credit
{
public:
	void load();
	void draw();
	void unload();

private:
	Texture2D Credit1;
	Texture2D Credit2;
	Texture2D Credit3;
};

class LeftIconImg
{
public:
	friend class Credit;

private:
	Texture2D LeftIcon;
	int frameWidth;
	int frameHeight;
	int totalFrames = 2;
	Rectangle frameRec;
};

class RightIconImg
{
public:
	friend class Credit;

private:
	Texture2D RightIcon;
	int frameWidth;
	int frameHeight;
	int totalFrames = 2;
	Rectangle frameRec;
};

class ExitIconImg
{
public:
	friend class Credit;

private:
	Texture2D ExitIcon;
	int frameWidth;
	int frameHeight;
	int totalFrames = 2;
	Rectangle frameRec;
};
#endif