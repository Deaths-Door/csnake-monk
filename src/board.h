/**
 * @file CSnakeLadderBoard.h
 * @brief Header file containing functions for board generation and manipulation in Snake and Ladder.
 *
 * This header file defines functions for generating a game board, creating players, and placing snakes and ladders on the board based on a provided game configuration. It also includes helper functions for point manipulation and random number generation.
 */
#pragma once
#ifndef CSNAKE_LADDER_BOARD_H
#define CSNAKE_LADDER_BOARD_H

#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "config.h"

/**
 * @brief Function to generate a game board based on a provided configuration.
 * @param config The configuration structure containing game setup details (number of players, difficulty, etc.).
 * @return A `board` structure representing the generated game board.
 */
board generate_board_from_config(config config);

// Function prototypes for internal helper functions:

/**
 * @brief Function to create an array of `player` structures for the given number of players.
 * 
 * This internal function likely allocates memory for the player array and initializes each element with appropriate player data.
 * 
 * @param number_of_players The number of players participating in the game.
 * @return A pointer to the newly created player array.
 */
players_array_pointer _create_players(const unsigned int number_of_players);

/**
 * @brief Function to create a 2D array representing the game board with labeled cells.
 * 
 * This internal function likely allocates memory for a 2D array and initializes each cell with appropriate labels or values.
 * 
 * @param board_size The size of the game board (number of squares on each side, assuming a square board).
 * @return A pointer to the newly created 2D board cell array.
 */
board_cell_array_pointer _create_labeled_board(const unsigned int board_size);

/**
 * @brief Function to generate snakes and ladders on the provided game board based on configuration.
 *
 * This internal function interacts with the `config` structure and the `board` structure to place snakes and ladders on the game board.
 * The specific placement logic depends on the game's rules and difficulty settings.
 *
 * @param config The configuration structure containing game setup details.
 * @param board The `board` structure representing the game board to be modified.
 */
void _generate_snake_and_ladders(config config, board board);

/**
 * @brief Generates a specified number of ladders on the board.
 *
 * This function takes a `board` structure and a desired `count` of ladders as input. 
 * It allocates memory for an array of `ladder` structs and populates it with randomly generated ladders.
 *
 * The algorithm follows these steps:
 *   1. Allocate memory for the ladder array.
 *   2. Initialize variables:
 *      - `minimum_start_y`: This controls the minimum starting y-coordinate for ladders, ensuring they don't concentrate at the bottom.
 *      - `maximum_length`: This represents the maximum length of a ladder, gradually decreasing as ladders are placed.
 *   3. Loop until the desired number of ladders (`count`) is generated.
 *      - Choose a random starting x-coordinate within valid board boundaries (excluding the last column).
 *      - Choose a random starting y-coordinate within the allowed range (`minimum_start_y` to `board.board_size`).
 *      - Check if the starting position's neighbors are empty using `all_neighbors_have_labels`. If not, skip and try a new starting position.
 *      - Choose a random length for the ladder between 2 and `maximum_length`.
 *      - Calculate the potential ending point using `point_for_length`.
 *      - Loop until a valid ending point is found:
 *          - Check if the neighbors of the potential ending point are empty using `all_neighbors_have_labels`. If empty, accept this point and break the loop.
 *      - If no valid ending point is found within the loop, choose a new ending position and repeat.
 *      - Create a `ladder` struct containing the start and end points.
 *      - Store the ladder in the ladders array.
 *      - Draw the ladder on the board using `_draw_line_on_board`.
 *      - Update `minimum_start_y` and `maximum_length` periodically to encourage ladder distribution across the board.
 *   4. Return the pointer to the allocated ladders array.
 *
 * @param board The `board` structure representing the game board.
 * @param count The desired number of ladders to generate.
 * @return A pointer to an array of `ladder` structs representing the generated ladders. (Caller needs to free the memory later)
 */
ladders_array_pointer _genereate_ladders(const board board, const unsigned int count);

