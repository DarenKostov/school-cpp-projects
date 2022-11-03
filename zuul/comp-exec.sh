#!/bin/sh
g++ *.cpp -o main.elf -g

if [ "$1" = "-d" ]; then
  gdb "$PWD"/main.elf
else
  "$PWD"/main.elf
fi

