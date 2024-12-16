#pragma once

#include "./utils/constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player/player.h"
#include "ball/ball.h"

struct State {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    struct Player players[PLAYER_AMOUNT];
    int last_player;
    struct Ball balls[BALL_AMOUNT];
    int game_is_running;
    int last_frame_time;
    float delta_time;
};

// global state
extern struct State state;