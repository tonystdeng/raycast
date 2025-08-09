#pragma once

#ifndef MAIN_HPP
#define MAIN_HPP
#define PI 3.14159265359

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


typedef std::vector<int> mapLine;
typedef std::vector<mapLine> map;

const int msr = 15;
const int hmsr = msr / 2;
//msr=map size rate, scaling map is nessary for player to walk free



const sf::Keyboard::Scancode keys[] = {
    sf::Keyboard::Scan::W,
    sf::Keyboard::Scan::D,
    sf::Keyboard::Scan::S,
    sf::Keyboard::Scan::A
};


class Main
{
private:
    float range = 60; // how wide is the view (fov in minecraft)
    float rate; // how detailed is the view

    sf::RenderWindow *window;
    sf::VideoMode wSize;

    int angle = 0;
    map Map;

    sf::Vector2f size, pos;
    // size of map and pos of player are both after scaling

public:
    Main(std::string);// Constructor 
    
    bool sfmlMain(); 
    void sfmlInput(float speed = 1);
    // sfmlDisplay.cpp

    bool terminalMain();
    void terminalInput(float speed = 1);
    // terminal.cpp

    map getMap();
    map scaleMap(map);
    // loadMap.cpp

    std::vector<std::pair<float, int>> tdLoader(int maxH);
    std::pair<float, int> gcr(float);
    bool movePlayer(int direction, float speed);
    // logic.cpp

};

#endif