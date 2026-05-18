/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern AttackPlayer attackplayer;
extern Player player;

int MovingPlayerState;
int AttackingPlayerState;

void DrawPlayer::load()
{
	front = LoadTexture("images/Hero_front.png");
	back = LoadTexture("images/Hero_back.png");
	left = LoadTexture("images/Hero_left.png");
	right = LoadTexture("images/Hero_right.png");
	frameWidth_moving = (float)(front.width / totalFrames_moving);
	frameHeight_moving = front.height;
	frameRec_moving = { 0, 0, frameWidth_moving, frameHeight_moving };

	attackF = LoadTexture("images/Hero_front_attack.png");
	attackL = LoadTexture("images/Hero_left_attack.png");
	attackB = LoadTexture("images/Hero_back_attack.png");
	attackR = LoadTexture("images/Hero_right_attack.png");
	frameWidth_attack = (float)(attackF.width / totalFrames_attack);
	frameHeight_attack = attackF.height;
	frameRec_attack = { 0,0,frameWidth_attack,frameHeight_attack };
}

void DrawPlayer::update_Moving()
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

void DrawPlayer::update_Attacking()
{
	framesCounter_attack++;

	if (framesCounter_attack >= 10)
	{
		currentFrame_attack++;

		if (pattern3start)
		{
			DuringShockWave = true;
			pattern3start = false;
		}

		if (pattern1start)
		{
			BeforeStarFall = true;
			pattern1start = false;
		}

		if (currentFrame_attack >= totalFrames_attack)
		{
			currentFrame_attack = 0;
			PlayerIsAttacking = false;
		}

		framesCounter_attack = 0;
	}

	frameRec_attack.x = frameWidth_attack * currentFrame_attack;
	frameRec_attack.y = 0;
}

void DrawPlayer::draw_Attacking()
{
	if (PlayerIsAttacking)
	{
		attackplayer.attack();
		switch ((DrawAttackingPlayer)AttackingPlayerState)
		{
		case::DrawAttackingPlayer::front:
			update_Attacking();
			DrawTextureRec(attackF, frameRec_attack, { (float)player.MovingPosition.x - 50, (float)player.MovingPosition.y - 50 }, WHITE);
			break;

		case::DrawAttackingPlayer::back:
			update_Attacking();
			DrawTextureRec(attackB, frameRec_attack, { (float)player.MovingPosition.x - 50, (float)player.MovingPosition.y - 50 }, WHITE);
			break;

		case::DrawAttackingPlayer::left:
			update_Attacking();
			DrawTextureRec(attackL, frameRec_attack, { (float)player.MovingPosition.x - 50, (float)player.MovingPosition.y - 50 }, WHITE);
			break;

		case::DrawAttackingPlayer::right:
			update_Attacking();
			DrawTextureRec(attackR, frameRec_attack, { (float)player.MovingPosition.x - 50, (float)player.MovingPosition.y - 50 }, WHITE);
			break;

		case::DrawAttackingPlayer::none:
			break;
		}
	}
}

void DrawPlayer::draw_Moving()
{
	if (PlayerIsAttacking == false)
	{
		if (IsKeyDown(65))
		{
			MovingPlayerState = 2;
			AttackingPlayerState = 4;
		}
		else if (IsKeyDown(68))
		{
			MovingPlayerState = 3;
			AttackingPlayerState = 4;
		}
		else if (IsKeyDown(83))
		{
			MovingPlayerState = 0;
			AttackingPlayerState = 4;
		}
		else if (IsKeyDown(87))
		{
			MovingPlayerState = 1;
			AttackingPlayerState = 4;
		}
		else
		{
			if (player.direction.y == 1)
			{
				MovingPlayerState = 0;
				AttackingPlayerState = 4;
			}
			else if (player.direction.y == -1)
			{
				MovingPlayerState = 1;
				AttackingPlayerState = 4;
			}
			else if (player.direction.x == 1)
			{
				MovingPlayerState = 3;
				AttackingPlayerState = 4;
			}
			else if (player.direction.x == -1)
			{
				MovingPlayerState = 2;
				AttackingPlayerState = 4;
			}
		}

	}

	switch ((DrawMovingPlayer)MovingPlayerState)
	{
	case::DrawMovingPlayer::front:
		update_Moving();
		DrawTextureRec(front, frameRec_moving, { (float)player.MovingPosition.x, (float)player.MovingPosition.y }, WHITE);
		break;

	case::DrawMovingPlayer::back:
		update_Moving();
		DrawTextureRec(back, frameRec_moving, { (float)player.MovingPosition.x, (float)player.MovingPosition.y }, WHITE);
		break;

	case::DrawMovingPlayer::left:
		update_Moving();
		DrawTextureRec(left, frameRec_moving, { (float)player.MovingPosition.x, (float)player.MovingPosition.y }, WHITE);
		break;

	case::DrawMovingPlayer::right:
		update_Moving();
		DrawTextureRec(right, frameRec_moving, { (float)player.MovingPosition.x, (float)player.MovingPosition.y }, WHITE);
		break;

	case::DrawMovingPlayer::none:
		break;
	}
}

void DrawPlayer::unload()
{
	UnloadTexture(front);
	UnloadTexture(back);
	UnloadTexture(left);
	UnloadTexture(right);
	UnloadTexture(attackF);
	UnloadTexture(attackL);
	UnloadTexture(attackB);
	UnloadTexture(attackR);
}
