#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
    # include <unistd.h>
#elif defined _WIN32
    # include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

#include "types.h"
#include "config.h"
#include "board.h"

unsigned int player_is_rolling(const unsigned int current_player) {
    for (unsigned int each = 0; each < 4; ++each) {
        printf ( "\rPlayer %u is rolling%.*s   \b\b\b",current_player + 1, each, "...");
        fflush (stdout); //force printing as no newline in output
        sleep(1);
    }

    const unsigned int roll = _random_between(1,6);
    
    printf("\r Player %u has rolled a %u \n",current_player,roll);

    return roll;
}

void move_player(board board,const unsigned roll ,const unsigned int current_player) {
    player* element = board.players + current_player;

    const unsigned int x0 = element->position_x;
    const unsigned int x1 = x0 + roll;

    const unsigned int board_size_minus_1 =  board.board_size - 1;

    // Ensure that the new positions are in bounds of the board
    if(x1 > board_size_minus_1) {
        // If the player is at the end of the board (reached the final position), 
        // and the sum of their current position and the roll value exceeds the total number of spaces on the board, 
        // then invalidate the roll.
        if(element->position_y == board_size_minus_1) {
            printf("This move would take you past the finish line. Hence your move is invalidated");
            return;
        } else {
            element->position_x = board_size_minus_1;
            element->position_y += 1;
        }

    
    } else element->position_x = x1;

    switch (board.inner_board[element->position_x][element->position_y]->role){
        case is_ladder_start :
            // TODO :Move current player
            break;
        case is_snake_head :
            // TODO : Move current player
            break;
        default: break;
    }
}

unsigned int number_of_digits(const unsigned int number) {
    if (number < 10) return 1;
    if (number < 100) return 2;
    if (number < 1000) return 3;
    if (number < 10000) return 4;

    // This should not be reached
}

void print_board(const board board) {
    const unsigned int board_size_minus_1 = board.board_size - 1;
    const unsigned int maximum_number_of_digits = number_of_digits(board.inner_board[board_size_minus_1][board_size_minus_1]->label);
    // so "| $ N $ |"
    const unsigned int recommended_length_per_cell = maximum_number_of_digits + 8;

    const size_t buffer_size = recommended_length_per_cell * board_size_minus_1;
    char string_buffer[buffer_size];

    for(unsigned int i = 0;i < buffer_size;i++) {
        string_buffer[i] = '-';
    }

    for(int row = board.board_size - 1;row >= 0;row--) {
        for(int col = 0;col < board.board_size;col++) {
            const unsigned int label = board.inner_board[row][col]->label;
            const unsigned int padding = (recommended_length_per_cell - number_of_digits(label)) / 2;

            printf(
                "|%*s%u%*s|",
                padding," ",
                label,
                padding," "
            );
        }

        if(row != 0) printf("%s",string_buffer);
    }
}


int main() {
    printf("Snake and Ladder Game\n");
    
    config config = receive_config_from_user();

    // Add bot player if single player
    if(config.number_of_players == 1) config.number_of_players += 1;

    board board = generate_board_from_config(config);

    unsigned int round = 0;
    unsigned int current_player = 0;

    while(true) {
        printf("Round %u\n",round);
       
        print_board(board);

        // Keep on rolling if get 6s, but invalidate move for 3 consecutive sixes
        unsigned int roll , consecutive_sixes = 0;
        do {
            roll = player_is_rolling(current_player);

            if(roll == 6) consecutive_sixes += 1;

            if(consecutive_sixes == 3){
                printf("Three consecutive sixes! Move invalidated.\n");
                break;
            }
            else move_player(board,roll,current_player);
        }while(roll == 6);

        // Update Round and Player
        if(current_player == config.number_of_players - 1) {
            round += 1;
            current_player = 0;
        } else current_player += 1;
    }

    free_board(board);
    
    return 0;
}