#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "monster.h"


Player *initialize_player(const char *name) {
    Player *player = malloc(sizeof(Player));
    player->name = strdup(name);
    player->health = 100;  // valeur initiale
    player->attack = 10;   // valeur initiale
    player->defense = 5;   // valeur initiale
    return player;
}

void display_player(Player *player) {
    printf("Nom: %s\n", player->name);
    printf("Vie: %d\n", player->health);
    printf("Attaque: %d\n", player->attack);
    printf("Défense: %d\n", player->defense);
}
void monster_attack(Monster *monster, Player *player) {
    int damage = monster->attackMax - player->defense;  // Utilisez "attackMax"
    if (damage < 0) damage = 0;
    player->health -= damage;
    printf("%s riposte et inflige %d dégâts à %s!\n", monster->name, damage, player->name);
}
