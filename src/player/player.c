#include "./player.h"
#include "../utils/constants.h"
#include "../state.h"
#include <SDL2/SDL.h>

void move_players(void) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    for(int i = 0; i < PLAYER_AMOUNT; i++) {
        if ( keys[state.players[i].UP] ) {
            state.players[i].y = state.players[i].y - (400.0f * state.delta_time);
        }
        if ( keys[state.players[i].DOWN] ) {
            state.players[i].y = state.players[i].y + (400.0f * state.delta_time);
        }
    }
}
