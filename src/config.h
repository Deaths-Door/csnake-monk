/**
 * @file CSnakeLadderConfig.h
 * @brief Header file containing functions for game configuration in Snake and Ladder.
 *
 * This header file defines functions for obtaining game configuration from the user. It also includes a declaration for a helper function used in the process.
 *
 */
#pragma once
#ifndef CSNAKE_LADDER_CONFIG_H
#define CSNAKE_LADDER_CONFIG_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

/**
 * @brief Function to receive game configuration from the user.
 *
 * This function interacts with the user to obtain the game configuration details (number of players, difficulty).
 * It likely utilizes the `receive_input` function for user input and validation.
 *
 * The specific implementation details of this function depend on the game's configuration options and validation logic.
 *
 * @return A `config` structure containing the collected game configuration details.
 */
config receive_config_from_user();

/**
 * @brief Function to receive user input for an integer value.
 *
 * This function prompts the user for an integer value with a provided label and performs basic validation using a supplied validation function.
 * It's likely defined elsewhere (perhaps in "types.h") and expected to handle error scenarios appropriately.
 *
 * @param label A constant character pointer representing the label to display to the user before input.
 * @param validate A validation function pointer that takes an `unsigned int` and returns a `const char*` (validation message) or `NULL` if valid.
 *
 * @return The user-provided integer value (assuming validation is successful).
 */
const unsigned int receive_input(const char *const label, validate validate);

#endif // CSNAKE_LADDER_CONFIG_H