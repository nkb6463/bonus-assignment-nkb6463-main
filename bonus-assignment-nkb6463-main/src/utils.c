#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

/*
 * Rolls a number between 1 and `dice`.
 */
int roll(int dice) 
{
    static int seeded = 0;
    if (!seeded) 
    {
        srand(time(NULL));
        seeded = 1;
    }
    
    return (rand() % dice) + 1;
}

/*
 * Removes the trailing newline from a string, if present.
 */
void remove_newline(char *str) 
{
    int l = strlen(str);

    if (str[l-1] == '\n') 
    {
        str[l-1] = 0;
    }
}