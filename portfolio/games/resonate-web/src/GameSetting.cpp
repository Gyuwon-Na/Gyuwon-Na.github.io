/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

Vector2 CreditIconPosition = { window_width / 2 - 200 , 500 };
Vector2 GoBackIconPosition = { -70, window_height - 130 };
Vector2 InstructionPosition = { window_width / 2 - 145, 100 };
Vector2 BossPosition = { window_width - 400, 150 };
Vector2 PlayerPosition = { 200, 350 };

void GameSetting::load()
{
	CreditIcon = LoadTexture("images/Credit_icon.png");
	GoBackIcon = LoadTexture("images/Exit_icon.png");
	Instruction = LoadTexture("images/Instruction.png");
	IntroHero = LoadTexture("images/IntroHero.png");
	IntroBoss = LoadTexture("images/IntroBoss.png");

	frameWidth = (int)(CreditIcon.width / totalFrames);
	frameHeight = CreditIcon.height;

	frameRec = { 0, 0, (float)frameWidth, (float)frameHeight };
}

void GameSetting::draw()
{
	DrawTexture(Instruction, InstructionPosition.x, InstructionPosition.y, WHITE);
	DrawTexture(IntroHero, PlayerPosition.x, PlayerPosition.y, WHITE);
	DrawTexture(IntroBoss, BossPosition.x, BossPosition.y, WHITE);

	if (GetMouseX() >= CreditIconPosition.x + 100 && GetMouseX() <= CreditIconPosition.x + 300
		&& GetMouseY() >= CreditIconPosition.y && GetMouseY() < CreditIconPosition.y + CreditIcon.height)
	{
		frameRec.x = frameWidth;
		DrawTextureRec(CreditIcon, frameRec, CreditIconPosition, WHITE);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			state = 5;
		}
	}
	else
	{
		frameRec.x = 0;
		DrawTextureRec(CreditIcon, frameRec, CreditIconPosition, WHITE);
	}

	if (GetMouseX() >= GoBackIconPosition.x + 110 && GetMouseX() <= GoBackIconPosition.x + GoBackIcon.width / 2 - 130
		&& GetMouseY() >= GoBackIconPosition.y && GetMouseY() <= GoBackIconPosition.y + GoBackIcon.height)
	{
		frameRec.x = frameWidth;
		DrawTextureRec(GoBackIcon, frameRec, GoBackIconPosition, WHITE);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			state = 0;
		}
	}
	else
	{
		frameRec.x = 0;
		DrawTextureRec(GoBackIcon, frameRec, GoBackIconPosition, WHITE);
	}
}

void GameSetting::unload()
{
	UnloadTexture(CreditIcon);
	UnloadTexture(GoBackIcon);
	UnloadTexture(Instruction);
	UnloadTexture(IntroBoss);
	UnloadTexture(IntroHero);
}
