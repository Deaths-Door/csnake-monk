/**
 * @file CSnakeLadderTypes.h
 * @brief Header file containing type definitions for the Snake and Ladder game.
 *
 * This header file defines various data types used in the Snake and Ladder game implementation.
 * It utilizes typedefs and structures to create clear and consistent representations of game elements.
 */
#pragma once
#ifndef CSNAKE_LADDER_TYPES_H
#define CSNAKE_LADDER_TYPES_H

/**
 * @typedef validate_int
 * @brief Unsigned integer type used for validation functions.
 */
typedef const unsigned int validate_int;

/**
 * @typedef validate_message
 * @brief Constant character pointer type representing a validation message.
 */
typedef const char* validate_message;

/**
 * @typedef validate
 * @brief Function pointer type for validation functions.
 *
 * This type defines a function pointer that takes an `unsigned int` as input and returns a `const char*` (validation message).
 * It is typically used for validating user input or game data.
 */
typedef validate_message (*validate)(validate_int input);

/**
 * @typedef board_cell_array_pointer
 * @brief Constant pointer to a pointer to a 2D array of `board_cell` structures.
 *
 * This complex type represents a pointer to a pointer to a 2D array of `board_cell` structures. It essentially holds the game board itself.
 */
typedef struct board_cell** *const board_cell_array_pointer;

/**
 * @typedef players_array_pointer
 * @brief Constant pointer to a pointer to an array of `player` structures.
 *
 * This type represents a pointer to a pointer to an array of `player` structures, keeping track of all players in the game.
 */
typedef struct player* *const players_array_pointer;

/**
 * @typedef ladders_array_pointer
 * @brief Constant pointer to an array of `ladder` structures.
 *
 * This type defines a constant pointer to an array of `ladder` structures, representing all ladders present on the game board.
 */
typedef struct ladder* ladders_array_pointer;

/**
 * @enum role
 * @brief Enumeration representing the role of a point on the board (ladder or snake).
 */
typedef enum role {
  is_ladder,  /**< Point represents the bottom of a ladder. */
  is_snake   /**< Point represents the head of a snake. */
} role;

/**
 * @typedef player
 * @brief Structure representing a player in the Snake and Ladder game.
 */
typedef struct player {
  /**
   * @brief The position of the player on the game grid (X-coordinate).
   */
  unsigned int position_x;

  /**
   * @brief The position of the player on the game grid (Y-coordinate).
   */
  unsigned int position_y;
} player;

/**
 * @typedef board_cell
 * @brief Structure representing a single cell on the game board.
 */
typedef struct board_cell {
  /**
   * @brief The label associated with the board cell (typically its position number).
   */
  unsigned int label;
} board_cell;


/**
 * @typedef point
 * @brief Structure representing a point on the game board.
 *
 * This structure defines a point with its X and Y coordinates, along with an optional role (ladder or snake) if applicable.
 */
typedef struct point {
  /**
   * @brief The X-coordinate of the point on the board.
   */
  const unsigned int x;

  /**
   * @brief The Y-coordinate of the point on the board.
   */
  const unsigned int y;

  /**
   * @brief The role associated with the point (ladder or snake), or unspecified (NULL) if not applicable.
   */
  const enum role role;
} point;

/**
 * @typedef ladder
 * @brief Structure representing a ladder on the game board.
 */
typedef struct ladder {
  /**
   * @brief The starting point (bottom) of the ladder.
   */
  const struct point start;

  /**
   * @brief The ending point (top) of the ladder.
   */
  const struct point end;
} ladder;


/**
 * @typedef board
 * @brief Structure representing the game board.
 *
 * This structure encapsulates all the essential elements of the game board for Snake and Ladder.
 */
typedef struct board {
  /**
   * @brief Pointer to a pointer to an array of `player` structures, representing all players in the game.
   */
  players_array_pointer players;

  /**
   * @brief The size of the game board (number of squares on each side, assuming a square board).
   */
  const unsigned int board_size;

  /**
   * @brief Pointer to a pointer to a 2D array of `board_cell` structures, representing the actual game board cells.
   */
  board_cell_array_pointer inner_board;

  /**
   * @brief Pointer to an array of `ladder` structures, representing all ladders present on the game board.
   */
  ladders_array_pointer ladders;
} board;

/**
 * @typedef config
 * @brief Structure representing the configuration for a game of Snake and Ladder.
 *
 * This structure holds information about the game setup, such as the number of players and difficulty level.
 */
typedef struct config {
  /**
   * @brief The number of players participating in the game.
   */
  const unsigned int number_of_players;

  /**
   * @brief The difficulty level of the game (implementation-specific, could be integer or enum).
   */
  const unsigned int difficulty;
} config;

#endif //CSNAKE_LADDER_TYPES_H