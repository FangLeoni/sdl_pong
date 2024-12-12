#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer =  NULL;

int last_frame_time = 0;
float delta_time = 0;

struct Ball {
    float x;
    float y;
    float width;
    float height;
    int score;
    int x_speed;
    int y_speed;
} ball;

struct Player {
    float x;
    float y;
    float width;
    float height;
    int score;
    int UP;
    int DOWN;
};

struct Player player1;
struct Player player2;

#define MAX_SCORE 4;

TTF_Font *font = NULL;

char str[42] = "";

int initialize_window(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(
        "NULL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if(!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        0
    );

    if(!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }
    
    TTF_Init();
    font = TTF_OpenFont("/usr/share/fonts/archcraft/normal-fonts/JetBrainsMono/JetBrainsMono-Regular.ttf", 24);
    if(!font) {
        fprintf(stderr, "Error creating FONT Renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void move_player(struct Player *player ) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if ( keys[player->UP] ) player->y -= 400 * delta_time;
    if ( keys[player->DOWN] ) player->y += 400 * delta_time;
}

SDL_Rect text_rect;
SDL_Texture *texture1;


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
    if(strcmp(str, "")) strcpy(str, "");

    strcat(str,"Score: Player 1 ");

    char p1_score[4];
    char p2_score[4];

    sprintf(p1_score, "(%d)", player1.score);
    strcat(str, p1_score);

    strcat(str, " vs Player 2 ");
    
    sprintf(p2_score, "(%d)", player2.score);
    strcat(str, p2_score);


    get_text_and_rect(renderer, (WINDOW_WIDTH / 2), 0, str, font, &texture1, &text_rect);
}

void collision_detection() {
    move_player(&player1);
    move_player(&player2);
    
    float nex_ballx = ball.x + (80.0f * delta_time * ball.x_speed);
    float nex_bally = ball.y + (80.0f * delta_time * ball.y_speed);

    int player1_scored = nex_ballx >= WINDOW_WIDTH;
    int player2_scored = (nex_ballx + ball.width) <= 0;

    if(player1_scored || player2_scored) {
        if(player1_scored) {
            player1.score += 1;
            ball.x_speed = 1;
        }
        if(player2_scored) {
            player2.score += 1;
            ball.x_speed = -1;
        }

        ball = (struct Ball){
            .x = WINDOW_WIDTH / 2,
            .y = 0,
            .width = 15,
            .height = 15,
            .x_speed = ball.x_speed,
            .y_speed = 1,
        };
        update_scoreboard();

        return;
    }

    if(
        (((player1.x + player1.width) > nex_ballx) &&
        (player1.y + player1.height > ball.y && ball.y + ball.height > player1.y))
            ||
        ((player2.x < (nex_ballx + ball.width)) && 
        (ball.y + ball.height > player2.y && player2.y + player2.height > ball.y))   
    ) {
        ball.x_speed = -ball.x_speed;
    }

    if((nex_bally + ball.height) >= WINDOW_HEIGHT || nex_bally <= 0) {
        ball.y_speed = -ball.y_speed;
    }


    ball.x += (80.0f * delta_time * ball.x_speed);
    ball.y += (200.0f * delta_time * ball.y_speed);
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
    }
    collision_detection();
}

void setup() {
    ball = (struct Ball){
        .x = WINDOW_WIDTH / 2,
        .y = 0,
        .width = 15,
        .height = 15,
        .x_speed = 1,
        .y_speed = 1,
    };
    player1 = (struct Player){
        .x = 40,
        .y = 20,
        .width = 10,
        .height = 80,
        .score = 0,
        .UP = SDL_SCANCODE_W,
        .DOWN = SDL_SCANCODE_S
    };
    player2 = (struct Player){
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

void update() {
    // Limit Frame rate
    // int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    // if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    //     SDL_Delay(time_to_wait);
    // }

    delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
}


void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture1, NULL, &text_rect);
    
    SDL_Rect ball_rect = { (int)ball.x, (int)ball.y, (int)ball.width, (int)ball.height };

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &ball_rect);


    SDL_Rect player1_rect = { (int)player1.x, (int)player1.y, (int)player1.width, (int)player1.height };

    SDL_SetRenderDrawColor(renderer, 0,255,255,255);
    SDL_RenderFillRect(renderer, &player1_rect);

    SDL_Rect player2_rect = { (int)player2.x, (int)player2.y, (int)player2.width, (int)player2.height };

    SDL_SetRenderDrawColor(renderer, 255,0,255,255);
    SDL_RenderFillRect(renderer, &player2_rect);

    SDL_RenderPresent(renderer);
}


void destroy_window() {
    SDL_DestroyTexture(texture1);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    game_is_running = initialize_window();

    setup();

    printf("Game is running...\n");
    while(game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}