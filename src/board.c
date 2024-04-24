#include "board.h"

board generate_board_from_config(config config) {
    // Calculate the board size based on the difficulty
    const unsigned int board_size = (1 + (config.difficulty - 1) * 0.15) * sqrt(config.number_of_players) * 10;

    srand(time(NULL));

    board board = {
        .board_size = board_size,
        .players = create_players(config.number_of_players),
        .inner_board = create_labeled_board(board_size)
    };

    _generate_snake_and_ladders(config,board);

    return board;
}

void _generate_snake_and_ladders(config config,board board) {
    // Calculate the number of entities on the grid
    const unsigned int adjusted_players_modifier = sqrt(config.number_of_players) * 10;
    const unsigned int number_of_snakes = floor(config.difficulty * (board.board_size / 10)) + adjusted_players_modifier;
    const unsigned int number_of_ladders = floor(config.difficulty * (board.board_size / 7.5)) - adjusted_players_modifier;

    board.ladders = _genereate_ladders(board,number_of_ladders);
}

ladders_array_pointer _genereate_ladders(const board board,const unsigned int count) {
    TODO
}