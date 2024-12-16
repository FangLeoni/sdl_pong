#pragma once

#include "../player/player.h"
#include "../ball/ball.h"

int aabb_collision (struct Player* player, struct Ball* ball);
void collision_detection(void);