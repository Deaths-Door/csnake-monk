#include "board.h"

board generate_board_from_config(config config) {
    // Calculate the board size based on the difficulty
    const unsigned int board_size = (1 + (config.difficulty - 1) * 0.15) * sqrt(config.number_of_players) * 10;

    srand(time(NULL));

    board board = {
        .board_size = board_size,
        .players = _create_players(config.number_of_players),
        .inner_board = _create_labeled_board(board_size)
    };

    _generate_snake_and_ladders(config,board);

    return board;
}

void free_board(board board) {
    // Free memory
    free(board.players);
    free(board.ladders);

    for (int i = 0; i < board.board_size; i++) {
        free(board.inner_board[i]);
    }

    free(board.inner_board);
}

players_array_pointer _create_players(const unsigned int number_of_players) {
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
        const struct player player = { 0, 0}; 
        players[i] = player;
    }

    return players;
}

board_cell_array_pointer _create_labeled_board(const unsigned int board_size) {
    board_cell** inner_board = malloc(board_size * sizeof(struct board_cell*));

    if(inner_board == NULL) {
        perror("malloc has failed");
        exit(1);
    }

    // Initalize board
    unsigned int count = 1;
    for (int i = 0; i < board_size; i++) {
        inner_board[i] = malloc(board_size * sizeof(struct board_cell));

        if(inner_board[i] == NULL) {
            perror("malloc has failed");
            exit(1);
        }

        for(int j = 0;j < board_size;j++) {
            const board_cell cell = { 
                .label = count,
                .role = none
            };

            inner_board[i][j] = cell;
            count += 1;
        }
    }
    
    return (board_cell_array_pointer) inner_board;
}

void _generate_snake_and_ladders(config config,board board) {
    // Calculate the number of entities on the grid
    const unsigned int adjusted_players_modifier = sqrt(config.number_of_players) * 10;
    const unsigned int number_of_ladders = abs(floor(config.difficulty * (board.board_size / 7.5)) - adjusted_players_modifier);

    board.ladders = _genereate_ladders(board,number_of_ladders);
    // TODO : Generate snakes but i dont know how
    const unsigned int number_of_snakes = floor(config.difficulty * (board.board_size / 10)) + adjusted_players_modifier;
}

