g++ -c ./src/main.cpp ./src/loadMap.cpp ./src/logic.cpp ./src/terminal.cpp
g++ ./main.o ./loadMap.o ./logic.o ./terminal.o -o mainExecutable  \
    -static-libgcc -static-libstdc++

rm ./main.o ./loadMap.o ./logic.o ./terminal.o

mkdir -p bin
mv mainExecutable bin


# bash raycast-app.bash