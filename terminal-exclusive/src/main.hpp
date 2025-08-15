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
#include <thread>
#include <chrono>
#include <sstream>


typedef std::vector<int> mapLine;
typedef std::vector<mapLine> map;

const int msr = 10;
const int hmsr = msr / 2;
//msr=map size rate, scaling map is nessary for player to walk free

const int targetFPS = 30;
const auto frameDuration = std::chrono::milliseconds(1000 / targetFPS);


class Main
{
private:
    float range = 60; // how wide is the view (fov in minecraft)
    float rate; // how detailed is the view

    int angle = 0;
    map Map;

    float pos[2] = {msr * 1.5, msr * 1.5};
    // size of map and pos of player are both after scaling

public:
    Main(std::string);// Constructor 
    
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