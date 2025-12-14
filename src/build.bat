@echo off
if not exist ..\GameAPP mkdir ..\GameAPP
g++ -std=c++20 -fmodules-ts -c GenericsProto.cpp
g++ -std=c++20 -fmodules-ts -c TicTacToe.cpp
g++ -std=c++20 -fmodules-ts -c main.cpp

g++ -std=c++20 -fmodules-ts -o ..\GameAPP\App GenericsProto.o Tic-Tac-Toe.o main.o 

if exist *.o del *.o
..\GameAPP\App
