#include "main.hpp"

// stands for three-d loader
std::vector<std::pair<float, int>> Main::tdLoader(int maxH) {
    std::vector<std::pair<float, int>> rectangles;
    std::pair<float, int> tempRect;
    float sight, height;
    float angleStart = angle - range / 2;       // start of field of view
    int index = 0;
    int cubed = Map[0].size() / msr * Map.size() / msr;    // map size

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
        float sight[2] = {std::sin(radians) * h + pos[0]
                        , std::cos(radians) * h + pos[1]};
        int x = std::round(sight[0]);
        int y = std::round(sight[1]);
        int spot = Map[x][y];                   // get map value
        if (spot) {                             // if hit a wall
            return {h, spot};                   // return distance and wall type
        }
    }
}

bool Main::movePlayer(int direction, float speed){
    float orgpos[2] = {pos[0], pos[1]}; // original position

    float radians = (90 - angle - (90 * direction)) * (PI / 180);
    pos[0] += std::sin(radians) * speed;
    pos[1] += std::cos(radians) * speed;

    // collision with wall occurs
    if (Map[std::round(pos[0])][std::round(pos[1])]) {
        std::copy(std::begin(orgpos), std::end(orgpos), pos);
        return false;
    }return true;
}