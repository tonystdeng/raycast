#include "game.hpp"

int main(){
    Game game;

    while (game.window->isOpen()){
        game.main();
    }
    return 0;
}