/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern DrawBoss drawboss;
extern PlayerHeart playerheart;
extern Boss boss;
extern Player player;

bool BossIsAttacking = false;
bool AttackExecuted = false;
bool CollisionWithBoss = false;

bool AttackBoss::CollisionStingFront()
{
    Rectangle CollisionBoxStingF = { boss.position.x + 70, boss.position.y + 300, boss.width / 2 - 20, boss.height - 200 };
    Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

    return CheckCollisionRecs(CollisionBoxStingF, Player);
}

bool AttackBoss::CollisionStingLeft()
{
    Rectangle CollisionBoxStingL = { boss.position.x - 200, boss.position.y + 150, boss.width - 100, boss.height - 250 };
    Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

    return CheckCollisionRecs(CollisionBoxStingL, Player);
}

bool AttackBoss::CollisionStingRight()
{
    Rectangle CollisionBoxStingR = { boss.position.x + 300, boss.position.y + 150, boss.width - 100, boss.height - 250 };
    Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

    return CheckCollisionRecs(CollisionBoxStingR, Player);
}

bool AttackBoss::CollisionSwingFront()
{
    Rectangle CollisionBoxSwingF = { boss.position.x - 50, boss.position.y + 300, boss.width + 100, boss.height - 250 };
    Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

    return CheckCollisionRecs(CollisionBoxSwingF, Player);
}

bool AttackBoss::CollisionSwingRight()
{
    Rectangle CollisionBoxSwingR = { boss.position.x + 200, boss.position.y + 200, boss.width - 200, boss.height - 280 };
    Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

    return CheckCollisionRecs(CollisionBoxSwingR, Player);
}

bool AttackBoss::CollisionSwingLeft()
{
    Rectangle CollisionBoxSwingL = { boss.position.x - 30, boss.position.y + 200, boss.width - 200, boss.height - 280 };
    Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, player.width, player.height };

    return CheckCollisionRecs(CollisionBoxSwingL, Player);
}

void AttackBoss::pattern1()
{
    BossIsAttacking = true;

    if (!AttackExecuted) {
        if (boss.direction.y == 1) {
            AttackingBossState = 0;
            MovingBossState = 4;

            if (CollisionStingFront())
            {
                CollisionWithBoss = true;
            }

            AttackFrameCounter++;

            if (AttackFrameCounter >= drawboss.totalFrames_stingf * 5.45455) {
                AttackExecuted = true;
                AttackFrameCounter = 0.0f;
                CollisionWithBoss = false;
            }
        }
        else if (boss.direction.x == -1) {
            AttackingBossState = 1;
            MovingBossState = 4;

            if (CollisionStingLeft())
            {
                CollisionWithBoss = true;
            }

            AttackFrameCounter++;

            if (AttackFrameCounter > drawboss.totalFrames_sting * 6.0) {
                AttackExecuted = true;
                AttackFrameCounter = 0.0f;
                CollisionWithBoss = false;
            }
        }
        else if (boss.direction.x == 1) {
            AttackingBossState = 2;
            MovingBossState = 4;

            if (CollisionStingRight())
            {
                CollisionWithBoss = true;
            }

            AttackFrameCounter++;

            if (AttackFrameCounter > drawboss.totalFrames_sting * 6.0) {
                AttackExecuted = true;
                AttackFrameCounter = 0.0f;
                CollisionWithBoss = false;
            }
        }
    }

    if (playerheart.health == 0) {
        Lose = true;
        BossIsAttacking = false;
        CollisionWithBoss = false;
        GameFinish = true;
        AttackExecuted = true;
    }
}

void AttackBoss::pattern2()
{
    BossIsAttacking = true;

    if (!AttackExecuted) {
        if (boss.direction.y == 1) {
            AttackingBossState = 3;
            MovingBossState = 4;

            if (CollisionSwingFront())
            {
                CollisionWithBoss = true;
            }

            AttackFrameCounter++;

            if (AttackFrameCounter > drawboss.totalFrames_swingf * 6.0) {
                AttackExecuted = true;
                AttackFrameCounter = 0.0f;
                CollisionWithBoss = false;
            }
        }
        else if (boss.direction.x == 1)
        {
            AttackingBossState = 5;
            MovingBossState = 4;

            if (CollisionSwingRight())
            {
                CollisionWithBoss = true;
            }

            AttackFrameCounter++;

            if (AttackFrameCounter > drawboss.totalFrames_swing * 6.66667) {
                AttackExecuted = true;
                AttackFrameCounter = 0.0f;
                CollisionWithBoss = false;
            }
        }
        else if (boss.direction.x == -1)
        {
            AttackingBossState = 4;
            MovingBossState = 4;

            if (CollisionSwingLeft())
            {
                CollisionWithBoss = true;
            }

            AttackFrameCounter++;

            if (AttackFrameCounter > drawboss.totalFrames_swing * 6.66667) {
                AttackExecuted = true;
                AttackFrameCounter = 0.0f;
                CollisionWithBoss = false;
            }
        }
    }

    if (playerheart.health == 0) {
        Lose = true;
        BossIsAttacking = false;
        CollisionWithBoss = false;
        GameFinish = true;
        AttackExecuted = true;
    }
}

void AttackBoss::attack()
{
    if (frameSecond >= 180) {
        if (frameSecond % 420 == 0 && !GameFinish) {
            srand((unsigned int)time(NULL));
            pattern = rand() % 2 + 1;
            AttackExecuted = false;
            BossIsAttacking = true;
        }

        switch (pattern) {
        case 1:
            if (!GameFinish) {
                pattern1();

                if (playerheart.invincible && GetTime() - playerheart.invincibleTime > InvincibleDuration)
                {
                    playerheart.invincible = false;
                }

                if (AttackExecuted)
                {
                    BossIsAttacking = false;
                }

                if (CollisionWithBoss && !playerheart.invincible)
                {
                    playerheart.Decrease(10);
                    if (playerheart.health <= 0)
                    {
                        Lose = true;
                        GameFinish = true;
                    }
                }
            }
            else if (GameFinish)
            {
                AttackExecuted = true;
                CollisionWithBoss = false;
            }
            break;

        case 2:
            if (!GameFinish)
            {
                pattern2();

                if (playerheart.invincible && GetTime() - playerheart.invincibleTime > InvincibleDuration)
                {
                    playerheart.invincible = false;
                }

                if (AttackExecuted)
                {
                    BossIsAttacking = false;
                }

                if (CollisionWithBoss && !playerheart.invincible)
                {
                    playerheart.Decrease(15);
                    if (playerheart.health <= 0)
                    {
                        Lose = true;
                        GameFinish = true;
                    }
                }
            }
            else if (GameFinish)
            {
                AttackExecuted = true;
                CollisionWithBoss = false;
            }
            break;
        }
    }
}
