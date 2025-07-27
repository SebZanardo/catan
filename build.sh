#!/bin/sh

# Define the files to compile in one place here
SOURCES="src/main.c src/game.c src/cards.c src/board.c src/player.c src/lookup.c"

LINUX="linux"
MACOS="macos"
WINDOWS="windows"

help() {
    echo "Please specify a valid target platform:"
    echo "$0 $LINUX"
    echo "$0 $MACOS"
    echo "$0 $WINDOWS"
    exit 1
}

if [ -z $1 ]; then
    help

elif [ $1 = $LINUX ]; then
    # https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
    cc $SOURCES -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -o game

elif [ $1 = $MACOS ]; then
    # https://github.com/raysan5/raylib/wiki/Working-on-macOS
    eval cc $SOURCES -framework IOKit -framework Cocoa -framework OpenGL $(pkg-config --libs --cflags raylib) -Wall -o game

elif [ $1 = $WINDOWS ]; then
    # https://github.com/raysan5/raylib/wiki/Working-on-Windows
    gcc $SOURCES -lraylib -lgdi32 -lwinmm -Wall -o game.exe

else
    help
fi

# Exit the script if the last command was unsuccessful
if [ $? -ne 0 ]; then
    echo "Failed to build"
    exit 1
fi

# Run compiled game
if [ $1 = $LINUX ]; then
    ./game
elif [ $1 = $MACOS ]; then
    ./game
elif [ $1 = $WINDOWS ]; then
    ./game.exe
fi
