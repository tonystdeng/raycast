#include "main.hpp"

// stands for three-d loader
std::vector<std::pair<float, int>> Main::tdLoader(int maxH) {
    std::vector<std::pair<float, int>> rectangles;
    std::pair<float, int> tempRect;
    float sight, height;
    float angleStart = angle - range / 2;       // start of field of view
    int index = 0;
    int cubed = size.x / msr * size.y / msr;    // map size

    // cast rays across the field of view
    for (float i = 0; i < range; i += rate) {
        auto [dist, wallType] = gcr(i + angleStart); // get raycast result
        float dif = i + angleStart - angle;         // get angle differeReplacing all error codes with jokes    nce
        if (dif < 0) dif += 360;                    // normalize angle
        if (dif > 360) dif -= 360;
        sight = dist * std::cos(dif * (PI / 180));  // fix fisheye effect
        height = (cubed * maxH) / sight / msr;      // calculate rectangle height
        if (height > maxH) height = maxH;           // limit height at window height

        tempRect.first = height; // rect height
        tempRect.second = wallType; // walltype(obviously)
        
        // add rect to list
        rectangles.push_back(tempRect);
        index++;
    }
    return rectangles;
}

// performs raycasting on a single angle (gcr stands for get closest reach)
std::pair<float, int> Main::gcr(float rayAngle) {
    float radians = (90 - rayAngle) * (PI / 180);
    for (float h = 0; ; h += 0.05) {            // taking steps
        sf::Vector2f sight(std::sin(radians) * h, std::cos(radians) * h);
        sight += pos;                           // ray position in map
        int x = std::round(sight.x);
        int y = std::round(sight.y);
        int spot = Map[x][y];                   // get map value
        if (spot) {                             // if hit a wall
            return {h, spot};                   // return distance and wall type
        }
    }
}

bool Main::movePlayer(int direction, float speed){
    sf::Vector2f orgpos = pos; // original position

    float radians = (90 - angle - (90 * direction)) * (PI / 180);
    sf::Vector2f offset(std::sin(radians) * speed, std::cos(radians) * speed);
    pos += offset;

    // collision with wall occurs
    if (Map[std::round(pos.x)][std::round(pos.y)]) {
        pos = orgpos;
        return false;
    }return true;
}