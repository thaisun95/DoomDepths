#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include "utils.h"
#include "monster.h"
#include "player.h"

/**
 * @brief Cross-platform function to clear console screen.
 *
 * Prints a regex where:
 * - "\e[1;1H" moves cursor to top left corner of terminal screen;
 * - "\e[2J" replaces all characters of the terminal screen with spaces.
 */
void clear_screen();

/**
 * @brief Cross-platform functino to clear a given number of console lines.
 *
 * Prints a regex where:
 * - "\x1b[1F" moves cursor to beginning of previous line;
 * - "\x1b[2K" replaces all characters of this line with spaces.
 */
void clear_lines(int);

/**
 * @brief Prints main menu.
 *
 * 2 options:
 * 1. Start Game;
 * 2. Quit.
 */
void main_menu();

/**
 * @brief Waits for user to press [ENTER] key.
 *
 * Uses getchar() in clearStdin() to wait for [ENTER] key.
 * Then, it clears the stdin buffer (in case user pressed more than one key).
 */
void wait_for_enter();

/**
 * @brief Gets the length of a string without counting ANSI escape codes.
 * 
 * @param str 
 * @return int 
 */
int actualStringLength(const char *str);
void player_attack(Monsters *monsters);
void monsters_attack(Player *player, Monster *monsters, int num_monsters);

#endif