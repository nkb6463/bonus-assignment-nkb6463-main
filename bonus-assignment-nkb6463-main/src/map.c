#include "map.h"
#include <stdlib.h>

/*
 * Determines if two players are adjacent to each other.
 * Returns 1 if true, 0 if false.
 */
int is_adjacent(character_t player1, character_t player2) 
{
    int dx = abs(player1.x - player2.x);
    int dy = abs(player1.y - player2.y);
    
    return (dx <= 1 && dy <= 1) && !(dx == 0 && dy == 0);
}

/*
 * Move a character to the given location.
 * Returns 0 if the move is successful and 1 if the move cannot be made.
 */
int move_character(character_t players[], int num_players, int player_idx, int x, int y) 
{
    // Check if the new location is within the map bounds
    if (x < 1 || x > COLS || y < 1 || y > ROWS) 
    {
        return 1;  // Invalid move - out of bounds
    }
    
    // Check if the new location is occupied
    if (is_occupied(x, y, players, num_players) != -1) 
    {
        return 1;  // Invalid move - space is occupied
    }
    
    // Move is valid, update the player's position
    players[player_idx].x = x;
    players[player_idx].y = y;
    
    return 0;  // Move successful
}

/*
 * Determines if a player is occupying the grid space at (x, y).
 * Returns the index of the player at that location if it is occupied.
 */
int is_occupied(int x, int y, character_t players[], int num_players) 
{
    for (int i = 0; i < num_players; i++) 
    {
        if (players[i].x == x && players[i].y == y) 
        {
            return i;  // Return the index of the player occupying the space
        }
    }
    return -1;  // Space is empty
}

/*
 * Displays a 2D grid with the player locations clearly marked.
 */
void show_map(character_t players[], int num_players) 
{
    for (int y = 0; y <= ROWS; y++)
    {
        if (y > 0) 
        {
            printf("%3d", y);
        }
        for (int x = 0; x <= COLS; x++) 
        {
            if (y == 0) 
            {
                // Print grid numbers in first row
                if (x == 0) 
                {
                    printf("   ");
                } 
                else 
                {
                    printf("%3d", x);
                }
            } 
            else 
            {
                int player_idx = is_occupied(x, y, players, num_players);
                if (player_idx != -1) 
                {
                    printf(" P%d", player_idx + 1);
                } 
                else 
                {
                    printf("   ");
                }
            }
        }
        printf("\n");
    }
}