/**
 * @brief Calculates the ending point on the board after a specified movement length from a starting point.
 *
 * This function takes a `board` structure, a starting `point`, and a movement `length` as input and returns the ending point on the board after the movement. It considers the board boundaries and wraps around if necessary.
 *
 * The movement direction is determined randomly using the `_random_between` function, which generates a number between 0 and 7 (inclusive). Here's the breakdown of possible directions based on the generated value:
 *  - **0:** Left, low diagonal (more right than left, no vertical movement)
 *  - **1:** Left, mid diagonal (more left than up)
 *  - **2:** Left, high diagonal (more up than left)
 *  - **3:** Right, low diagonal (more right than up)
 *  - **4:** Right, mid diagonal (more up than right)
 *  - **5:** Right, high diagonal (more up than right)
 *  - **6:** Straight up (vertical)
 *
 * If the movement would cause the ending point to go beyond the board boundaries, the function adjusts the coordinates to stay within the valid range.
 *
 * @param board The `board` structure representing the game board.
 * @param start The starting point on the board (coordinates).
 * @param length The movement length (number of squares to move).
 * @return The ending point on the board after the movement.
 */
point point_for_length(const board board,const point start,const unsigned int length);

/**
 * @brief Function to generate a random number between a specified minimum and maximum value (inclusive).
 *
 * This internal function generates a random unsigned integer within the specified range (inclusive). It's likely used for various purposes within the game logic, such as determining ladder lengths or random placements.
 *
 * @param min The minimum value (inclusive) for the random number.
 * @param max The maximum value (inclusive) for the random number.
 * @return A random unsigned integer between `min` and `max`.
 */
unsigned int _random_between(const unsigned int min,const unsigned int max);

/**
 * @brief Checks if all surrounding squares (neighbors) of a given position on the board have labels.
 *
 * This function takes a `board` structure, a starting `start_x` coordinate, and a starting `start_y` coordinate as input and returns a boolean value indicating whether all surrounding squares (up, down, left, and right) have labels assigned.
 * 
 * The function considers the board boundaries and ignores squares outside the valid range.
 *
 * @param board The `board` structure representing the game board.
 * @param start_x The x-coordinate of the starting position.
 * @param start_y The y-coordinate of the starting position.
 * @return True if all surrounding squares have labels, False otherwise.
 */
bool all_neighbors_have_labels(const board board, const int start_x, const int start_y);

/**
 * @brief Draws a line on the board using Bresenham's line algorithm, considering existing board elements and preventing overlaps.
 *
 * This internal function takes a `board` structure, a starting `point`, and a suggested ending `point` as input. It utilizes [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#:~:text=Bresenham's%20line%20algorithm%20is%20a,straight%20line%20between%20two%20points.) to calculate the intermediate points along the line and updates the corresponding elements in the board's inner cell array (`inner_board`).
 *
 * The function avoids drawing over existing elements on the board (e.g., snake bodies, ladder endpoints) to maintain board integrity.
 * 
 * @param board The `board` structure representing the game board.
 * @param start The starting point (coordinates) for the line.
 * @param suggested_end The suggested ending point (coordinates) for the line.
 *
 * @return The end point used to draw the line
 */
point _draw_line_on_board(board board,const point start,const point suggested_end);

/**
 * @brief Finds a suggested ending point for a ladder based on a starting point and desired length, considering board boundaries and empty spaces.
 *
 * This function takes a `board` structure, a starting `point`, and a calculated `length` for the ladder as input. It iterates through potential ending points based on the calculated length and checks if the corresponding cells on the board are empty using `all_neighbors_have_labels`.
 *
 * If all neighbors of a potential ending point are empty, the function returns that point as the suggested ending point. Otherwise, it continues searching until the end of the board is reached or a suitable ending point is found.
 *
 * @param board The `board` structure representing the game board.
 * @param start The starting point (coordinates) for the ladder.
 * @param calculated_length The calculated length (number of squares) for the ladder.
 * @return A `point` representing the suggested ending point for the ladder, or an invalid point (e.g., with negative coordinates) if no suitable point is found. 
 */
point _suggested_end_point_for(const board board,const point start,const unsigned int calculated_length);

#endif