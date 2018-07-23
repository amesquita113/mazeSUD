/*
 * main.c - Main program loop for the maze-rpg game
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include "objects.h"
#include "player.h"
#include "misc.h"
#include "locations.h"
#include "monsters.h"


static char input[60];                         // buffer for keyboard input

/* get_input() function - gets keyboard input from the user and stores it in 
 * the static array 'input[]' */
static int get_input()
{
  printf("\n[%d|%d]> ", player.health, player.energy);                              // Player prompt
  return fgets(input, sizeof(input), stdin) != NULL;
}

/* parse_input() function - function to parse user input string into tokens 
 * 'verb' and 'noun' and run commands based on the verb/noun combination */
static int parse_input()
{
  char *verb = strtok(input, " \n");            // Break the input string down into 2 tokens
  char *noun = strtok(NULL, "\n");
  // if statements to run commands based on input verb
  if (verb != NULL) {
    if (strcasecmp(verb, "QUIT") == 0) {
      return 0;
    }
    else if (strcasecmp(verb, "CLEAR") == 0) { 
      clear_screen();
    }
    else if (strcasecmp(verb, "LOOK") == 0) {
      execute_look(noun);
    }
    else if (strcasecmp(verb, "GO") == 0) {
      execute_go(noun);
    }
    /* Commands for singe letter directions */
    else if (strcasecmp(verb, "N") == 0 &&
      locations[player.location].north !=NULL) {
      move_player(locations[player.location].north);
    }
    else if (strcasecmp(verb, "S") == 0 &&
      locations[player.location].south != NULL) {
      move_player(locations[player.location].south);
    }
    else if (strcasecmp(verb, "E") == 0 &&
      locations[player.location].east != NULL) {
      move_player(locations[player.location].east);
    }
    else if (strcasecmp(verb, "W") == 0 &&
      locations[player.location].west != NULL) {
      move_player(locations[player.location].west);
    }
    /* end of direction comands */
    else if (strcasecmp(verb, "INVENTORY") == 0) {
      list_inventory();
    }
    else if (strcasecmp(verb, "GET") == 0) {
      execute_get(noun);
    }
    else if (strcasecmp(verb, "DROP") == 0) {
      execute_drop(noun);
    }
    else if (strcasecmp(verb, "EQUIP") == 0) {
      execute_equip(noun);
    }
    else if (strcasecmp(verb, "UNEQUIP") == 0) {
      execute_unequip(noun);
    }
    else {
      printf("I'm sorry, I don't know what you mean by %s.\n", verb);
    }
  }

  return 1;
}

/* mazeSUD main program loop */
int main()
{
  /* Intializes random number generator - ONCE ONLY */
  srand(time(0));

  printf("\n--Welcome to mazeSUD v0.3 Alpha--\n");
  printf("--uncopyright 2018  by: xpadrex--\n\n");

  init_monsters();  // randomize monster locations
  init_loot();      // randomize loot for mosters
  create_character();   
  clear_screen();
  execute_look("around");

  while (get_input() && parse_input());

  printf("\nThanks for playing!\n");

  return 0;
}
