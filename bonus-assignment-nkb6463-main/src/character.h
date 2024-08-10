#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <stdio.h>

#define MAX_NAME 32
#define MAX_STATS 15
#define BASE_HP 50
#define BASE_AC 15

typedef struct {
    char name[MAX_NAME];
    int hp;
    int ac;
    int str;
    int dex;
    int con;
    int x;
    int y;
} character_t;

void print_character(character_t);
character_t create_character();

#endif
