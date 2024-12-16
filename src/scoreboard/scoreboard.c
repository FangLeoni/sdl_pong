#include "../state.h"
#include "./scoreboard.h"

struct ScoreBoard scoreboard;

void get_text_and_rect(
    SDL_Renderer *renderer,
    int x,
    int y,
    char *text,
    TTF_Font *font,
    SDL_Texture **texture,
    SDL_Rect *rect
) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderUTF8_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x - (text_width / 2);
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

void update_scoreboard() {
    if(strcmp(scoreboard.text, "")) strcpy(scoreboard.text, "");

    for(int i = 0; i < PLAYER_AMOUNT; i++) {
        char score_string[4];
        strcat(scoreboard.text,"Player ");
        sprintf(score_string, "(%i)", state.players[i].score);
        strcat(scoreboard.text, score_string);
        if(i < PLAYER_AMOUNT - 1) strcat(scoreboard.text," vs ");
    }

    get_text_and_rect(state.renderer, (WINDOW_WIDTH / 2), 0, scoreboard.text, state.font, &scoreboard.texture, &scoreboard.text_rect);
}

void render_scoreboard() {
    SDL_RenderCopy(state.renderer, scoreboard.texture, NULL, &scoreboard.text_rect);
}

void destroy_scoreboard(void) {
    SDL_DestroyTexture(scoreboard.texture);
    TTF_Quit();
}

void score(void) {
    if(state.last_player >= 0) {
        state.players[state.last_player].score += 1;
        state.last_player = -1;
    }

    for(int i = 0; i < BALL_AMOUNT; i++) {
        state.balls[i] = (struct Ball){
            .x = WINDOW_WIDTH / 2,
            .y = 0,
            .width = 15,
            .height = 15,
            .x_speed = 1,
            .y_speed = 1,
        };
    }
    
    update_scoreboard();
}