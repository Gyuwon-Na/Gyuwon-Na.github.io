/*
*GAM100
*Rudy Castan, Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef PATTERN2_H
#define PATTERN2_H

#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Stone
{
public:
	bool StoneExecuted;
	void load();
	void pattern2();
	void unload();

private:
	Texture2D SmallAttackStone;
	Texture2D BigAttackStone;
	Rectangle stone_b;
	Rectangle stone_s;
	std::vector<Vector2*> big_position;
	std::vector<Vector2*> small_position;
	float StoneFallEndTime_S = 0.0f;
	float StoneFallEndTime_B = 0.0f;
	float speed = 3.5f;
	int numbers_of_stone = 3;

	void update_B(int);
	void update_S(int);
	void draw_S();
	void draw_B();
};

#endif