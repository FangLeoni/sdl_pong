#include "../utils/constants.h"
#include "../state.h"
#include "../player/player.h"
#include "../ball/ball.h"
#include "../scoreboard/scoreboard.h"

int aabb_collision (struct Player* player, struct Ball* ball) {
    return player->x < ball->x + ball->width &&
    player->x + player->width > ball->x &&
    player->y < ball->y + ball->height &&
    player->y + player->height > ball->y;
}

void collision_detection() {
    move_players();
    
    for(int i = 0; i < BALL_AMOUNT; i++) {
        struct Ball* current_ball = &state.balls[i];

        float nex_ballx = current_ball->x + (80.0f * state.delta_time * current_ball->x_speed);
        float nex_bally = current_ball->y + (80.0f * state.delta_time * current_ball->y_speed);

        for(int i = 0; i < PLAYER_AMOUNT; i++) {
            int out_of_bounds = nex_ballx >= WINDOW_WIDTH || nex_ballx < 0;

            if(out_of_bounds) {
                score();
                return;
            }
            
            int collision_test = aabb_collision(&state.players[i], current_ball);
            if(collision_test) {
                state.last_player = i;
                current_ball->x_speed = -current_ball->x_speed;
                break;
            }
        }

        if((nex_bally + current_ball->height) >= WINDOW_HEIGHT || nex_bally <= 0) {
            current_ball->y_speed = -current_ball->y_speed;
        }

        current_ball->x += (80.0f * state.delta_time * current_ball->x_speed);
        current_ball->y += (200.0f * state.delta_time * current_ball->y_speed);
    }
}