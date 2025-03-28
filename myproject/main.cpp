#include "game.h"
using namespace std;
int main (int argc, char * argv [])
{
    Game game;
    if (game.running)
    {
        game.run();
    }
    game.GameEnd();
    return 0;
}


