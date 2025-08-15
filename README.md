# C++ Terminal & Graphical 3D Engine with Raycasting  .v1.0

## Project Explanation

Its a simple 3D engine coded in C++ that renders 3D graphic by the raycasting algorithm that works in **Linux**.

It works in both **Terminal and GUI** with fluid animation and takes keyboard input for movement.

## How to use

**Map Management**

This application reads a **CSV** file to load a virtual 2D world for you to explore.

- Run simple script `./initMap.py`(with python and `requirements.txt` installed) to recieve a blank **8 x 8** world as a CSV file to edit
- You can use the default testing maps avalible, but be sure to change the file name to `map.csv`.
- You need to always make sure that there is a file named `map.csv` in the same folder as the application for it to work.
- To add walls in your virtual world, simply change 0 to 1 in the CSV file. Feel free to extend the world also.

**Run App** 

- In the same folder with the application, make sure you have `map.csv` as mentioned in **Map Management**
- All together in the same folder, you should have `map.csv`, `bin` with all the executables, and `raycast-app.bash` as a trigger script.
- Execute script `raycast-app.bash`  in terminal for sfml supported GUI, or add parameter `-t` (`raycast-app.bash -t`)  instead for in terminal graphic(use Ctrl-C to exit).
  
  The terminal exclusive version won't react to any parameter, it only ports into  terminal mode.

**Compile App**

Normal version:

- Have `g++`&`sfml>=3.0.0` installed on your system.

- Run `run.bash` which should produce a `bin` folder.

- Done, run with instructions from **Run App**.

Terminal exclusive:

- Have `g++` installed (its just plane c++).

- Cd into the `terminal-exclusive` folder in terminal.

- Same thing, Run `run.bash` and done.
