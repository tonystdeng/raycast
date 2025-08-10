# C++ Terminal & Graphical 3D Engine with Raycasting  .v1.0

## Project Explanation

Its a simple 3D engine coded in C++ that renders 3D graphic by the raycasting algorithm that works in **Linux & MacOS**.

It works in both **Terminal and GUI** with fluid animation and takes keyboard input for movement.

## How to use

**Map Management**

This application reads a **CSV** file to load a virtual 2D world for you to explore.

- Run simple script `./initMap.py`(with python and pandas installed) to recieve a blank **8 x 8** world as a CSV file to edit.

- You need to always make sure that there is a file named `map.csv` in the same folder as the application for it to work.

- To add walls in your virtual world, simply change 0 to 1 in the CSV file. Feel free to extend the world also.

**Run App** 

- Make sure you have `sfml`(gui support) installed.
- In the same folder with the executable file `raycast`, make sure you have `map.csv` as mentioned in **Map Management**
- Run `./raycast`  in terminal for sfml supported GUI
- Run `./raycast -t`  instead for in terminal graphic