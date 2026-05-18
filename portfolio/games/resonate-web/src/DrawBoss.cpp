/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Boss boss;

int MovingBossState;
int AttackingBossState;

void DrawBoss::load()
{
	front = LoadTexture("images/ph1_moving_front.png");
	back = LoadTexture("images/ph1_moving_back.png");
	left = LoadTexture("images/ph1_moving_left.png");
	right = LoadTexture("images/ph1_moving_right.png");
	frameWidth_moving = (float)(front.width / totalFrames_moving);
	frameHeight_moving = front.height;
	frameRec_moving = { 0, 0, frameWidth_moving, frameHeight_moving };

	sting_left = LoadTexture("images/ph1_sting_left.png");
	sting_right = LoadTexture("images/ph1_sting_right.png");
	frameWidth_sting = (float)(sting_left.width / totalFrames_sting);
	frameHeight_sting = sting_left.height;
	frameRec_sting = { 0, 0, frameWidth_sting, frameHeight_sting };

	sting_front = LoadTexture("images/ph1_sting_front.png");
	frameWidth_stingf = (float)(sting_front.width / totalFrames_stingf);
	frameHeight_stingf = sting_front.height;
	frameRec_stingf = { 0, 0, frameWidth_stingf, frameHeight_stingf };

	swing_front = LoadTexture("images/ph1_swing_front.png");
	frameWidth_swingf = (float)(swing_front.width / totalFrames_swingf);
	frameHeight_swingf = swing_front.height;
	frameRec_swingf = { 0,0,frameWidth_swingf, frameHeight_swingf };

	swing_left = LoadTexture("images/ph1_swing_left.png");
	swing_right = LoadTexture("images/ph1_swing_right.png");
	frameWidth_swing = (float)(swing_left.width / totalFrames_swing);
	frameHeight_swing = swing_left.height;
	frameRec_swing = { 0,0,frameWidth_swing, frameHeight_swing };
}

void DrawBoss::update_Moving()
{
	framesCounter_moving++;

	if (framesCounter_moving >= 15)
	{
		currentFrame_moving++;

		if (currentFrame_moving >= totalFrames_moving)
		{
			currentFrame_moving = 0;
		}

		framesCounter_moving = 0;
	}

	frameRec_moving.x = frameWidth_moving * currentFrame_moving;
	frameRec_moving.y = 0;
}

void DrawBoss::update_Sting()
{
	framesCounter_sting++;

	if (framesCounter_sting >= 6)
	{
		currentFrame_sting++;

		if (currentFrame_sting >= totalFrames_sting)
		{
			currentFrame_sting = 0;
		}

		framesCounter_sting = 0;
	}
	frameRec_sting.x = frameWidth_sting * currentFrame_sting;
	frameRec_sting.y = 0;
}

void DrawBoss::update_StingF()
{
	framesCounter_stingf++;

	if (framesCounter_stingf > 5.455)
	{
		currentFrame_stingf++;

		if (currentFrame_stingf >= totalFrames_stingf - 1) //to reduce frame error which happend because of an infinite decimal
		{
			currentFrame_stingf = 0;
		}

		framesCounter_stingf = 0;
	}

	frameRec_stingf.x = frameWidth_stingf * currentFrame_stingf;
	frameRec_stingf.y = 0;
}

void DrawBoss::update_SwingF()
{
	framesCounter_swingf++;

	if (framesCounter_swingf >= 6)
	{
		currentFrame_swingf++;

		if (currentFrame_swingf >= totalFrames_swingf)
		{
			currentFrame_swingf = 0;
		}

		framesCounter_swingf = 0;
	}
	frameRec_swingf.x = frameWidth_swingf * currentFrame_swingf;
	frameRec_swingf.y = 0;
}

void DrawBoss::update_Swing()
{
	framesCounter_swing++;

	if (framesCounter_swing > 6.666)
	{
		currentFrame_swing++;

		if (currentFrame_swing >= totalFrames_swing - 1) //to reduce frame error which happend because of an infinite decimal
		{
			currentFrame_swing = 0;
		}

		framesCounter_swing = 0;
	}
	frameRec_swing.x = frameWidth_swing * currentFrame_swing;
	frameRec_swing.y = 0;
}

