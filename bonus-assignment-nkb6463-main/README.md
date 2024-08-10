# CSE 1310 Bonus Assignment

In this assignment, you will be creating code as part of a larger program and then integrating it into the final program. A client has contracted your development company to create a table top RPG
combat simulator that supports 2 players. Your team has already finalized the design and implemented
other components of the application. There are a few core tasks remaining that you must implement.

## (10 points) Rolling Dice

Your first task is to implement the function `int roll(int dice);` as declared in `utils.h`.
Given an input integer, `dice`, representing the number of faces on the dice, this function should randomly
roll a value between 1 and `dice`. Return the rolled value.
For example, if the function is called as `roll(20)`, the function will generate a random number between 1 and 20.

This function should be defined in `utils.c`.

### Testing

Once you implement this function, compile the test file for this by calling `make rolltest` from the base of the project directory.
You can then run the test by calling `./tests/rolltest`.
It should successfully roll 6 dice and print the output.

**DO NOT MODIFY THE TEST CODE FILE.**

## (40 points) Map

As part of the combat simulator, the players should be able to see their location on a map.
In the design phase of this project, your team decided that they will need to implement 4 core functions as described below.

### (15 points) Checking if two players are adjacent

As part of the rules given to us by the client, a player may only attack another player if they are adjacent to the target.
That is, they must be within one square of them.
This will be implemented following the function declaration given in `map.h`.

```
int is_adjacent(character_t, character_t);
```

Given an attacker and a target, in that order, the function should determine if the players are adjacent.
The function will return 1 if they are, and 0 if they are not.

This function should be defined in `map.c`.

### (15 points) Checking if a space is occupied

A player should not be able to move into the same space as another player.
To check this, implement the function declared in `map.h`:

```
int is_occupied(int, int, character_t[], int);
```

That is given an x value, y value, array of players, and an integer representing the number of players,
loop through the player array and check if any of the players are in the space at $(x, y)$.
If a player is occupying that space, return the array index of that player.
If the space is empty, return -1.

This function should be defined in `map.c`.

## (10 points) Moving a character

Characters must be able to move to empty spaces on the map during their turn.
This will be implemented using the function declared in `map.h`:

```
int move_character(character_t[], int, int, int, int);
```

Given an array of players, the number of players, the array index of the player being moved, the x value they wish
to move to, and the y value they wish to move to, define this function in `map.c`.
This function should make sure that the desired location is valid. That is, it must be an unoccupied space
(hint: use `is_occupied` to check) and it must be within the size of the map.

## Showing the map

The `show_map` function is provided for you and will use the above functions when displaying the map. Asusming you've implemented the above functions correctly, you should be able to display the map with the player locations.

The player locations should show up similar to the following example output.

```
     1  2  3  4  5  6  7  8  9 10
  1             P2                  
  2                                 
  3                                 
  4                                 
  5                                 
  6                                 
  7                      P1         
  8                                 
  9                                 
 10                                 
```

### Testing

Once the above functions are defined, you can test them by compiling the map test via `make maptest` from the base of the project directory.
This will generate an executable that you can run using `./tests/maptest`.
The first 3 functions should pass the test.
The `show_map` function should clearly display player 1 at location $(3, 3)$ and player 2 at location $(3, 6)$.

**DO NOT MODIFY THE TEST CODE FILE.**

## Compiling the Application

Once you have finished implementing the tasks above, you can run and play the combat simulator.
From the base project directory, type `make`.
This should execute a command to compile the project.
The program can be run by using the command `./build/combat_sim`.