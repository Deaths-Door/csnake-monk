#include "config.h"


validate_message ensure_players_within_1_10(validate_int input) {
    if(input < 1 || input > 10) return "Number of players has to be between 1 and 10!\n";
    else return NULL;
}

validate_message ensure_difficulty_within_1_10(validate_int input) {
    if(input < 1 || input > 10) return "The difficulty level has to be between 1 and 10!\n";
    else return NULL;
}

// Function Pointers https://www.geeksforgeeks.org/function-pointer-in-c/
config receive_config_from_user() {
    const unsigned int number_of_players = receive_input("Enter the difficulty level (1-10): \n",&ensure_players_within_1_10);
    const unsigned int difficulty = receive_input("Enter the difficulty level (1-10): \n",&ensure_difficulty_within_1_10);

    config config = {
        .number_of_players = number_of_players,
        .difficulty = difficulty,
    };

    return config;
}


const unsigned int receive_input(const char *const label, validate validate) {
    unsigned int value;

    while(true) {
        printf(label);

        // Clear the input buffer before reading the number
        // This loop is crucial to prevent unexpected behavior when using scanf
        // 
        // Explanation:
        // 
        // 1. scanf("%u", &number_of_players) might leave a newline character in the buffer:
        //    - scanf reads characters from the input stream until it encounters a whitespace 
        //      (like space, tab, newline) or reaches the end of the line (EOF).
        //    - Imagine the user enters "12" followed by Enter. scanf reads "12" but the 
        //      newline character ("\n") remains in the buffer.
        // 
        // 2. This loop discards any leftover characters in the buffer:
        //    - It declares an integer variable 'c'.
        //    - The 'while' loop continues as long as 'c' is not:
        //        - a newline character (`\n`)
        //        - the end-of-file indicator (EOF)
        //    - Inside the loop, getchar() reads a single character from the standard input 
        //      and discards it by assigning it to 'c'. This effectively "eats up" any 
        //      leftover characters until it encounters a newline or EOF.
        // 
        // 3. Why is this important?
        //    - Without this cleaning, the next scanf might accidentally read the leftover 
        //      newline character instead of the user's next input. This can lead to:
        //        - scanf failing to read the input
        //        - scanf interpreting the newline as part of the next number (causing errors)
        // 
        // 4. Alternative solutions for buffer cleaning:
        //    - fgets: reads a line of text (including newline). You can then extract the 
        //      desired number using string manipulation functions.
        //    - scanf with size specifier: allows specifying a maximum number of characters 
        //      to read. However, this might not be ideal for very long user inputs.
        //
        // Clear the input buffer before reading the number
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if(scanf("%u", &value) != 1) {
            perror("Invalid input\n");
            continue;
        }

        validate_message message = (*validate)(value);

        if(message != NULL) {
            perror(message);
            continue;
        }

        break;
    };
  
    return value;
}