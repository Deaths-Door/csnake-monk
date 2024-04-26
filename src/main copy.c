#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Read this https://stackoverflow.com/a/890846/20243803

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