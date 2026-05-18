/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern PlayerHeart playerheart;
extern Player player;
extern Boss boss;

void ShockWave::load()
{
	wave = LoadTexture("images/ph1_shockwave.png");
	frameWidth = (float)(wave.width / totalFrames);
	frameHeight = wave.height;
	frameRec = { 0,0,frameWidth, frameHeight };
}

void ShockWave::update()
{
	framesCounter++;

	if (framesCounter >= 7.5)
	{
		currentFrame++;

		if (currentFrame == totalFrames / 2 + 2)
		{
			isPushing = true;
		}

		if (currentFrame == totalFrames - 1)
		{
			DuringShockWave = false;
		}

		framesCounter = 0;
	}
	frameRec.x = frameWidth * currentFrame;
	frameRec.y = 0;
}

void ShockWave::draw()
{
	update();
	DrawTexturePro(wave, frameRec, { 0,0,window_width,window_height }, { 0,0 }, 0.0f, WHITE);
}

void ShockWave::pattern3()
{
	if (DuringShockWave) {
		AttackExecuted = true;
		playerheart.invincible = true;

		if (hideTime == 0.0 && AttackExecuted == true)
		{
			hideTime = GetTime() + 1.0;
		}

		if (GetTime() >= hideTime && hideTime != 0.0)
		{
			pushAway(player.MovingPosition.x);
			draw();
		}

		boss.position.x = window_width / 2 - 120;
		boss.position.y = 150;
	}
	else
	{
		hideTime = 0.0;
		currentFrame = 0;
		isPushing = false;
	}
}

float ShockWave::pushAway(float movingPos)
{
	if (isPushing)
	{
		if (movingPos < window_width / 2 - 120)
		{
			player.direction.x = -1;
			movingPos += pushSpeed * player.direction.x;
		}
		else
		{
			player.direction.x = 1;
			movingPos += pushSpeed * player.direction.x;
		}

		player.position.x = movingPos;

		float currentTime = GetTime();

		if (currentTime - lastDecreaseTime >= 1.0f)
		{
			if (CheckCollisionCircleRec({ window_width / 2, window_height / 2 }, 350, { player.MovingPosition.x, player.MovingPosition.y, (float)(player.width), (float)(player.height) }))
			{
				playerheart.Decrease(40);
			}
			lastDecreaseTime = currentTime;
		}
		return player.position.x;
	}
}

void ShockWave::unload()
{
	UnloadTexture(wave);
}
