#include "Game.h"
int main(int argc, char const *argv[])
{
    Game game;
    bool success =game.Initialize();
    if(success){
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
