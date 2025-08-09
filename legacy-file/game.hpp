#pragma once

#ifndef GAME_HPP
#define GAME_HPP
#define PI 3.14159265359

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
typedef std::vector<int> mapLine;
typedef std::vector<mapLine> map;
const int msr=15;const int hmsr=msr/2;
const float range=60, rate=0.1;
//msr=map size rate, scaling map is nessary for player to walk free

class Game
{
    public:
        sf::RenderWindow *window;
        sf::VideoMode wSize;
        int angle=0;
        map Map;
        sf::Vector2f size, pos;
        // size of map and pos of player both afted scaling

        Game();//working
        void getMap();//working
        map scaleMap(map);

        void main();
        bool checkEvent();//working
        void move();
        void display();
        std::vector<sf::RectangleShape> tdLoader();
        //the above function returns all rectangles that forms the 3d look
        std::pair<float,int> gcr(float);
        //gcr stands for get closest reach
        // the above function returns the sight when raycast at a certain angle
    
};


#endif