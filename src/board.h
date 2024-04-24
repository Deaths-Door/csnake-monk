#pragma once
#ifndef CSNAKE_LADDER_BOARD_H
#define CSNAKE_LADDER_BOARD_H

#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "config.h"

board generate_board_from_config(config config);

players_array_pointer _create_players(const unsigned int number_of_players);
board_cell_array_pointer _create_labeled_board(const unsigned int board_size);

void _generate_snake_and_ladders(config config,board board);
ladders_array_pointer _genereate_ladders(const board board,const unsigned int count);

#endif