g++ -c ./src/main.cpp ./src/loadMap.cpp ./src/logic.cpp ./src/sfmlDisplay.cpp ./src/terminal.cpp
g++ ./main.o ./loadMap.o ./logic.o ./sfmlDisplay.o ./terminal.o -o raycast -lsfml-graphics -lsfml-window -lsfml-system
rm ./main.o ./loadMap.o ./logic.o ./sfmlDisplay.o ./terminal.o
./raycast -t