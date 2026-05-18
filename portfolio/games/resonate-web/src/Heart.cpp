/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Stone pattern2;
extern Home home;
extern PlayerHeart playerheart;
extern Heart heart;

Hearts hearts[10];
Texture2D heartTextures[5];

bool bgmchange = false;
bool DuringShockWave = false;
bool pattern1start = false;
bool pattern3start = false;
double InvincibleDuration = 2.0;

void PlayerHeart::Decrease(int damage)
{
	if (((!invincible && BossIsAttacking) || ((!GameFinish && !Win && !Lose && frameSecond >= 180) && (pattern1start || pattern2.StoneExecuted || DuringShockWave))) && state != 3) {
		invincible = true;
		invincibleTime = GetTime();
		for (int i = 9; i >= 0; --i) {
			while (damage > 0 && hearts[i].health > 0) {
				--hearts[i].health;
				hearts[i].texture = heartTextures[hearts[i].health];
				health--;
				--damage;
			}

			if (damage == 0) {
				if (hearts[0].health == 0) {
					health = 0;
					Lose = true;
				}
				break;
			}
		}
		BossIsAttacking = false;
	}

	if (health <= 0) {
		health = 0;
		GameFinish = true;
		AttackExecuted = true;
		PlayerIsAttacking = false;
		Lose = true;
		home.EndWhenYouLose();
	}
}

void PlayerHeart::Increase(int healthIncrease)
{
	if (!GameFinish && state != 3)
	{
		health += healthIncrease;
		if (health > 40)
		{
			health = 40;
		}
		heart.draw();
	}
}

void BossHeart::Decrease(int damage)
{
	if (!invincible && PlayerIsAttacking && !GameFinish && !Win && !Lose)
	{
		invincible = true;
		invincibleTime = GetTime();
		health--;
		PlayerIsAttacking = false;

		if (health == 40 && !pattern2.StoneExecuted && !DuringShockWave)
		{
			pattern1start = true; //pattern 1 executed condition
		}

		if ((health == 80 || health == 20) && !pattern1start && !DuringShockWave)
		{
			pattern2.StoneExecuted = true; //pattern 2 executed condition
		}
		if (health == 60 && !pattern1start && !pattern2.StoneExecuted)
		{
			pattern3start = true; //pattern 3 executed condition
			bgmchange = true;
		}

		if (health <= 0)
		{
			health = 0;
			Win = true;
			GameFinish = true;
			AttackExecuted = true;
			BossIsAttacking = false;
			home.EndWhenYouWin();
		}
	}
}

void Heart::load()
{
	for (int i = 0; i < 5; ++i) {
		heartTextures[i] = LoadTexture(("images/Health_" + std::to_string(i) + ".png").c_str());
	}

	for (int i = 0; i < 10; ++i) {
		hearts[i].x = 20 + i * 40;
		hearts[i].y = 20;
		hearts[i].texture = heartTextures[4];
		hearts[i].health = 4;
	}
}

void Heart::draw()
{
	for (int i = 0; i < 10; ++i) {
		DrawTexture(hearts[i].texture, hearts[i].x, hearts[i].y, WHITE);
		if (playerheart.health == 0) {
			hearts[i].texture = heartTextures[0];
			hearts[i].health = 0;
		}
		if (playerheart.health % 4 == 0)
		{
			if (i < playerheart.health / 4)
			{
				hearts[i].health = 4;
				hearts[i].texture = heartTextures[4];
			}
		}
		else if (playerheart.health > 0 && playerheart.health % 4 != 0)
		{
			if (i <= playerheart.health / 4)
			{
				if (i < playerheart.health / 4)
				{
					hearts[i].health = 4;
					hearts[i].texture = heartTextures[4];
				}
				else if (i == playerheart.health / 4)
				{
					hearts[i].health = playerheart.health % 4;
					hearts[i].texture = heartTextures[playerheart.health % 4];
				}
			}
		}
		else if (playerheart.health % 4 == 1)
		{
			if (i < playerheart.health / 4)
			{
				hearts[i].health = 0;
				hearts[i].texture = heartTextures[0];
			}
		}
	}
}

void Heart::unload()
{
	for (int i = 0; i < 5; ++i)
	{
		UnloadTexture(heartTextures[i]);
	}
}

