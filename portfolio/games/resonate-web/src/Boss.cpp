/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern int frameSecond = 0;

void Boss::Moving()
{
	frameSecond++;

	if (!BossIsAttacking && !ShieldExecuted)
	{
		if (frameSecond >= 180.0)
		{
			position.x += speed * direction.x;
			position.y += speed * direction.y;

			if (position.x <= 20 || position.x >= window_width - width)
			{
				direction.x *= -1;

				if (position.x < 20)
				{
					position.x = 20;
				}
				else if (position.x > window_width - width)
				{
					position.x = window_width - width;
				}
			}

			if (position.y <= 0 || position.y > window_height - height)
			{
				direction.y *= -1;

				if (direction.y == 1)
				{
					speed = 0.7f;
				}
				else if (direction.y == -1)
				{
					speed = 1.2f; //Up as fast as possible to change direction because there is no back attack from the boss.
				}

				if (position.y < 0)
				{
					position.y = 0;
				}
				else if (position.y > window_height - height)
				{
					position.y = window_height - height;
				}
			}
		}
	}
}