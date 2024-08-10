#include "combat.h"
#include "map.h"

/*
 * Attempts to attack the `target`.
 * Returns the amount of damage dealt if the attack was successful.
 */
int attack(character_t attacker, character_t target) {
    if (!is_adjacent(attacker, target)) {
        printf("%s is not close enough to attack!\n", target.name);
        return 0;
    }

    int hit_roll = roll(20) + attacker.dex - 5;

    if (hit_roll < target.ac) {
        printf("%s missed %s.\n", attacker.name, target.name);
        return 0;
    }

    int damage_roll = roll(6) + attacker.str - 5;

    printf("%s hit %s for %d damage (rolled %d to hit).\n", attacker.name, target.name, damage_roll, hit_roll);

    return damage_roll;
}
