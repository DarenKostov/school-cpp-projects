#!/bin/sh
g++ -o $1 $1.cpp

#for windows
./$1.exe

#for linux
./$1