unsigned int _random_between(const unsigned int min,const unsigned int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

point point_for_length(const board board,const point start,const unsigned int length) {
    const unsigned int direction = _random_between(0,7);

    unsigned int x = start.x;
    unsigned int y = start.y;

    const unsigned int half_length = length / 2;

    switch (direction){
        case 6:
            y += length;
            break;
        case 5:
            // Right diagonal (up and right)
            x += length;
            y += length;
            break;
        case 4:
            // Right mid diagonal (more up than right)
            x += half_length;
            y += length;
            break;
        case 3:
            // Right low diagonal (more right than up)
            x += length;
            y += half_length;
            break;
        case 2:
            // Left high diagonal (more up than left)
            x -= half_length;
            y += length;
            break;
        case 1:
            // Left mid diagonal (more left than up)
            x -= length;
            y += half_length;
            break;
        case 0:
            // Left low diagonal (more right than left)
            x -= length;
            y += 1; // No vertical movement for low left diagonal
            break;
    }

    const unsigned int board_size_minus_1 = board.board_size - 1;
    
    // keep in board range 
    if(y > board_size_minus_1) y = board_size_minus_1;
    if(x > board_size_minus_1) x = board_size_minus_1;

    const point point = {
        .x = x,
        .y = y,
    };

    return point;
}

bool all_neighbors_have_labels(const board board, const int start_x, const int start_y) {
    board.inner_board[start_x];
    board.inner_board[start_x][start_y];
    board.inner_board[start_x][start_y]->role;
    board.inner_board[start_x][start_y]->role != none;

    board.inner_board[start_x + 1];
    board.inner_board[start_x + 1][start_y];
    board.inner_board[start_x + 1][start_y]->role;
    board.inner_board[start_x + 1][start_y]->role != none;

    board.inner_board[start_x - 1];
    board.inner_board[start_x - 1][start_y];
    board.inner_board[start_x - 1][start_y]->role;
    board.inner_board[start_x - 1][start_y]->role != none;


    board.inner_board[start_x];
    board.inner_board[start_x][start_y  + 1];
    board.inner_board[start_x][start_y + 1]->role;
    board.inner_board[start_x][start_y + 1]->role != none;


    board.inner_board[start_x];
    board.inner_board[start_x][start_y - 1];
    board.inner_board[start_x][start_y - 1]->role;
    board.inner_board[start_x][start_y - 1]->role != none;

    return board.inner_board[start_x][start_y]->role != none && board.inner_board[start_x + 1][start_y]->role != none; //&&
          //  board.inner_board[start_x - 1][start_y]->role != none && board.inner_board[start_x][start_y - 1]->role != none &&
         //   board.inner_board[start_x][start_y + 1]->role != none;
}

point _draw_line_on_board(board board,const point start,const point suggested_end){
    unsigned int x0 = start.x;
    unsigned int y0 = start.y;
    const unsigned int x1 = suggested_end.x;
    const unsigned int y1 = suggested_end.y;

    const unsigned int dx = abs(x1 - x0);
    const int sx = (x0 < x1) ? 1 : -1;
    const int dy = -abs(y1-y0);
    const int sy = (y0 < y1) ? 1 : -1;

    int error = dx + dy;

    while(true) {
        // Do not place on ladder or the snake head
        // So either stop placing by breaking
        // Or set the role of this cell as ladder
        if(board.inner_board[x0][y1]->role == is_ladder 
            || board.inner_board[x0][y1]->role == is_ladder_start 
            || board.inner_board[x0][y1]->role == is_snake_head
            ) break;
        else board.inner_board[x0][y0]->role = is_ladder_start; // Create ladder here

        if(x0 == x1 && y0 == y1) break;

        const int e2 = 2 * error;

        if(e2 >= dy) {
            if(x0 == x1) break;

            error += dy;
            x0 += sx;
        }

        if(e2 <= dx) {
            if(y0 == y1) break;

            error += dx;
            y0 += sy;
        }
    }

    const point end = {
        .x = x0,
        .y = y0
    };

    return end;
}

point _suggested_end_point_for(const board board,const point start,const unsigned int calculated_length) {
    while(true) {
        const point suggested_end = point_for_length(board,start,calculated_length);

        // This ensures that the ladder doesn't end over , or in the way of an other ladder
        if(!all_neighbors_have_labels(board,suggested_end.x,suggested_end.y)) {
            return suggested_end;
        }
    }
}

ladders_array_pointer _genereate_ladders(const board board,const unsigned int count) {
    ladder* ladders = malloc(count * sizeof(ladder));
    
    unsigned int minimum_start_y = 0;
    unsigned int maximum_length = (int)(board.board_size * 0.5);

    unsigned int ladders_placed = 0;

    while(ladders_placed < count) {
        // board.board_size - 2 so that the ladder is not on the last column of the grid
        const unsigned int _start_x = _random_between(0,board.board_size - 2);
        const unsigned int _start_y = _random_between(minimum_start_y,board.board_size - 2);

        // This ensures that the ladder doesn't start over , or in the way of an other ladder
        if(!all_neighbors_have_labels(board,_start_x,_start_y)) {
            continue;
        }

        const unsigned int calculated_length = _random_between(2,maximum_length);
        
        const point start = {
            .x = _start_x,
            .y = _start_y,
        };

        const point suggested_end = _suggested_end_point_for(board,start,calculated_length);
        const point end = _draw_line_on_board(board,start,suggested_end);

        const ladder new_ladder = {
            .start = start,
            .end = end
        };
    
        // https://stackoverflow.com/a/77446759
        memcpy(&ladders[ladders_placed],&new_ladder, sizeof(ladder));

        // Increase the minimum start_y on every 3rd iteration, and hence decrease the maximum length
        if(ladders_placed %3 == 0) {
            minimum_start_y += 1;
            maximum_length -= 1;
        }

        ladders_placed += 1;
    }
    
    return ladders;
}