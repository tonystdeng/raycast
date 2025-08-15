#include "main.hpp"


Main::Main(std::string type) {
    if (type == "sfml"){
        // init window
        wSize = sf::VideoMode({1600, 800});
        window = new sf::RenderWindow(wSize, "Raycaster");
        window->setFramerateLimit(targetFPS);
        rate = 0.1;
    }
    else if (type == "terminal") {
        rate = 0.5;
    }

    Map = getMap();         
    Map = scaleMap(Map);
}


int main(int argc, char* argv[]){
    if (argc >= 2 && std::strcmp(argv[1], "-t") == 0) {
        Main main("terminal");
        while (main.terminalMain()) {}
    }
    else {
        Main main("sfml");
        while (main.sfmlMain()) {}
    }
    return 0;
}