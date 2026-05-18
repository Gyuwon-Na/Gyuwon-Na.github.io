/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef ATTACKPLAYER_H
#define ATTACKPLAYER_H

#include <raylib.h>

extern bool PlayerIsAttacking;

class AttackPlayer
{
public:
	void attack();

private:
	bool CollisionFront();
	bool CollisionBack();
	bool CollisionLeft();
	bool CollisionRight();
};

#endif