void DrawBoss::draw_Moving()
{
	if (!BossIsAttacking && !CollisionWithBoss && !DuringShockWave && !ShieldExecuted)
	{
		if (IsKeyDown(65))
		{
			if (boss.direction.x == 1)
			{
				MovingBossState = 3;
				AttackingBossState = 6;

			}
			else if (boss.direction.x == -1)
			{
				MovingBossState = 2;
				AttackingBossState = 6;
			}
		}
		else if (IsKeyDown(68))
		{
			if (boss.direction.x == 1)
			{
				MovingBossState = 3;
				AttackingBossState = 6;
			}
			else if (boss.direction.x == -1)
			{
				MovingBossState = 2;
				AttackingBossState = 6;
			}
		}
		else if (IsKeyDown(83))
		{
			if (boss.direction.y == 1)
			{
				MovingBossState = 0;
				AttackingBossState = 6;
			}
			else if (boss.direction.y == -1)
			{
				MovingBossState = 1;
				AttackingBossState = 6;
			}
		}
		else if (IsKeyDown(87))
		{
			if (boss.direction.y == 1)
			{
				MovingBossState = 0;
				AttackingBossState = 6;

			}
			else if (boss.direction.y == -1)
			{
				MovingBossState = 1;
				AttackingBossState = 6;
			}
		}
		else
		{
			if (boss.direction.y == 1)
			{
				MovingBossState = 0;
				AttackingBossState = 6;
			}
			else if (boss.direction.y == -1)
			{
				MovingBossState = 1;
				AttackingBossState = 6;
			}
			else if (boss.direction.x == 1)
			{
				MovingBossState = 2;
				AttackingBossState = 6;
			}
			else if (boss.direction.x == -1)
			{
				MovingBossState = 3;
				AttackingBossState = 6;
			}
		}

		switch ((DrawMovingBoss)MovingBossState)
		{
		case::DrawMovingBoss::front:
			update_Moving();
			DrawTextureRec(front, frameRec_moving, { (float)boss.position.x + 50, (float)boss.position.y }, WHITE);
			break;

		case::DrawMovingBoss::back:
			update_Moving();
			DrawTextureRec(back, frameRec_moving, { (float)boss.position.x - 50, (float)boss.position.y - 20 }, WHITE);
			break;

		case::DrawMovingBoss::left:
			update_Moving();
			DrawTextureRec(left, frameRec_moving, { (float)boss.position.x, (float)boss.position.y }, WHITE);
			break;

		case::DrawMovingBoss::right:
			update_Moving();
			DrawTextureRec(right, frameRec_moving, { (float)boss.position.x, (float)boss.position.y }, WHITE);
			break;

		case::DrawMovingBoss::none:
			break;
		}
	}
}

void DrawBoss::draw_Attacking()
{
	if (!AttackExecuted)
	{
		switch ((DrawAttackingBoss)AttackingBossState)
		{
		case::DrawAttackingBoss::sting_front:
			update_StingF();
			if (boss.position.y >= window_width - boss.height) //To prevent boss from going out of the screen
			{
				DrawTextureRec(sting_front, frameRec_stingf, { boss.position.x - 100, boss.position.y - 70 }, WHITE);
			}
			else
			{
				DrawTextureRec(sting_front, frameRec_stingf, { boss.position.x - 100, boss.position.y - 50 }, WHITE);
			}
			break;

		case::DrawAttackingBoss::sting_left:
			update_Sting();
			DrawTextureRec(sting_left, frameRec_sting, { boss.position.x - boss.width, boss.position.y }, WHITE);
			break;

		case::DrawAttackingBoss::sting_right:
			update_Sting();
			if (boss.position.x >= window_width - boss.width) //To prevent boss from going out of the screen
			{
				DrawTextureRec(sting_right, frameRec_sting, { boss.position.x - 200, boss.position.y }, WHITE);
			}
			else
			{
				DrawTextureRec(sting_right, frameRec_sting, { boss.position.x, boss.position.y }, WHITE);
			}
			break;

		case::DrawAttackingBoss::swing_front:
			update_SwingF();
			if (boss.position.y >= window_height - boss.height) //To prevent boss from going out of the screen
			{
				DrawTextureRec(swing_front, frameRec_swingf, { boss.position.x - 200, boss.position.y - 300 }, WHITE);
			}
			else
			{
				DrawTextureRec(swing_front, frameRec_swingf, { boss.position.x - 200, boss.position.y - 250 }, WHITE);
			}
			break;

		case::DrawAttackingBoss::swing_left:
			update_Swing();
			DrawTextureRec(swing_left, frameRec_swing, { boss.position.x - 300, boss.position.y }, WHITE);
			break;

		case::DrawAttackingBoss::swing_right:
			update_Swing();
			DrawTextureRec(swing_right, frameRec_swing, { boss.position.x - 100, boss.position.y }, WHITE);
			break;

		case::DrawAttackingBoss::none:
			break;
		}
	}
}

void DrawBoss::unload()
{
	UnloadTexture(front);
	UnloadTexture(back);
	UnloadTexture(right);
	UnloadTexture(left);
	UnloadTexture(sting_front);
	UnloadTexture(sting_left);
	UnloadTexture(sting_right);
	UnloadTexture(swing_front);
	UnloadTexture(swing_left);
	UnloadTexture(swing_right);
}
