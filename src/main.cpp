#include "Game.hpp"

int main()
{
    Game game;

    while (game.running())
    {
        //init rand
        std::srand(static_cast<unsigned>(time(NULL)));
        // update
        game.update();
        // render
        game.render();
    }
}
