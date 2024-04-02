#include "../include/game.hpp"

Game *game = nullptr;

int main(int argc, const char *argv[])
{

    game = new Game();

    game->init("the_game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);

    while (game->running())
    {

        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}