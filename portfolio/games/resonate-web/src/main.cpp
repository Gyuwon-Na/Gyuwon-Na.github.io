/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

AttackBoss attackboss;
AttackPlayer attackplayer;
BackGround background;
Boss boss;
Credit credit;
DrawBoss drawboss;
DrawPlayer drawplayer;
GameSetting setting;
Heart heart;
PlayerHeart playerheart;
BossHeart bossheart;
DigiPen digipen;
StarLink team;
Pattern1 pattern1;
Stone pattern2;
ShockWave pattern3;
Player player;
Potion potion;
Home home;

int state;
float timePlayed = 0.0f;
Music bg1;
Music bg2;
Sound sword;
bool bg1Playing = false;
bool bg2Playing = false;
bool wasPlayerAttacking = false;
int previousState = -1;

void load()
{
	digipen.load();
	team.load();
	background.load();
	heart.load();
	drawboss.load();
	drawplayer.load();
	credit.load();
	setting.load();
	pattern1.load();
	pattern2.load();
	pattern3.load();
	potion.load();
	home.load();
}

void unload()
{
	digipen.unload();
	team.unload();
	background.unload();
	heart.unload();
	credit.unload();
	drawboss.unload();
	drawplayer.unload();
	setting.unload();
	pattern1.unload();
	pattern2.unload();
	pattern3.unload();
	potion.unload();
	home.unload();
}

void game()
{
	if (player.MovingPosition.y >= boss.position.y + (boss.height - player.height)) //to consider a sense of distance
	{
		drawboss.draw_Moving();
		drawboss.draw_Attacking();
		drawplayer.draw_Moving();
		drawplayer.draw_Attacking();
	}
	else
	{
		drawplayer.draw_Moving();
		drawplayer.draw_Attacking();
		drawboss.draw_Moving();
		drawboss.draw_Attacking();
	}
	MovingCollide();
	attackboss.attack();
	attackplayer.attack();
	boss.Moving();
	player.Moving();
	pattern1.pattern1();
	pattern2.pattern2();
	pattern3.pattern3();
	heart.draw();
	potion.draw();
	home.EndWhenYouLose();
	home.EndWhenYouWin();
}

void stopAllAudio()
{
	if (bg1Playing)
	{
		StopMusicStream(bg1);
		bg1Playing = false;
	}
	if (bg2Playing)
	{
		StopMusicStream(bg2);
		bg2Playing = false;
	}
	StopSound(sword);
	wasPlayerAttacking = false;
}

void updateGameplayAudio(bool stopWhenLose)
{
	if (Win || (stopWhenLose && Lose))
	{
		stopAllAudio();
		return;
	}

	if (bgmchange)
	{
		if (bg1Playing)
		{
			StopMusicStream(bg1);
			bg1Playing = false;
		}
		if (!bg2Playing)
		{
			PlayMusicStream(bg2);
			bg2Playing = true;
		}
		UpdateMusicStream(bg2);
		timePlayed = (GetMusicTimePlayed(bg2) / GetMusicTimeLength(bg2));
	}
	else
	{
		if (bg2Playing)
		{
			StopMusicStream(bg2);
			bg2Playing = false;
		}
		if (!bg1Playing)
		{
			PlayMusicStream(bg1);
			bg1Playing = true;
		}
		UpdateMusicStream(bg1);
		timePlayed = (GetMusicTimePlayed(bg1) / GetMusicTimeLength(bg1));
	}

	if (timePlayed > 1.0f)
	{
		timePlayed = 0.0f;
	}

	if (PlayerIsAttacking && !wasPlayerAttacking)
	{
		PlaySound(sword);
	}
	wasPlayerAttacking = PlayerIsAttacking;
}

void updateDrawFrame()
{
	State currentState = (State)state;
	bool isGameplayState = currentState == State::start || currentState == State::cheat;
	bool wasGameplayState = previousState == (int)State::start || previousState == (int)State::cheat;

	if (isGameplayState && !wasGameplayState)
	{
		stopAllAudio();
	}
	else if (!isGameplayState && wasGameplayState)
	{
		stopAllAudio();
	}

	BeginDrawing();
	ClearBackground(BLACK);

	digipen.draw();
	background.draw();
	team.draw();

	if (UnloadDigiPenLogo && UnloadTeamLogo)
	{
		switch ((State)state)
		{
		case State::main:
			home.draw();
			break;

		case State::start:
			game();

			updateGameplayAudio(true);

			if (Lose || Win)
			{
				player.speed = 0;
				player.upspeed = 0;
				player.diagonalSpeed = 0;
				boss.speed = 0;

				PlayerIsAttacking = false;
				BossIsAttacking = false;
				ShieldExecuted = false;
			}
			if (IsKeyPressed(KEY_F1)) //change game mode into cheat mode
			{
				state = 3;
			}
			break;

		case State::exit:
			break;

		case State::cheat:
			game();

			updateGameplayAudio(false);

			if (Win)
			{
				player.speed = 0;
				player.upspeed = 0;
				player.diagonalSpeed = 0;
				boss.speed = 0;

				PlayerIsAttacking = false;
				BossIsAttacking = false;
				ShieldExecuted = false;
			}
			if (IsKeyPressed(KEY_F1)) //change cheat mode into game mode
			{
				state = 1;
			}
			break;

		case State::setting:
			setting.draw();
			break;

		case State::credit:
			credit.draw();
			break;
		}
	}

	EndDrawing();
	previousState = state;

#if defined(PLATFORM_WEB)
	if (state == 2)
	{
		emscripten_cancel_main_loop();
	}
#endif
}

int main()
{
	srand((unsigned int)time(NULL));
	InitWindow(window_width, window_height, "Resonate");
	InitAudioDevice();

	SetTargetFPS(windows_per_frame_second);

	bg1 = LoadMusicStream("musics/BGM_part1.mp3");
	bg2 = LoadMusicStream("musics/BGM_part2.mp3");
	sword = LoadSound("musics/sword.mp3");

	load();

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(updateDrawFrame, 0, 1);
#else
	while (!WindowShouldClose() && state != 2)
	{
		updateDrawFrame();
	}

	UnloadMusicStream(bg1);
	UnloadMusicStream(bg2);
	UnloadSound(sword);
	unload();
	CloseAudioDevice();
	CloseWindow();
#endif

	return 0;
}
