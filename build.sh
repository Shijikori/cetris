#!/bin/bash
g++ -o cetris app.cpp -lglfw -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lsfml-audio -lsfml-system -I libs -Wall