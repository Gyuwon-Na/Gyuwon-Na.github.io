/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Player player;
extern BossHeart bossheart;
extern Boss boss;

bool PlayerIsAttacking = false;

bool AttackPlayer::CollisionFront()
{
	Rectangle Boss = { boss.position.x, boss.position.y, boss.width, boss.height };
	Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y + player.height / 2, player.width, player.height };

	return CheckCollisionRecs(Boss, Player);
}

bool AttackPlayer::CollisionBack()
{
	Rectangle Boss = { boss.position.x, boss.position.y, boss.width, boss.height };
	Rectangle Player = { player.MovingPosition.x , player.MovingPosition.y - player.height / 2, player.width, player.height };

	return CheckCollisionRecs(Boss, Player);
}

bool AttackPlayer::CollisionLeft()
{
	Rectangle Boss = { boss.position.x, boss.position.y, boss.width, boss.height };
	Rectangle Player = { player.MovingPosition.x - player.width / 2, player.MovingPosition.y - player.height / 2, player.width, player.height };

	return CheckCollisionRecs(Boss, Player);
}

bool AttackPlayer::CollisionRight()
{
	Rectangle Boss = { boss.position.x, boss.position.y, boss.width, boss.height };
	Rectangle Player = { player.MovingPosition.x + player.width / 2, player.MovingPosition.y, player.width, player.height };

	return CheckCollisionRecs(Boss, Player);
}

void AttackPlayer::attack()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && frameSecond >= 180)
	{
		PlayerIsAttacking = true;
	}

	if (PlayerIsAttacking == true && frameSecond >= 180)
	{
		if (player.direction.y == 1)
		{
			AttackingPlayerState = 0;
			MovingPlayerState = 4;

			if (bossheart.invincible && GetTime() - bossheart.invincibleTime > InvincibleDuration)
			{
				bossheart.invincible = false;
			}

			if (CollisionFront() && !bossheart.invincible)
			{
				bossheart.Decrease(1);
			}
		}
		else if (player.direction.y == -1)
		{
			AttackingPlayerState = 1;
			MovingPlayerState = 4;

			if (bossheart.invincible && GetTime() - bossheart.invincibleTime > InvincibleDuration)
			{
				bossheart.invincible = false;
			}

			if (CollisionBack() && !bossheart.invincible)
			{
				bossheart.Decrease(1);
			}
		}
		else if (player.direction.x == 1)
		{
			AttackingPlayerState = 3;
			MovingPlayerState = 4;

			if (bossheart.invincible && GetTime() - bossheart.invincibleTime > InvincibleDuration)
			{
				bossheart.invincible = false;
			}

			if (CollisionRight() && !bossheart.invincible)
			{
				bossheart.Decrease(1);
			}
		}
		else if (player.direction.x == -1)
		{
			AttackingPlayerState = 2;
			MovingPlayerState = 4;

			if (bossheart.invincible && GetTime() - bossheart.invincibleTime > InvincibleDuration)
			{
				bossheart.invincible = false;
			}

			if (CollisionLeft() && !bossheart.invincible)
			{
				bossheart.Decrease(1);
			}
		}
	}
}