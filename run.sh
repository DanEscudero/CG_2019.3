#!/bin/bash

cd lab$1
g++ main.cpp -o out.out -lGL -lglfw -l GLEW
./out.out
cd ..