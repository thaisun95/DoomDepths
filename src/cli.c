#include "cli.h"
#include "monster.h"

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

void clear_lines(int lines)
{
    for (int i = 0; i < lines; ++i)
        printf("\x1b[1F\x1b[2K");
}

void wait_for_enter()
{
    printf("\nPress [ENTER] to continue...");
    clear_stdin();
}

int actualStringLength(const char *str)
{
    int length = 0;
    int inColorCode = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\x1B')
        { // Check for ANSI escape code
            inColorCode = 1;
        }
        else if (inColorCode && str[i] == 'm')
        {
            inColorCode = 0;
        }
        else if (!inColorCode)
        {
            length++;
        }
    }

    return length;
}

void main_menu()
{
    int choice;
    do
    {
        clear_screen();
        display_menu_design();

        printf("\n 1. Start Game\n 2. Quit\n\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clear_stdin();
        switch (choice)
        {
        case 1:
            clear_screen();
            Monsters *monsters = initialize_monsters();

            // Seed the random number generator once at the beginning of the program
            srand(time(NULL));

            // Randomize between 1 and 5 monsters
            int numMonsters = rand() % 5 + 1;
            for (int i = 0; i < numMonsters; ++i)
            {
                // Generate a unique seed for each monster
                unsigned int seed = (unsigned int)time(NULL) + i;

                Monster *monster = create_monster(seed);               // Create a new monster
                monsters = add_monster_to_monsters(monsters, monster); // Add the new monster to the list
            }

            dispaly_all_monsters(monsters);

            // Appel de la fonction player_attack
            player_attack(monsters, numMonsters);

            free_monsters(monsters);

            break;

        case 2:
            break;
        default:
            choice = 0;
            break;
        }
    } while (choice < 1 || choice > 2);
}

void monsters_attack(Player *player, Monster *monsters, int num_monsters) {
    printf("\nC'est au tour des monstres d'attaquer!\n");
    for (int i = 0; i < num_monsters; i++) {
        if (monsters[i].life > 0) {  // Le monstre attaque seulement s'il est en vie
            int damage = (rand() % (monsters[i].attackMax - monsters[i].attackMin + 1)) + monsters[i].attackMin;
            printf("Le monstre %s attaque et inflige %d dégâts!\n", monsters[i].name, damage);
            player->health -= damage;
        }
    }

    printf("Votre vie restante: %d\n", player->health);
    if (player->health <= 0) {
        printf("Vous avez été vaincu...\n");
        exit(0);  // Fin du jeu
    }
}


void player_attack(Monster *monsters, int num_monsters) {
    printf("Choisissez un monstre à attaquer (0-%d):\n", num_monsters - 1);
    for (int i = 0; i < num_monsters; i++) {
        printf("%d. %s (Vie: %d)\n", i, monsters[i].name, monsters[i].life);
    }

    int choice;
    scanf("%d", &choice);

    if (choice >= 0 && choice < num_monsters) {
    
        int damage = 10 - monsters[choice].defense;
        if (damage < 0) damage = 0; 
        monsters[choice].life -= damage;
        printf("Vous avez infligé %d dégâts au monstre %s!\n", damage, monsters[choice].name);

        if (monsters[choice].life <= 0) {
            printf("Le monstre %s est mort!\n", monsters[choice].name);
        }
    } else {
        printf("Choix invalide.\n");
    }
}
