#include "main.hpp"


// load map.csv
map Main::getMap() {
    std::ifstream mapFile("map.csv");
    map mapVector; 
    std::string tempX, tempY;
    int lineIndex = 0;

    // read lines from the CSV file
    while (std::getline(mapFile, tempX)) {
        mapVector.push_back(mapLine{});      
        std::istringstream tempStream(tempX);
        mapVector[lineIndex].push_back(1); 
        while (std::getline(tempStream, tempY, ',')) {
            mapVector[lineIndex].push_back(std::stoi(tempY));
        }
        mapVector[lineIndex].push_back(1);
        lineIndex++;
    }

    // add border walls
    mapLine line(mapVector[0].size(), 1); 
    mapVector.insert(mapVector.begin(), line);
    mapVector.push_back(line);  

    return mapVector;
}

// scale map for smoother movement
map Main::scaleMap(map mapVector) {
    mapLine tempLine(mapVector[0].size() * msr, 0); // init row
    map Map(mapVector.size() * msr, tempLine);      // init map

    // each cell
    for (int Y = 0; Y < mapVector.size(); Y++) {
        for (int X = 0; X < mapVector[Y].size(); X++) {
            if (mapVector[Y][X]) {                  // if cell is a wall
                // fill block with shading values
                for (int y = 0; y < msr; y++) {
                    for (int x = 0; x < msr; x++) {
                        float yg = (y < hmsr) ? std::abs(hmsr - y) : y - hmsr;
                        float xg = (x < hmsr) ? std::abs(hmsr - x) : x - hmsr;
                        int shade = (yg > xg) + 1;  // Determine shade (1 or 2)
                        Map[y + Y * msr][x + X * msr] = shade;
                    }
                }
                // add specific nodes (value 3) at corners and edges
                Map[Y * msr][X * msr] = 3;
                Map[Y * msr + msr - 1][X * msr] = 3;
                Map[Y * msr][X * msr + msr - 1] = 3;
                Map[Y * msr + msr - 1][X * msr + msr - 1] = 3;
                Map[Y * msr + 1][X * msr + 1] = 3;
                Map[Y * msr + msr - 2][X * msr + 1] = 3;
                Map[Y * msr + 1][X * msr + msr - 2] = 3;
                Map[Y * msr + msr - 2][X * msr + msr - 2] = 3;
            }
        }
    }
    return Map;
}
