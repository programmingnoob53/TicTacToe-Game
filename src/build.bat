@echo off

if not exist ..\bin mkdir ..\bin
if exist gmc.cache rmdir \s \q gmc.cache

echo compiling...

g++ -std=c++20 -fmodules-ts TicTacToe.cpp -c
g++ -std=c++20 -fmodules-ts GameHandler.cpp -c
g++ -std=c++20 -fmodules-ts main.cpp -c

g++ -std=c++20 -fmodules-ts *.o -o ..\bin\app.exe

if exist *.o del *.o
if exist gmc.cache rmdir \s \q gmc.cache

echo DONE BAKING...

echo RUNNING

..\bin\app.exe