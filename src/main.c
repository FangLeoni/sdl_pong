#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "./state.h"
#include "./physics/physics.h"
#include "./scoreboard/scoreboard.h"
#include "./window/window.h"

struct State state;

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            state.game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                state.game_is_running = FALSE;
            break;
    }
    collision_detection();
}

void update() {
    state.delta_time = (SDL_GetTicks() - state.last_frame_time) / 1000.0f;
    state.last_frame_time = SDL_GetTicks();
}

void render() {
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    render_scoreboard();
    
    for(int i = 0; i < BALL_AMOUNT; i++) {
        SDL_Rect ball_rect = { (int)state.balls[i].x, (int)state.balls[i].y, (int)state.balls[i].width, (int)state.balls[i].height };
        SDL_SetRenderDrawColor(state.renderer, 255,255,255,255);
        SDL_RenderFillRect(state.renderer, &ball_rect);
    }

    for(int i = 0; i < PLAYER_AMOUNT; i++) {
        SDL_Rect player2_rect = { (int)state.players[i].x, (int)state.players[i].y, (int)state.players[i].width, (int)state.players[i].height };
        SDL_SetRenderDrawColor(state.renderer, 255,255,255,255);
        SDL_RenderFillRect(state.renderer, &player2_rect);
    }

    SDL_RenderPresent(state.renderer);
}

void setup() {
    state.delta_time = 0.0f;
    state.last_frame_time = 0;
    state.game_is_running = 1;
    state.last_player = -1;

    state.balls[0] = (struct Ball){
        .x = WINDOW_WIDTH / 2,
        .y = 0,
        .width = 15,
        .height = 15,
        .x_speed = 1,
        .y_speed = 1,
    };

    state.players[0] = (struct Player){
        .x = 40,
        .y = 20,
        .width = 10,
        .height = 80,
        .score = 0,
        .UP = SDL_SCANCODE_W,
        .DOWN = SDL_SCANCODE_S
    };

    state.players[1] = (struct Player){
        .x = WINDOW_WIDTH - 40 - 10,
        .y = 20,
        .width = 10,
        .height = 80,
        .score = 0,
        .UP = SDL_SCANCODE_UP,
        .DOWN = SDL_SCANCODE_DOWN
    };

    update_scoreboard();
}

int main(int argc, char* args[]) {

    initialize_window();

    setup();

    printf("Game is running...\n");
    while(state.game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}