#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Read this https://stackoverflow.com/a/890846/20243803
unsigned int receive_input(const char *const label, validate validate) {
    
}

players_array_pointer create_players(const unsigned int number_of_players) {
    // Allocate memory for the players array
    //    - `config.number_of_players * sizeof(struct player_data)`: This expression
    //      calculates the total amount of memory needed to store the players array.
    //    - The return value of `malloc` is a pointer to the allocated memory
    //      block, or `NULL` if the allocation fails (there's not enough memory
    //      available).
    players_array_pointer players = malloc(number_of_players * sizeof(struct player));

    if(players == NULL) {
        perror("malloc has failed");
        exit(1);
    }

    for(int i = 0;i < number_of_players;i++) {
        players[i]->position_x = 0;
        players[i]->position_y = 0;
    }

    return players;
}


board_cell_array_pointer create_labeled_board(const unsigned int board_size) {
    board_cell_array_pointer inner_board = malloc(board_size * sizeof(struct board_cell*));

    if(inner_board == NULL) {
        perror("malloc has failed");
        exit(1);
    }

    // Initalize board
    unsigned int count = 1;
    for (int i = 0; i < board_size; i++) {
        struct board_cell* *const line = malloc(board_size * sizeof(struct board_cell));

        if(line == NULL) {
            perror("malloc has failed");
            exit(1);
        }

        for(int j = 0;j < board_size;j++) {
            line[j]->label =count;

            count += 1;
        }

        inner_board[i] = line;
    }
    
    return inner_board;
}

unsigned int random_between(const unsigned int min,const unsigned int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/*
unsigned int direction_for_entity() {
    return random_between(0,7);
}

// TODO : Replace this with a checker that checks for the maximum value i can have 
unsigned int maximum_length_for_entity(
    const struct board board,
    const unsigned int start_x,
    const unsigned int start_y,
    const unsigned int direction
) {
    unsigned int max_length;

    switch (direction) {
        case 0:  // Up
            max_length = start_y;  // Limited by starting row
            break;
        case 1:  // Down
            max_length = board.board_size - start_y - 1;  // Limited by remaining rows
            break;
        case 2:  // Right
            max_length = board.board_size - start_x - 1;  // Limited by remaining columns
            break;
        case 3:  // Left
            max_length = start_x;  // Limited by starting column
            break;
        case 4:  // Up-right
            max_length = min(start_y, board.board_size - start_x - 1);  // Limited by both
            break;
        case 5:  // Down-right
            max_length = min(board.board_size - start_y - 1, board.board_size - start_x - 1);  // Limited by both
            break;
        case 6:  // Up-left
            max_length = min(start_y, start_x);  // Limited by both
            break;
        case 7:  // Down-left
            max_length = min(board.board_size - start_y - 1, start_x);  // Limited by both
            break;
    }

    return max_length;
}*/


// Look at the psecudeocode here https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#:~:text=Bresenham's%20line%20algorithm%20is%20a,straight%20line%20between%20two%20points.
void draw_line(
    board_cell_array_pointer board,
    const struct point p1,
    const struct point p2
    ){
    const unsigned int dx = p2.x - p1.x;
    const unsigned int dy = p2.y - p1.y;
    const unsigned int _2dy = 2 * dy;
    const unsigned int _2dx = 2 * dx;

    unsigned int y = p1.y;
    unsigned int d = _2dy - dx;

    for(unsigned int x = p1.x;x < p2.x;x++) {
        // TODO : Plot assign it the role, but also check for collisions

        if(d > 0) {
            y += 1;
            d -= _2dx;
        }

        d += _2dy;
    }
}


ladders_array_pointer genereate_ladders(const struct board board,const unsigned int count) {
    ladders_array_pointer ladders = malloc(count * sizeof(struct ladder));

    for(int i = 0;i < count;i++) {
        const unsigned int start_x = random_between(0,board.board_size);
        const unsigned int start_y = random_between(start_x,board.board_size);


        //const unsigned int direction = direction_for_entity();
       // const unsigned int maximum_length = maximum_length_for_entity(board,start_x,start_y,direction);    
    
    }
}

void generate_snake_and_ladders(struct config config,struct board board) {
    // Calculate the number of entities on the grid
    const unsigned int adjusted_players_modifier = sqrt(config.number_of_players) * 10;
    const unsigned int number_of_snakes = floor(config.difficulty * (board.board_size / 10)) + adjusted_players_modifier;
    const unsigned int number_of_ladders = floor(config.difficulty * (board.board_size / 7.5)) - adjusted_players_modifier;

    board.ladders = genereate_ladders(board,number_of_ladders);
}

struct board generate_board_from_config(struct config config) {
 
    generate_snake_and_ladders(config,board);
}


void free_board(struct board board) {
    // Free memory
    free(board.players);
    free(board.ladders);

    for (int i = 0; i < board.board_size; i++) {
        free(board.inner_board[i]);
    }

    free(board.inner_board);
}

// TODO : Add colors and better sizing to terminal -- add bot playing
int main() {

    struct board board = generate_board_from_config(config);

    free_board(board);

    return 0;
}