#include "../state.h"
#include "../scoreboard/scoreboard.h"
#include "./window.h"

int initialize_window(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    state.window = SDL_CreateWindow(
        "NULL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if(!state.window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    state.renderer = SDL_CreateRenderer(
        state.window,
        -1,
        0
    );

    if(!state.renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }
    
    TTF_Init();
    state.font = TTF_OpenFont("/usr/share/fonts/archcraft/normal-fonts/JetBrainsMono/JetBrainsMono-Regular.ttf", 24);
    if(!state.font) {
        fprintf(stderr, "Error creating FONT Renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void destroy_window(void) {
    destroy_scoreboard();

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}