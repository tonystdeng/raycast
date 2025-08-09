#include <iostream>
#include <chrono>
#include <thread>

int main() {
    const int width = 40;

    while (true) {
        for (int i = 0; i < width; ++i) {
            std::cout << "\033[2J\033[1;1H";  // Clear screen and move cursor
            for (int j = 0; j < i; ++j) std::cout << ' ';
            std::cout << "o\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    return 0;
}
