#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ctype.h>

#define MAX_PLAYERS 10


int current_player_game_loop = 0;
int player_amount;

void quit_interact();
void update_player_location (int current_player, int value_to_add);
void print_player_names (int player_amount);
void print_player_names_debug (int quit_or_not);


struct player {
    int location;
    char name[10];
} players[MAX_PLAYERS];

struct board {
    int size;
    int thorn_bush;
};

struct board board;


int create_random_value(int min, int max) {
    int value = rand() % (max - min + 1) + min;

    return value;
}

int set_player_amount () {
    char amount_as_char[10];
    int amount;
    while (true) {
        printf("How many players (Maximum 10): \n");

        fgets(amount_as_char, sizeof(amount_as_char), stdin);
        amount = atoi(amount_as_char);

        if (amount >= MAX_PLAYERS) {
            printf("To many players!\n");
        }
        else {
            break;
        }
    }
    return amount;
};

void roll_interact (int current_player) {
    while (true) {
        //print_player_names_debug(0);

        char answer = 'p';
        int rolled_value;
    
        printf("Do you want to roll?(yY/nN)\n");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            rolled_value = create_random_value(0, 6);

            update_player_location(current_player, rolled_value);
            break;
        }

        else if (answer == 'n' || answer == 'N') {
            quit_interact();
        }

        else {
            printf("%c is not a correct value...", answer);
        }
    }
}

void update_player_location (int current_player, int value_to_add) {
    int new_location = players[current_player].location + value_to_add;

    players[current_player].location = new_location;
}

void check_if_won (int current_player) {
    if (players[current_player].location > board.size) {
        printf("%s won !!!", players[current_player].name);
        exit(0);
    }
}

void check_if_bush(int current_player) {
    if (players[current_player].location == board.thorn_bush) {
        int value = create_random_value(1, board.size-players[current_player]);
    }
}

void quit_interact () {
    char choice;

    while (true) {
        printf("Are you sure you want to quit? yY/nN:\n");
        scanf(" %c", &choice);
        
        if ( choice == 'y' || choice == 'Y' ) {
            exit(1);
        }
        else if ( choice == 'n' || choice == 'N' ) {
            break;
        }
        else {
            printf("Not a valid choice!\n");
        }
    }
}

void name_newline_to_null_terminator (int current_player) {
    int player_name_len = strlen(players[current_player].name);
    for (int i = 0; i < player_name_len; i++) {
        if (players[current_player].name[i] == '\n') {
            players[current_player].name[i] = '\0';
        }
    } 
}

void print_player_names_debug (int quit_or_not) {
    for (int i = 0; i < player_amount; i++) {
        printf("Player %d = %s\n", i+1, players[i].name);        
    }
    
    if (quit_or_not == 1) {
        exit(1);
    }
}

void init_players () {
    char name[10];

    for (int i = 0; i < player_amount; i++) {
        players[i].location = 1;
        
        
        printf("What is your name player %d\n", i+1);
        fgets(name, sizeof(name), stdin);

        strncpy(players[i].name, name, 9);
        
        name_newline_to_null_terminator(i);

        //printf("%d\n", players[i].location);
        //printf("%s\n\n", players[i].name);
    }

    //print_player_names_debug(0);
}

void print_player_names_on_board (int current_spot) {
    for (int i = 0; i < player_amount; i++) {
        if (players[i].location == current_spot) {
            printf("%s (Player %d)\n", players[i].name, i+1);
        }
    }

}

void create_thorn_bush() {
    board.thorn_bush = create_random_value(2, board.size); 
}

void print_thorn_bush(int current_spot) {
    if (current_spot == board.thorn_bush) {
        printf("Thorn bush\n");
    }
}

void print_board () {
    for (int i = 1; i <= board.size; i ++) {
        printf("%d:\n", i);
        
        print_thorn_bush(i);
        print_player_names_on_board(i);

    }

    printf("Player %d (%s), on position %d\n", current_player_game_loop+1, players[current_player_game_loop].name, players[current_player_game_loop].location);
}

void game_setup() {
    
    player_amount = set_player_amount();

    init_players();
    create_thorn_bush();
}

int main () {
    board.size = 63;

    game_setup();   

    while (true) {
        //printf("\x1B[2J");

        print_board();
        roll_interact(current_player_game_loop);

        check_if_won(current_player_game_loop);

        if (current_player_game_loop == player_amount-1) {
            current_player_game_loop = 0;
        }

        else {
            current_player_game_loop++;
        }
    }

    return 0;
}
