#sudo pacman -Syu sfml

g++ -c ./src/main.cpp ./src/loadMap.cpp ./src/logic.cpp ./src/sfmlDisplay.cpp ./src/terminal.cpp
g++ ./main.o ./loadMap.o ./logic.o ./sfmlDisplay.o ./terminal.o -o mainExecutable  \
    -static-libgcc -static-libstdc++ \
    -lsfml-graphics -lsfml-window -lsfml-system

rm ./main.o ./loadMap.o ./logic.o ./sfmlDisplay.o ./terminal.o

mkdir -p bin
mv mainExecutable bin

cp /usr/lib/libsfml-graphics.so* /usr/lib/libsfml-window.so* /usr/lib/libsfml-system.so* bin/
#sudo pacman -Rns sfml

bash raycast-app.bash