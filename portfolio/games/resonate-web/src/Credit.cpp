/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

LeftIconImg left;
RightIconImg right;
ExitIconImg gohome;

int creditstate;

Vector2 LeftIconPosition = { 50 , window_height - 100 };
Vector2 RightIconPosition = { window_width - 100, window_height - 100 };
Vector2 GoSettingIconPosition = { -70, window_height - 130 };

void Credit::load()
{
	Credit1 = LoadTexture("images/Credit_Page1.png");
	Credit2 = LoadTexture("images/Credit_Page2.png");
	Credit3 = LoadTexture("images/Credit_Page3.png");
	left.LeftIcon = LoadTexture("images/Arrow_left.png");
	right.RightIcon = LoadTexture("images/Arrow_right.png");
	gohome.ExitIcon = LoadTexture("images/Exit_icon.png");

	left.frameWidth = (int)(left.LeftIcon.width / left.totalFrames);
	left.frameHeight = left.LeftIcon.height;
	left.frameRec = { 0, 0, (float)left.frameWidth, (float)left.frameHeight };

	right.frameWidth = (int)(right.RightIcon.width / right.totalFrames);
	right.frameHeight = right.RightIcon.height;
	right.frameRec = { 0, 0, (float)right.frameWidth, (float)right.frameHeight };

	gohome.frameWidth = (int)(gohome.ExitIcon.width / gohome.totalFrames);
	gohome.frameHeight = gohome.ExitIcon.height;
	gohome.frameRec = { 0, 0, (float)gohome.frameWidth, (float)gohome.frameHeight };
}

void Credit::draw()
{
	switch ((CreditState)creditstate)
	{
	case CreditState::page1:
		DrawTexture(Credit1, 0, 0, WHITE);
		if (GetMouseX() >= RightIconPosition.x && GetMouseX() <= RightIconPosition.x + right.RightIcon.width / 2
			&& GetMouseY() >= RightIconPosition.y && GetMouseY() <= RightIconPosition.y + right.RightIcon.height)
		{
			right.frameRec.x = right.frameWidth;
			DrawTextureRec(right.RightIcon, right.frameRec, RightIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				creditstate = 1;
			}
		}
		else
		{
			right.frameRec.x = 0;
			DrawTextureRec(right.RightIcon, right.frameRec, RightIconPosition, WHITE);
		}

		if (GetMouseX() >= GoSettingIconPosition.x + 110 && GetMouseX() <= GoSettingIconPosition.x + gohome.ExitIcon.width / 2 - 130
			&& GetMouseY() >= GoSettingIconPosition.y && GetMouseY() <= GoSettingIconPosition.y + gohome.ExitIcon.height)
		{
			gohome.frameRec.x = gohome.frameWidth;
			DrawTextureRec(gohome.ExitIcon, gohome.frameRec, GoSettingIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				state = 4;
			}
		}
		else
		{
			gohome.frameRec.x = 0;
			DrawTextureRec(gohome.ExitIcon, gohome.frameRec, GoSettingIconPosition, WHITE);
		}
		break;

	case CreditState::page2:
		DrawTexture(Credit2, 0, 0, WHITE);
		if (GetMouseX() >= RightIconPosition.x && GetMouseX() <= RightIconPosition.x + right.RightIcon.width / 2
			&& GetMouseY() >= RightIconPosition.y && GetMouseY() <= RightIconPosition.y + right.RightIcon.height)
		{
			right.frameRec.x = right.frameWidth;
			DrawTextureRec(right.RightIcon, right.frameRec, RightIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				creditstate = 2;
			}
		}
		else
		{
			right.frameRec.x = 0;
			DrawTextureRec(right.RightIcon, right.frameRec, RightIconPosition, WHITE);
		}

		if (GetMouseX() >= LeftIconPosition.x && GetMouseX() <= LeftIconPosition.x + left.LeftIcon.width / 2
			&& GetMouseY() >= LeftIconPosition.y && GetMouseY() <= LeftIconPosition.y + left.LeftIcon.height)
		{
			left.frameRec.x = left.frameWidth;
			DrawTextureRec(left.LeftIcon, left.frameRec, LeftIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				creditstate = 0;
			}
		}
		else
		{
			left.frameRec.x = 0;
			DrawTextureRec(left.LeftIcon, left.frameRec, LeftIconPosition, WHITE);
		}
		break;

	case CreditState::page3:
		DrawTexture(Credit3, 0, 0, WHITE);
		if (GetMouseX() >= LeftIconPosition.x && GetMouseX() <= LeftIconPosition.x + left.LeftIcon.width / 2
			&& GetMouseY() >= LeftIconPosition.y && GetMouseY() <= LeftIconPosition.y + left.LeftIcon.height)
		{
			left.frameRec.x = left.frameWidth;
			DrawTextureRec(left.LeftIcon, left.frameRec, LeftIconPosition, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				creditstate = 1;
			}
		}
		else
		{
			left.frameRec.x = 0;
			DrawTextureRec(left.LeftIcon, left.frameRec, LeftIconPosition, WHITE);
		}
		break;
	}
}

void Credit::unload()
{
	UnloadTexture(Credit1);
	UnloadTexture(Credit2);
	UnloadTexture(Credit3);
	UnloadTexture(left.LeftIcon);
	UnloadTexture(right.RightIcon);
	UnloadTexture(gohome.ExitIcon);
}