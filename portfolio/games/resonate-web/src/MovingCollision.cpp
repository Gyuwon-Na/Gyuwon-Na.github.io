/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Player player;
extern Boss boss;

bool MovingCollision = false;

Vector2 playerCenter;
Vector2 bossCenter;

void MovingCollide()
{
	PlayerRange = { player.MovingPosition.x + 30, player.MovingPosition.y + 50, 40, (float)(player.height / 2) };
	BossRange = { boss.position.x + 100, boss.position.y + 300, 100, 50 };

	playerCenter = { PlayerRange.x + PlayerRange.width / 2, PlayerRange.y + PlayerRange.height / 2 };
	bossCenter = { BossRange.x + BossRange.width / 2, BossRange.y + BossRange.height / 2 };

	float minDistanceX = PlayerRange.width / 2 + BossRange.width / 2;
	float minDistanceY = PlayerRange.height / 2 + BossRange.height / 2;

	float distanceX = fabs(playerCenter.x - bossCenter.x);
	float distanceY = fabs(playerCenter.y - bossCenter.y);

	bool collisionX = distanceX < minDistanceX;
	bool collisionY = distanceY < minDistanceY;

	if (collisionX && collisionY)
	{
		MovingCollision = true;

		float overlapX = minDistanceX - distanceX;
		float overlapY = minDistanceY - distanceY;

		if (overlapX > 0 && overlapY > 0) {
			if (overlapX > overlapY) {
				if (playerCenter.y > bossCenter.y) {
					player.position.y += overlapY;
				}
				else {
					player.position.y -= overlapY;
				}
			}
			else {
				if (playerCenter.x > bossCenter.x) {
					player.position.x += overlapX;
				}
				else {
					player.position.x -= overlapX;
				}
			}
		}
	}
	else
	{
		MovingCollision = false;
	}
}
