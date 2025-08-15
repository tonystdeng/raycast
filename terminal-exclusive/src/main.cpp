#include "main.hpp"


Main::Main(std::string type) {
    rate = 0.5;
    Map = getMap();         
    Map = scaleMap(Map);
}


int main(int argc, char* argv[]){
    Main main("terminal");
    while (main.terminalMain()) {}
    return 0;
}