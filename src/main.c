#include "types.h"
#include "config.h"
#include "board.h"

int main() {
    printf("Snake and Ladder Game\n");
    
    config config = receive_config_from_user();
    board board = generate_board_from_config(config);

    unsigned int round = 0;
    unsigned int current_player = 0;

    while(true) {
        printf("Round %u",round);

        for(int i = 0;i< board.board_size;i++) {
            for(int j = 0;j <board.board_size;j++) {
                printf("| %u |",board.inner_board[i][j]->label);
            }
        }

        break;

        if(current_player == config.number_of_players - 1) current_player += 1;
    }

    return 0;
}