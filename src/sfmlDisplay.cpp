#include "main.hpp"


// main loop
bool Main::sfmlMain() {
    while (const std::optional<sf::Event> event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
            return false;
        }
    }
    sfmlInput();

    int maxH = wSize.size.y;
    std::vector<std::pair<float, int>> rectangles = tdLoader(maxH);// load three-d
    float rectx = wSize.size.x / range * rate;   // width of each rectangle
    sf::Color color;

    window->clear(sf::Color::Black);
    for (int i = 0; i < rectangles.size(); i++) {

        auto [height, wallType] = rectangles[i]; 
        // get slice (std::pair<float, int>)

        // make sfml rect
        sf::RectangleShape tempRect;
        tempRect.setSize(sf::Vector2f(rectx, height));
        tempRect.setPosition({i * rectx, (wSize.size.y - height) / 2});

        // set color based on wall type (if corner, the color stays as the last one)
        switch(wallType){
            case 1:
                color = sf::Color(150,0,0);
                break;
            case 2:
                color = sf::Color(250,50,50);
                break;
        }
        tempRect.setFillColor(color);
        window->draw(tempRect);
    } 
    window->display();
    return true;
}

void Main::sfmlInput(float speed) {
    float radians;


    // rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        angle -= speed; 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        angle += speed;
    }
    
    // movement
    speed *= 0.6;
    for (int i = 0; i < 4; ++i) {
        if (sf::Keyboard::isKeyPressed(keys[i])) {
            movePlayer(i, speed);
        }
    }
}