#include "Game.h"
#define EXIT_SUCCESS 0

int main() {

    printf("Let's roll!\n");

    Game game;
    game.initialize();
    game.start();
    return EXIT_SUCCESS;
}
