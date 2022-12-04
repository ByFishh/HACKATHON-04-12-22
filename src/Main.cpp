#include "./Game/Game.hpp"
#include <time.h>

int main(void)
{
    Game game = Game();

    srand(time(NULL));
    game.Loop();

    return 0;
}