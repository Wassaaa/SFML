#include "Game.hpp"

int main()
{
    Game game;
    std::srand(static_cast<unsigned>(time(NULL)));

    while (game.running())
    {
        //init rand
        // update
        game.update();
        // render
        game.render();
    }
}
