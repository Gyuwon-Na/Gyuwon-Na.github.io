/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "AttackBoss.h"
#include "AttackPlayer.h"
#include "BackGround.h"
#include "Boss.h"
#include "Credit.h"
#include "DrawBoss.h"
#include "DrawPlayer.h"
#include "GameSetting.h"
#include "Heart.h"
#include "Logo.h"
#include "MovingCollision.h"
#include "Pattern1.h"
#include "Pattern2.h"
#include "Pattern3.h"
#include "Player.h"
#include "Potion.h"
#include "Start.h"

constexpr int window_width = 1280;
constexpr int window_height = 720;
constexpr int windows_per_frame_second = 60;

extern int state;
enum class State
{
	main,
	start,
	exit,
	cheat,
	setting,
	credit,
};

extern int creditstate;
enum class CreditState
{
	page1,
	page2,
	page3
};

extern int MovingBossState;
enum class DrawMovingBoss
{
	front,
	back,
	left,
	right,
	none
};

extern int MovingPlayerState;
enum class DrawMovingPlayer
{
	front,
	back,
	left,
	right,
	none
};

extern int AttackingPlayerState;
enum class DrawAttackingPlayer
{
	front,
	back,
	left,
	right,
	none
};

extern int AttackingBossState;
enum class DrawAttackingBoss
{
	sting_front,
	sting_left,
	sting_right,
	swing_front,
	swing_left,
	swing_right,
	none
};