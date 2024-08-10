#include <time.h>

#include "combat.h"
#include "map.h"
#include "character.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MAX_PLAYERS 2

/*
 * Rolls to determine which player starts first.
 */
void roll_initiative(character_t players[], int init_order[]) {
    int p1_roll = roll(20) + players[0].dex - 5;
    int p2_roll = roll(20) + players[1].dex - 5;

    do {
        p1_roll = roll(20) + players[0].dex - 5;
        p2_roll = roll(20) + players[1].dex - 5;
    } while (p1_roll == p2_roll);

    if (p1_roll > p2_roll) {
        init_order[0] = 0;
        init_order[1] = 1;
    } else {
        init_order[0] = 1;
        init_order[1] = 0;
    }
}

/*
 * Randomly place the players on the map.
 */
void scatter_players(character_t players[], int num_players) {
    for (int i = 0; i < num_players; i++) {
        do {
            players[i].x = roll(COLS);
            players[i].y = roll(ROWS);
        } while (is_occupied(players[i].x, players[i].y, players, num_players) != i);
    }
}

/*
 * Display the movement controls to the user.
 */
void show_move_menu() {
    printf("Movement Controls:\n");
    printf("1 2 3\n");
    printf("4 * 6\n");
    printf("7 8 9\n");
    printf("B - Back to previous menu.\n");

}

/*
 * Process a player's movement in a round of combat.
 */
int process_move(character_t players[], int num_players, int current_player, int movement_remaining) {
    // Move character
    if (movement_remaining <= 0) {
        printf("You have no movement remaining.\n");
        return 0;
    }

    char choice = 0;

    while (movement_remaining > 0) {
        int cur_x = players[current_player].x;
        int cur_y = players[current_player].y;
        int target_x = 0;
        int target_y = 0;

        show_map(players, num_players);
        printf("%d movement remaining.\n", movement_remaining);
        show_move_menu();

        scanf("%c", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case '1':
                target_x = cur_x - 1;
                target_y = cur_y - 1;
                break;
            case '2':
                target_x = cur_x;
                target_y = cur_y - 1;
                break;
            case '3':
                target_x = cur_x + 1;
                target_y = cur_y - 1;
                break;
            case '4':
                target_x = cur_x - 1;
                target_y = cur_y;
                break;
            case '6':
                target_x = cur_x + 1;
                target_y = cur_y;
                break;
            case '7':
                target_x = cur_x - 1;
                target_y = cur_y + 1;
                break;
            case '8':
                target_x = cur_x;
                target_y = cur_y + 1;
                break;
            case '9':
                target_x = cur_x + 1;
                target_y = cur_y + 1;
                break;
            case 'b':
            case 'B':
                return movement_remaining;
            default:
                printf("Invalid selection!\n");
        }

        if (choice > '0' && choice <= '9' && choice != '5') {
            if (!move_character(players, num_players, current_player, target_x, target_y)) {
                movement_remaining--;
            }
        }
    }

    return movement_remaining;
}

/*
 * Display player options for their turn.
 */
void show_turn_menu() {
    printf("A - Attack\n");
    printf("M - Move\n");
    printf("E - End Turn\n");
}

/*
 * Process a player's turn.
 */
void process_turn(character_t players[], int num_players, int current_player) {
    int movement_remaining = 5;
    char choice = 0;
    int opponent_idx = current_player ? 0 : 1;
    int has_attacked = 0;

    while (1) {
        show_map(players, num_players);
        show_turn_menu(has_attacked, movement_remaining);

        scanf("%c", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 'a':
            case 'A':
                if (!has_attacked) {
                    int dmg = attack(players[current_player], players[opponent_idx]);
                    players[opponent_idx].hp = MAX(players[opponent_idx].hp - dmg, 0);
                    has_attacked = 1;
                } else {
                    printf("%s has already attempted an attack.\n", players[current_player].name);
                }
                break;
            case 'm':
            case 'M':
                movement_remaining = process_move(players, num_players, current_player, movement_remaining);
                break;
            case 'e':
            case 'E':
                printf("Ending turn...\n");
                return;
        }

    }

}

/*
 * Determines if the game should end.
 * Returns 1 if true, 0 if false.
 */
int end_check(character_t players[], int num_players) {
    if (players[0].hp == 0) {
        printf("%s is the winner!\n", players[1].name);
        return 1;
    } else if (players[1].hp == 0) {
        printf("%s is the winner!\n", players[0].name);
        return 1;
    }

    return 0;
}

/*
 * Provides a summary of the players as well as their identifier on the map.
 */
void show_player_summary(character_t players[], int num_players, int init_order[]) {
    printf("\n");
    for (int i = 0; i < num_players; i++) {
        int player_idx = init_order[i];
        printf("P%d: %s (%d HP)\n", player_idx + 1, players[player_idx].name, players[player_idx].hp);
    }
}

/*
 * Start a game of combat.
 */
void start_combat(character_t players[], int num_players) {
    // Roll to see who goes first
    int init_order[MAX_PLAYERS] = { 0 };
    roll_initiative(players, init_order);

    scatter_players(players, num_players);

    // Reset player health
    for (int i = 0; i < num_players; i++) {
        players[i].hp = BASE_HP + players[i].con - 5;
    }

    // Process a round
    while (1) {
        for (int i = 0; i < num_players; i++) {
            show_player_summary(players, num_players, init_order);
            printf("\n%s's turn (P%d).\n", players[init_order[i]].name, init_order[i] + 1);
            process_turn(players, num_players, init_order[i]);

            if (end_check(players, num_players)) {
                printf("Game over!\n");
                return;
            }
        }
    }
}

/*
 * Display the main menu.
 */
void main_menu(character_t players[], int num_players) {
    int choice = 0;

    while (1) {
        printf("\n==========================\n");
        printf("= TTRPG Combat Simulator =\n");
        printf("==========================\n\n");

        if (num_players == 0) {
            printf("Create or load 2 players to begin!\n");
        }

        for (int i = 0; i < num_players; i++) {
            printf("Player %d: %s\n", i + 1, players[i].name);
        }

        printf("\n1. Start Game\n");
        printf("2. Create Character\n");
        printf("3. Save Character\n");
        printf("4. Load Character\n");
        printf("5. Exit\n");

        scanf("%d", &choice);
        while (getchar() != '\n');

        switch(choice) {
            case 1:
                if (num_players < 2) {
                    printf("Create or load at least 2 characters first.\n");
                } else {
                    // Start combat
                    start_combat(players, num_players);
                }
                break;
            case 2:
                if (num_players == MAX_PLAYERS) {
                    printf("You already have the maximum number of players.\n");
                } else {
                    players[num_players++] = create_character();
                }
                break;
            case 3:
                // TODO: Create save_character function as described in the assignment.
                break;
            case 4:
                // TODO: Create load_character function as described in the assignment.
                break;
            case 5:
                printf("Thanks for playing!\n");
                return;
            default:
                printf("Invalid selection!\n");
        }
    }
}

int main() {
    time_t t;
    time(&t);
    srand(t);

    character_t players[MAX_PLAYERS] = { 0 };
    int num_players = 0;

    main_menu(players, num_players);
}
