#include "map.h"

int test_is_adjacent() {
    int result = 0;

    character_t players[2] = {
        { "Grog", 0, 0, 0, 0, 0, 1, 1 },
        { "Keyleth", 0, 0, 0, 0, 0, 1, 2 }
    };

    // Truth check
    result = is_adjacent(players[0], players[1]);

    // False check
    players[1].y = 3;

    result += !is_adjacent(players[0], players[1]);

    return result;
}

int test_is_occupied() {
    int result = 0;

    character_t players[2] = {
        { "Grog", 0, 0, 0, 0, 0, 1, 1 },
        { "Keyleth", 0, 0, 0, 0, 0, 1, 2 }
    };

    result = is_occupied(1, 1, players, 2) != -1;
    result += is_occupied(1, 3, players, 2) == -1;

    return result;
}

int test_move_character() {
    int result = 0;

    character_t players[2] = {
        { "Grog", 0, 0, 0, 0, 0, 1, 1 },
        { "Keyleth", 0, 0, 0, 0, 0, 1, 2 }
    };

    result = move_character(players, 2, 0, -1, -1) == 1;
    result += move_character(players, 2, 0, 5, 5) == 0;

    return result;
}

void test_show_map() {
    character_t players[2] = {
        { "Grog", 0, 0, 0, 0, 0, 1, 1 },
        { "Keyleth", 0, 0, 0, 0, 0, 1, 2 }
    };

    show_map(players, 2);
    move_character(players, 2, 0, 5, 5);
    show_map(players, 2);
}

int main() {

    int test1_result = test_is_adjacent();
    if (test1_result) {
        printf("is_adjacent: PASS\n");
    } else {
        printf("is_adjacent: FAIL\n");
    }

    int test2_result = test_is_occupied();
    if (test2_result) {
        printf("is_occupied: PASS\n");
    } else {
        printf("is_occupied: FAIL\n");
    }

    int test3_result = test_move_character();
    if (test3_result) {
        printf("move_character: PASS\n");
    } else {
        printf("move_character: FAIL\n");
    }

    test_show_map();

    return 0;
}
