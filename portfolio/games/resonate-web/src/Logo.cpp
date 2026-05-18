/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

bool UnloadDigiPenLogo = false;
bool UnloadTeamLogo = false;

Vector2 DigiPenLogoPosition = { 250, window_height / 2 - 100 };

void DigiPen::load()
{
	DigiPenLogo = LoadTexture("images/DigiPen.png");
}

void DigiPen::draw()
{
	if (!UnloadDigiPenLogo)
	{
		if (DigiPenLogoFadeIn && !DigiPenLogoFadeOut)
		{
			FadeInSecond++;

			Color fadeInColor = { 255, 255, 255, (unsigned char)(255 * (FadeInSecond / 120.0f)) };
			DrawTexture(DigiPenLogo, 250, window_height / 2 - 100, fadeInColor);

			if (fadeInColor.a >= 255)
			{
				fadeInColor.a = 255;
				DigiPenLogoFadeIn = false;
			}
		}
		else if (!DigiPenLogoFadeIn && !DigiPenLogoFadeOut)
		{
			FrameStaySecond += GetFrameTime();

			DrawTexture(DigiPenLogo, 250, window_height / 2 - 100, WHITE);

			if (FrameStaySecond >= 2.0f)
			{
				DigiPenLogoFadeOut = true;
			}
		}
		else if (DigiPenLogoFadeOut)
		{
			FadeOutSecond++;

			Color fadeOutColor = { 255, 255, 255, (unsigned char)(255 * (1.0f - (FadeOutSecond / 120.0f))) };
			DrawTexture(DigiPenLogo, 250, window_height / 2 - 100, fadeOutColor);

			if (fadeOutColor.a <= 0)
			{
				fadeOutColor.a = 0;
				UnloadDigiPenLogo = true;
				DigiPenLogoFadeOut = false;
			}
		}
	}
}

void DigiPen::unload()
{
	UnloadTexture(DigiPenLogo);
}

void StarLink::load()
{
	TeamLogo = LoadTexture("images/Project_Logo.png");
	frameWidth = (float)TeamLogo.width / totalFrames_column;
	frameHeight = (float)TeamLogo.height / totalFrames_row;
	frameRec = { 0,0,frameWidth, frameHeight };
}

void StarLink::update()
{
	framesCounter++;

	if (framesCounter > 6.026)
	{
		framesCounter = 0;

		if (currentFrame_column >= totalFrames_column - 2 && currentFrame_row >= totalFrames_row - 1)
		{
			TeamLogoFadeOut = true;
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

void StarLink::draw()
{
	if (UnloadDigiPenLogo)
	{
		update();

		if (TeamLogoFadeOut && !UnloadTeamLogo)
		{
			FrameSecond++;
			Color fadeOutColor = { 255, 255, 255, (unsigned char)(255 * (1.0f - (FrameSecond / 120.0f))) };
			DrawTextureRec(TeamLogo, frameRec, { 0, 0 }, fadeOutColor);
			if (fadeOutColor.a <= 0)
			{
				fadeOutColor.a = 0;
				UnloadTeamLogo = true;
			}
		}
		else if (!UnloadTeamLogo)
		{
			DrawTextureRec(TeamLogo, frameRec, { 0, 0 }, fadeOutColor);
		}
	}
}

void StarLink::unload()
{
	UnloadTexture(TeamLogo);
}