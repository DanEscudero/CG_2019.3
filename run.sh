#!/bin/bash

LAB=${1:-1}
MAIN_FILE=${2:-"main"}

cd lab$1
g++ $MAIN_FILE.cpp -o out.out -lGL -lglfw -lGLEW && ./out.out
cd ..