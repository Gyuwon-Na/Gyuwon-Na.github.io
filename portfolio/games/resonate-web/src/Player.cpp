/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Potion potion;
extern Boss boss;

void Player::Moving()
{
	if (frameSecond >= 180.0)
	{
		if (IsKeyDown(65) && IsKeyDown(87)) // a + w 
		{
			direction.x = -1;
			direction.y = -1;

			position.x += diagonalSpeed * direction.x;
			position.y += diagonalSpeed * direction.y;
		}
		else if (IsKeyDown(65) && IsKeyDown(83)) // a + s 
		{
			direction.x = -1;
			direction.y = 1;

			position.x += diagonalSpeed * direction.x;
			position.y += diagonalSpeed * direction.y;
		}
		else if (IsKeyDown(68) && IsKeyDown(87)) // d + w
		{
			direction.x = 1;
			direction.y = -1;

			position.x += diagonalSpeed * direction.x;
			position.y += diagonalSpeed * direction.y;
		}
		else if (IsKeyDown(68) && IsKeyDown(83)) // d + s
		{
			direction.x = 1;
			direction.y = 1;

			position.x += diagonalSpeed * direction.x;
			position.y += diagonalSpeed * direction.y;

		}
		else
		{
			if (IsKeyDown(65)) //a
			{
				direction.x = -1;
				direction.y = 0;

				position.x += speed * direction.x;

				if (!BossIsAttacking)
				{
					if (position.x >= boss.position.x + 200)
					{
						boss.direction.x = 1;
					}
					else if (position.x < boss.position.x + 200)
					{
						boss.direction.x = -1;
					}
				}
			}
			else if (IsKeyDown(68)) //d
			{
				direction.x = 1;
				direction.y = 0;

				position.x += speed * direction.x;

				if (!BossIsAttacking)
				{
					if (position.x >= boss.position.x + 200)
					{
						boss.direction.x = 1;
					}
					else if (position.x < boss.position.x + 200)
					{
						boss.direction.x = -1;
					}
				}
			}
			else if (IsKeyDown(83)) //s
			{
				direction.y = 1;
				direction.x = 0;

				position.y += speed * direction.y;

				if (!BossIsAttacking)
				{
					if (position.y >= boss.position.y + 50)
					{
						boss.direction.y = 1;
					}
					else if (position.y < boss.position.y + 200)
					{
						boss.direction.y = -1;
					}
				}
			}
			else if (IsKeyDown(87)) //w 
			{
				direction.y = -1;
				direction.x = 0;

				position.y += upspeed * direction.y;

				if (!BossIsAttacking)
				{
					if (position.y >= boss.position.y + 200)
					{
						boss.direction.y = 1;
					}
					else if (position.y < boss.position.y + 200)
					{
						boss.direction.y = -1;
					}
				}
			}
		}
	}
	else
	{
		if (IsKeyDown(65)) //a
		{
			if (position.x >= boss.position.x + 200)
			{
				boss.direction.x = 1;
			}
			else if (position.x < boss.position.x + 200)
			{
				boss.direction.x = -1;
			}
		}
		else if (IsKeyDown(68)) //d
		{
			if (position.x >= boss.position.x + 200)
			{
				boss.direction.x = 1;
			}
			else if (position.x < boss.position.x + 200)
			{
				boss.direction.x = -1;
			}
		}
		else if (IsKeyDown(83)) //s
		{
			if (position.y >= boss.position.y + 200)
			{
				boss.direction.y = 1;
			}
			else if (position.y < boss.position.y + 200)
			{
				boss.direction.y = -1;
			}
		}
		else if (IsKeyDown(87)) //w 
		{
			if (position.y >= boss.position.y + 400)
			{
				boss.direction.y = 1;
			}
			else if (position.y < boss.position.y + 400)
			{
				boss.direction.y = -1;
			}
		}
	}

	MovingPosition = { position.x, position.y };

	if (MovingPosition.x > window_width - 150)
	{
		MovingPosition.x = window_width - 150;
	}
	else if (MovingPosition.x < 100)
	{
		MovingPosition.x = 100;
	}

	if (MovingPosition.y > window_height - 100)
	{
		MovingPosition.y = window_height - 100;
	}
	else if (MovingPosition.y < 220)
	{
		MovingPosition.y = 220;
	}
	potion.ApplyPotionEffect();
}
