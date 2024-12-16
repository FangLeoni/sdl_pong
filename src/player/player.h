#pragma once

struct Player {
    float x;
    float y;
    float width;
    float height;
    int score;
    int UP;
    int DOWN;
};

void move_players(void);