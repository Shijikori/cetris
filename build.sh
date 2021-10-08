#!/bin/bash
g++ -o app app.cpp -lglfw -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lsfml-audio -lsfml-system -I libs -Wall