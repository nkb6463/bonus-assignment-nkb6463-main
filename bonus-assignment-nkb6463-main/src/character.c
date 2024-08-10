#include "character.h"
#include "utils.h"

int read_stat(int remaining) {
    int val = 0;

    do {
        scanf("%d", &val);

        if (val > remaining) {
            printf("You only have %d points to use.\n", remaining);
        }
    } while (val > remaining);

    return val;
}

void print_character(character_t character) {
    printf("Name: %s\n", character.name);
    printf("HP: %d\n", character.hp);
    printf("AC: %d\n", character.ac);
    printf("STR: %d\n", character.str);
    printf("DEX: %d\n", character.dex);
    printf("CON: %d\n", character.con);
}

character_t create_character() {
    character_t character = { 0 };
    int stats_remaining = MAX_STATS;
    int notified = 0;

    printf("Enter character name: ");
    fgets(character.name, MAX_NAME, stdin);
    remove_newline(character.name);

    printf("Enter STR (%d remaining): ", stats_remaining);
    character.str = read_stat(stats_remaining);

    stats_remaining -= character.str;

    if (stats_remaining > 0) {
        printf("Enter DEX (%d remaining): ", stats_remaining);
        character.dex = read_stat(stats_remaining);

        stats_remaining -= character.dex;
    }

    if (stats_remaining > 0) {
        printf("Enter CON (%d remaining): ", stats_remaining);
        character.con = read_stat(stats_remaining);

        stats_remaining -= character.con;
    }

    character.hp = BASE_HP + character.con - 5;
    character.ac = BASE_AC + character.dex - 5;

    print_character(character);

    return character;
}
