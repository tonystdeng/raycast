#include "main.hpp"


bool Main::terminalMain() {
    auto frameStart = std::chrono::steady_clock::now();

    int maxH = 24; // height of graphic in terminal in unit of char
    int hmaxH = maxH / 2;
    std::vector<std::pair<float, int>> rectangles = tdLoader(maxH);// load three-d
    char color;

    std::cout << "\033[2J";
    for (int row = -hmaxH; row < hmaxH; row++) {
        

        for (int i = 0; i < rectangles.size(); i++) {

            auto [height, wallType] = rectangles[i]; 
            // get slice (std::pair<float, int>)

            // check if this rectangle is tall enough to print on this row
            if (height / 2 <= std::abs(row)) {
                std::cout << ' ';
                continue;
            }

            // set color based on wall type (if corner, the color stays as the last one)
            switch(wallType){
                case 1:
                    color = '@';
                    break;
                case 2:
                    color = '=';
                    break;
            }
            std::cout << color;
        }std::cout << '\n';
    }
    
    sfmlInput();

        // --- End render ---
    auto frameEnd = std::chrono::steady_clock::now();
    auto workTime = frameEnd - frameStart;

    // Sleep if frame rendered too quickly
    if (workTime < frameDuration) {
        std::this_thread::sleep_for(frameDuration - workTime);
    }
    return true;
}


char getch() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Turn off line buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal
    return c;
}

void Main::terminalInput(float speed) {
    float radians;

    char c = getch();  // read one key without Enter

    // rotation
    if (c == '\033') {              // arrow key sequence
        getch();                    // skip '['
        char arrow = getch();       // get actual arrow
        if (arrow == 'D') angle -= speed;     // left
        else if (arrow == 'C') angle += speed; // right
    }

    // movement
    speed *= 0.6;
    switch (c) {
        case 'w': movePlayer(0, speed); break;
        case 'd': movePlayer(1, speed); break;
        case 's': movePlayer(2, speed); break;
        case 'a': movePlayer(3, speed); break;
    }
}
