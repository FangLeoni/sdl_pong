#pragma once

struct ScoreBoard {
    char text[42];
    SDL_Rect text_rect;
    SDL_Texture *texture;
};

extern struct ScoreBoard scoreboard;

void update_scoreboard(void);
void render_scoreboard(void);
void destroy_scoreboard(void);
void score(void);