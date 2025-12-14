# TicTacToe C++ (Modules)

A simple console-based TicTacToe game built in modern C++ using modules.

---

## Features
- 2-player turn system
- Modular design with `TicTacToe` (game logic) and `GameHandler` (input/flow)
- Dynamic grid handling
- Input validation
- Console-based gameplay

---

## Controls
Top Row: q - Top Left w - Top Center e - Top Right
Middle Row: a - Mid Left s - Mid Center d - Mid Right
Bottom Row: z - Bot Left x - Bot Center c - Bot Right
f - Quit

---
## Build Instructions
Requires a **C++20 compiler** with module support (e.g., g++ 12+).

Example:

- Run the provided `build.bat`  
Or using command line:

```bash
g++ -std=c++20 -fmodules-ts GenericsProto.cpp -c
g++ -std=c++20 -fmodules-ts TicTacToe.cpp -c
g++ -std=c++20 -fmodules-ts main.cpp -c
g++ -std=c++20 -fmodules-ts *.o -o App
./App

