/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern PlayerHeart playerheart;
extern BossHeart bossheart;
extern Player player;
extern Boss boss;
extern Potion potion;

Vector2 StartIconPosition = { window_width / 2 - 200, 400 };
Vector2 ExitIconPosition = { window_width / 2 - 200, 500 };
Vector2 SettingIconPosition = { 50, window_height - 100 };

bool Win = false;
bool Lose = false;
bool GameFinish = false;

void Home::load()
{
	GameLogo = LoadTexture("images/Resonate.png");
	StartIcon = LoadTexture("images/Start_icon.png");
	ExitIcon = LoadTexture("images/Exit_icon.png");
	SettingIcon = LoadTexture("images/star_icon.png");
	defeated = LoadTexture("images/DEFEATED.png");
	takedown = LoadTexture("images/TAKEDOWN.png");

	frameWidth = (int)(StartIcon.width / totalFrames);
	frameHeight = StartIcon.height;

	frameRec = { 0, 0, (float)frameWidth, (float)frameHeight };

	frameWidth_setting = (int)(SettingIcon.width / totalFrames);
	frameHeight_setting = SettingIcon.height;

	frameRec_setting = { 0,0,(float)frameWidth_setting, (float)frameHeight_setting };
}

void Home::draw()
{
	if (UnloadTeamLogo)
	{
		DrawTexture(GameLogo, 0, 0, WHITE);

		if (GetMouseX() >= StartIconPosition.x + 120 && GetMouseX() <= StartIconPosition.x + 280
			&& GetMouseY() >= StartIconPosition.y && GetMouseY() < StartIconPosition.y + StartIcon.height)
		{
			frameRec.x = frameWidth;
			DrawTextureRec(StartIcon, frameRec, StartIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				state = 1;
			}
		}
		else
		{
			frameRec.x = 0;
			DrawTextureRec(StartIcon, frameRec, StartIconPosition, WHITE);
		}

		if (GetMouseX() >= ExitIconPosition.x + 120 && GetMouseX() <= ExitIconPosition.x + 280
			&& GetMouseY() >= ExitIconPosition.y && GetMouseY() < ExitIconPosition.y + ExitIcon.height)
		{
			frameRec.x = frameWidth;
			DrawTextureRec(ExitIcon, frameRec, ExitIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				state = 2;
			}
		}
		else
		{
			frameRec.x = 0;
			DrawTextureRec(ExitIcon, frameRec, ExitIconPosition, WHITE);
		}

		if (GetMouseX() >= SettingIconPosition.x && GetMouseX() <= SettingIconPosition.x + frameWidth_setting
			&& GetMouseY() >= SettingIconPosition.y && GetMouseY() <= SettingIconPosition.y + SettingIcon.height)
		{
			frameRec_setting.x = frameWidth_setting;
			DrawTextureRec(SettingIcon, frameRec_setting, SettingIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				state = 4;
			}
		}
		else
		{
			frameRec_setting.x = 0;
			DrawTextureRec(SettingIcon, frameRec_setting, SettingIconPosition, WHITE);
		}
	}
}

void Home::EndWhenYouLose()
{
	if (Lose)
	{
		Win = false;
		DrawTexture(defeated, 0, 0, WHITE);
		if (GetMouseX() >= ExitIconPosition.x + 120 && GetMouseX() <= ExitIconPosition.x + 280
			&& GetMouseY() >= ExitIconPosition.y && GetMouseY() < ExitIconPosition.y + ExitIcon.height)
		{
			frameRec.x = frameWidth;
			DrawTextureRec(ExitIcon, frameRec, ExitIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				state = 0;
				Initialize();
			}
		}
		else
		{
			frameRec.x = 0;
			DrawTextureRec(ExitIcon, frameRec, ExitIconPosition, WHITE);
		}
	}
}

void Home::EndWhenYouWin()
{
	if (Win)
	{
		Lose = false;
		DrawTexture(takedown, 0, 0, WHITE);
		if (GetMouseX() >= ExitIconPosition.x + 120 && GetMouseX() <= ExitIconPosition.x + 280
			&& GetMouseY() >= ExitIconPosition.y && GetMouseY() < ExitIconPosition.y + ExitIcon.height)
		{
			frameRec.x = frameWidth;
			DrawTextureRec(ExitIcon, frameRec, ExitIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				state = 0;
				Initialize();
			}
		}
		else
		{
			frameRec.x = 0;
			DrawTextureRec(ExitIcon, frameRec, ExitIconPosition, WHITE);
		}
	}
}

void Home::Initialize()
{
	Lose = false;
	GameFinish = false;
	Win = false;
	BossIsAttacking = false;
	PlayerIsAttacking = false;
	IsPotionActive = false;
	bgmchange = false;

	player.speed = 4.0f;
	player.upspeed = 2.5f;
	player.diagonalSpeed = player.speed * 0.717f;
	if (boss.direction.y == 1)
	{
		boss.speed = 0.7f;
	}
	else if (boss.direction.y == -1)
	{
		boss.speed = 1.2f;
	}
	frameSecond = 0;
	playerheart.health = 40;
	bossheart.health = 100;
	boss.direction = { 1,1 };
	player.direction = { 1,1 };
	boss.position = { window_width / 2 - 120 , 0 };
	player.position = { window_width / 2 - 100, window_height / 2 };
	potion.PotionCount = 5;
}

void Home::unload()
{
	UnloadTexture(StartIcon);
	UnloadTexture(ExitIcon);
	UnloadTexture(GameLogo);
	UnloadTexture(defeated);
	UnloadTexture(takedown);
}