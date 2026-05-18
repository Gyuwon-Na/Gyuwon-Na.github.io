/*
*GAM100
*Rudy Castan, Haneul Lee, Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

extern Player player;
extern PlayerHeart playerheart;

void Stone::load()
{
    BigAttackStone = LoadTexture("images/stone_big.png");
    SmallAttackStone = LoadTexture("images/stone_small.png");
}

void Stone::update_B(int count)
{
    for (int i = 0; i < count; i++)
    {
        Vector2* bigPos = new Vector2{ float(rand() % (window_width - 169) + 60), float(rand() % (window_height / 2 - 99) + 100) };
        big_position.push_back(bigPos);
    }
}

void Stone::update_S(int count)
{
    for (int i = 0; i < count; i++)
    {
        Vector2* smallPos = new Vector2{ float(rand() % (window_width - 169) + 60), float(rand() % (window_height / 2 - 99) + 100) };
        small_position.push_back(smallPos);
    }
}

void Stone::draw_B()
{
    for (size_t i = 0; i < big_position.size(); i++)
    {
        DrawTexture(BigAttackStone, big_position[i]->x, big_position[i]->y, WHITE);
    }

    for (auto pos : big_position)
    {
        delete pos;
    }
    big_position.clear();
}

void Stone::draw_S()
{
    for (size_t i = 0; i < small_position.size(); i++)
    {
        DrawTexture(SmallAttackStone, small_position[i]->x, small_position[i]->y, WHITE);
    }

    for (auto pos : small_position)
    {
        delete pos;
    }
    small_position.clear();
}

void Stone::pattern2()
{
    if (StoneExecuted)
    {
        update_S(numbers_of_stone);
        update_B(numbers_of_stone);

        if (StoneFallEndTime_B <= 180.0f)
        {
            for (int i = static_cast<int>(big_position.size()) - 1; i >= 0; --i)
            {
                big_position[i]->y += speed * StoneFallEndTime_B;

                Rectangle stone_b = { big_position[i]->x, big_position[i]->y, 100, 100 };
                Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, 100, 100 };

                if (CheckCollisionRecs(stone_b, Player))
                {
                    playerheart.Decrease(12);
                    delete big_position[i];
                    big_position.erase(big_position.begin() + i);
                    StoneExecuted = false;
                }
                else if (big_position[i]->y > window_height - 110)
                {
                    delete big_position[i];
                    big_position.erase(big_position.begin() + i);
                }
            }
            draw_B();

            StoneFallEndTime_B++;
        }
        else
        {
            StoneFallEndTime_B = 0.0f;
            StoneExecuted = false;
        }

        if (StoneFallEndTime_S <= 180.0f)
        {
            for (int i = static_cast<int>(small_position.size()) - 1; i >= 0; --i)
            {
                small_position[i]->y += speed * StoneFallEndTime_S;

                Rectangle stone_s = { small_position[i]->x, small_position[i]->y, 100, 100 };
                Rectangle Player = { player.MovingPosition.x, player.MovingPosition.y, 100, 100 };

                if (CheckCollisionRecs(stone_s, Player))
                {
                    playerheart.Decrease(6);
                    delete small_position[i];
                    small_position.erase(small_position.begin() + i);
                    StoneExecuted = false;
                }
                else if (small_position[i]->y > window_height - 110)
                {
                    delete small_position[i];
                    small_position.erase(small_position.begin() + i);
                }
            }
            draw_S();

            StoneFallEndTime_S++;
        }
        else
        {
            StoneFallEndTime_S = 0.0f;
            StoneExecuted = false;
        }
    }
}

void Stone::unload()
{
    UnloadTexture(SmallAttackStone);
    UnloadTexture(BigAttackStone);
}
