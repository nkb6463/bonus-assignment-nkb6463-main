#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>

#include "character.h"

#define ROWS 10
#define COLS 10

int is_adjacent(character_t, character_t);
int move_character(character_t[], int, int, int, int);
int is_occupied(int, int, character_t[], int);
void show_map(character_t[], int);

#endif
