#include <stdio.h>
#include <stdlib.h>
// #include <ctype.h>

#define MAX_PLAYERS 10

// names and locations only for testing
char names[MAX_PLAYERS][10] = {"robert", "sam", "anne", "tom", "chiel", "teun", "piet", "jantje", "tux", "maria"};
int locations[MAX_PLAYERS] = {12, 35, 24, 55, 18}; 

bool game_running = true;

void quit_interact();
void update_player_location (int current_player, int value_to_add);

typedef struct {
    int location;
    //char name[10];
    char *name;
} player_t;

struct player {
    int location;
    char *name;
} players[MAX_PLAYERS];

struct board {
    int size;  
};

// player_t players[MAX_PLAYERS];

int create_random_value(int min, int max) {
    int value = rand() % (max - min + 1) + min;

    return value;
}

int set_player_amount () {
    int amount;
    while (true) {
        printf("How many players (Maximum 10): \n");

        scanf("%d", &amount);

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
        char answer = 'p';
        int rolled_value;
    
        printf("Do you want to roll?(yY/nN)\n");
        //int val;  
        //val = 
        scanf(" %c", &answer);
        // fgets(answer, sizeof(answer), stdin);
        
        //printf("Value scanf: %d\n", val);
        //printf("Value answer: %c\n", answer);

        if (answer == 'y' || answer == 'Y') {
            rolled_value = create_random_value(0, 6);

            update_player_location(current_player, rolled_value);
            break;
        }

        else if (answer == 'n' || answer == 'N') {
            quit_interact();
        }

        /*
        else if ( (int) answer == NULL) {
            printf("answer is NULL");
        }
        */

        else {
            printf("%c is not a correct value...", answer);
        }
    }
}

void update_player_location (int current_player, int value_to_add) {
    int new_location = players[current_player].location + value_to_add;

    players[current_player].location = new_location;
}

void check_if_won (int current_player, int board_size) {
    if (players[current_player].location > board_size) {
        printf("%s won !!!", players[current_player].name);
        exit(0);
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

void init_players (int player_amount) {
    for (int i = 0; i < player_amount; i++) {
        char name[10];
        players[i].location = 1;
        
        
        printf("What is your name player %d\n", i+1);
        scanf("%s", name);
        

        players[i].name = name;
        //players[i].name = names[i];

        printf("%d\n", players[i].location);
        printf("%s\n\n", players[i].name);
    }
}

void print_player_names (int current_spot, int player_amount) {
    for (int i = 0; i < player_amount; i++) {
        if (players[i].location == current_spot) {
            printf("%s (Player %d)", players[i].name, i+1);
            if (i != player_amount - 1) {
                printf(", ");
            }
        }
        
    }

}

void print_board (int board_size, int player_amount) {
    for (int i = 1; i <= board_size; i ++) {
        printf("%d: ", i);

        print_player_names(i, player_amount);

        printf("\n");
    }
}


int main () {
    struct board b;
    b.size = 63;


    int current_player = 0;
    
    int p_a = set_player_amount();

    init_players(p_a);

    while (game_running == true) {
        print_board(b.size, p_a);
        roll_interact(current_player);

        check_if_won(current_player, b.size);

        if (current_player == p_a) {
            current_player = 0;
        }

        else {
            current_player++;
        }
    }

    return 0;
}
