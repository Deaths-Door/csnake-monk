#include "types.h"
#include "config.h"

int main() {
    printf("Snake and Ladder Game\n");
    
    config config = receive_config_from_user();
    board board = generate_board_from_config(config);

    
    return 0;
}