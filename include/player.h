#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char *name;
    int health;
    int attack;
    int defense;
} Player;

Player *initialize_player(const char *name);

void display_player(Player *player);

#endif
