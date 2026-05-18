/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#ifndef ATTACKBOSS_H
#define ATTACKBOSS_H

#include <raylib.h>

extern bool BossIsAttacking;
extern bool AttackExecuted;
extern bool CollisionWithBoss;

class AttackBoss
{
public:
	void attack();
	void pattern1();
	void pattern2();
	int pattern;

private:
	float AttackFrameCounter = 0.0f;
	bool CollisionStingFront();
	bool CollisionStingLeft();
	bool CollisionStingRight();
	bool CollisionSwingFront();
	bool CollisionSwingLeft();
	bool CollisionSwingRight();
};
#endif