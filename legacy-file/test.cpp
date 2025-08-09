#include <iostream>
#include <unistd.h>
#include <termios.h>

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

void handleInput() {
    while (true) {
        char c = getch();
        
        if (c == '\033') { // Escape sequence (arrow keys)
            getch();       // skip [
            char arrow = getch();
            switch (arrow) {
                case 'A': std::cout << "Up arrow\n"; break;
                case 'B': std::cout << "Down arrow\n"; break;
                case 'C': std::cout << "Right arrow\n"; break;
                case 'D': std::cout << "Left arrow\n"; break;
            }
        } else {
            switch (c) {
                case 'w': std::cout << "W key\n"; break;
                case 'a': std::cout << "A key\n"; break;
                case 's': std::cout << "S key\n"; break;
                case 'd': std::cout << "D key\n"; break;
                case 'q': return; // Quit on 'q'
                default: std::cout << "Other key: " << c << "\n";
            }
        }
    }
}

int main() {
    std::cout << "Press keys (WASD or arrow keys). Press 'q' to quit.\n";
    handleInput();
}
