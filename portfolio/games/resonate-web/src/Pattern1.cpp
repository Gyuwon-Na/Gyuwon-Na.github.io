/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Boss boss;
extern PlayerHeart playerheart;
extern Player player;

static double StarFallEndTime = 0.0;
static double ShieldTime = 0.0;
static double hideTime = 0.0;
static double BeforeShieldTime = 0.0;

Vector2 Position = { 0, 0 };
Vector2 ShieldPos = { 0,0 };

float point = 0;

extern bool BeforeStarFall = false;
extern bool BeforeShield = false;
extern bool ShieldExecuted = false;
bool AfterStarFall = false;
bool collision = true;

Star star;
Shield shield;
BeforeShieldAnim beforeshieldanim;
AfterStarFallAnim afterstarfallanim;

void BeforeShieldAnim::load()
{
	before = LoadTexture("images/beforeShield.png");

	frameWidth = (float)(before.width / totalFrames);
	frameHeight = before.height;

	frameRec = { 0,0,frameWidth, frameHeight };
}

void BeforeShieldAnim::update()
{
	framesCounter++;

	if (framesCounter > 5.455)
	{
		currentFrame++;

		if (currentFrame >= totalFrames)
		{
			BeforeShield = false;
			ShieldExecuted = true;
			currentFrame = 0;
		}

		framesCounter = 0;
	}

	frameRec.x = frameWidth * currentFrame;
	frameRec.y = 0;
}

void BeforeShieldAnim::draw()
{
	update();
	DrawTexturePro(before, frameRec, { 0,0,1280,720 }, { 0,0 }, 0.0f, WHITE);
}

void BeforeShieldAnim::unload()
{
	UnloadTexture(before);
}

void Star::load()
{
	star = LoadTexture("images/Star.png");

	frameWidth = (float)(star.width / totalFrames);
	frameHeight = star.height;

	frameRec = { 0, 0, frameWidth, frameHeight };
}

void Star::update()
{
	framesCounter++;

	if (framesCounter >= 6)
	{
		currentFrame++;

		if (currentFrame >= totalFrames)
		{
			currentFrame = 0;
		}

		framesCounter = 0;
	}

	frameRec.x = frameWidth * currentFrame;
	frameRec.y = 0;
}

void Star::draw()
{
	update();
	DrawTextureRec(star, frameRec, Position, WHITE);
}

void Star::unload()
{
	UnloadTexture(star);
}

void Shield::load()
{
	shield = LoadTexture("images/Shield.png");

	frameWidth = (float)(shield.width / totalFrames);
	frameHeight = shield.height;

	frameRec = { 0, 0, frameWidth, frameHeight };
}

void Shield::update()
{
	framesCounter++;

	if (framesCounter > 5.455)
	{
		currentFrame++;

		if (currentFrame >= totalFrames - 1)
		{
			currentFrame = 0;
		}
		framesCounter = 0;
	}
	frameRec.x = frameWidth * currentFrame;
	frameRec.y = 0;
}

void Shield::draw()
{
	update();
	ShieldPos = { Position.x - 50, Position.y - 10 };
	DrawTextureRec(shield, frameRec, ShieldPos, WHITE);
}

void Shield::unload()
{
	UnloadTexture(shield);
}

void AfterStarFallAnim::load()
{
	after = LoadTexture("images/AfterStarFall.png");
	frameWidth = (float)(after.width / totalFrames_column);
	frameHeight = (float)(after.height / totalFrames_row);

	frameRec = { 0, 0, frameWidth, frameHeight };
}

void AfterStarFallAnim::update()
{
	framesCounter++;

	if (framesCounter > 7.8260)
	{
		framesCounter = 0;

		if (currentFrame_column >= totalFrames_column - 1 && currentFrame_row >= totalFrames_row - 1)
		{
			ShieldExecuted = false;
			AfterStarFall = false;
			currentFrame_column = 0;
			currentFrame_row = 0;
			if (!collision)
			{
				playerheart.health = 0;
			}
		}
		else
		{
			currentFrame_column++;

			if (currentFrame_column >= totalFrames_column)
			{
				currentFrame_column = 0;
				currentFrame_row++;
			}
		}
	}

	frameRec.x = frameWidth * currentFrame_column;
	frameRec.y = frameHeight * currentFrame_row;
}

void AfterStarFallAnim::draw()
{
	update();
	DrawTextureRec(after, frameRec, { 0,0 }, WHITE);
}

void AfterStarFallAnim::unload()
{
	UnloadTexture(after);
}

void Pattern1::load()
{
	star.load();
	shield.load();
	beforeshieldanim.load();
	afterstarfallanim.load();
}

void Pattern1::CollisionWithShield()
{
	Rectangle CollisionBoxShield = { Position.x - 50, Position.y - 10, 200,200 };
	Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

	if (!CheckCollisionRecs(CollisionBoxShield, Player))
	{
		collision = false;
	}
}

void Pattern1::pattern1()
{
	srand((unsigned int)time(NULL));
	Position.x = rand() % (801) + window_width / 2 - 400;
	point = rand() % (window_height - 469) + 220;

	if (BeforeStarFall)
	{
		star.draw();

		if (Position.y < point)
		{
			Position.y += 3.0f; //gravity speed
			if (Position.y >= point)
			{
				point = Position.y;
			}
		}

		if (Position.y >= point && StarFallEndTime == 0.0)
		{
			StarFallEndTime = GetTime() + 1.0;
			BeforeShieldTime = GetTime() + 10.0;
			BeforeStarFall = false;
			BeforeShield = true;
		}
	}

	if (GetTime() >= BeforeShieldTime && BeforeShieldTime != 0.0)
	{
		if (BeforeShield)
		{
			playerheart.invincible = true;
			BossIsAttacking = true;
			AttackExecuted = true;
			beforeshieldanim.draw();
		}
	}

	if (ShieldExecuted)
	{
		playerheart.invincible = true;
		shield.draw();

		boss.position.x = window_width / 2 - 120;
		boss.position.y = 150;

		if (ShieldTime == 0)
		{
			ShieldTime = GetTime() + 1.0;
		}

		if (GetTime() >= ShieldTime && ShieldTime != 0.0)
		{
			AfterStarFall = true;
		}

		if (AfterStarFall)
		{
			playerheart.invincible = true;
			CollisionWithShield();
			afterstarfallanim.draw();
		}
	}

	if (!BeforeStarFall && !BeforeShield && !ShieldExecuted && !AfterStarFall)
	{
		hideTime = 0.0;
		StarFallEndTime = 0.0;
		ShieldTime = 0.0;
		Position.y = 0;
		collision = true;
	}
}

void Pattern1::unload()
{
	star.unload();
	shield.unload();
	beforeshieldanim.unload();
	afterstarfallanim.unload();
}
