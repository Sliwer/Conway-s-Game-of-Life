#include <iostream>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


char** initWorld(int width, int height, int fillPercent);
void updateWorld(char **world, int w, int h);
void drawWorld(char **world, int width, int height);
void clrscr();

int main(int argc, char *argv[])
{
    int worldSizeX = 70, worldSizeY = 40, fillPercent = 60;
    if (argc > 2) {
        worldSizeX = strtol(argv[1], nullptr, 0);
        worldSizeY = strtol(argv[2], nullptr, 0);
        fillPercent = strtol(argv[3], nullptr, 0);
    }
    srand(time(NULL));


    // Initailize the world with empty spaces and living creatures(#)
    char **world = initWorld(worldSizeX, worldSizeY, fillPercent);

    // Run the simulation
    while (true) {
        updateWorld(world, worldSizeX, worldSizeY);
        drawWorld(world, worldSizeX, worldSizeY);

        usleep(50000);
        clrscr();
    }

    return 0;
}

// Initialize the world 
char** initWorld(int width, int height, int fillPercent)
{
    char **outer_arr = (char**) malloc(height * sizeof(char*));

    for (int i = 0; i < height; i++) {
        outer_arr[i] = (char*) malloc(width * sizeof(char));
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 100 < fillPercent)
                outer_arr[i][j] = '.';
            else 
                outer_arr[i][j] = '#';
        }
    }

    return outer_arr;
}

// Update the world
void updateWorld(char **world, int w, int h)
{
    // For now we will chech all squares except the border
    for (int i = 1; i < h - 1; i++) {
        for (int j = 1; j < w - 1; j++) {
            int live = 0, dead = 0;
            (world[i - 1][j - 1] == '.') ? dead++ : live++;
            (world[i - 1][j] == '.') ? dead++ : live++;
            (world[i - 1][j + 1] == '.') ? dead++ : live++;
            (world[i][j - 1] == '.') ? dead++ : live++;
            (world[i][j + 1] == '.') ? dead++ : live++;
            (world[i + 1][j - 1] == '.') ? dead++ : live++;
            (world[i + 1][j - 1] == '.') ? dead++ : live++;
            (world[i + 1][j + 1] == '.') ? dead++ : live++;

            if (live == 3) {
                world[i][j] = '#'; 
            } else if (live == 2 && world[i][j] == '#') {
                world[i][j] = '#';
            } else 
                world[i][j] = '.';
        }
    }
}

// Draw the world
void drawWorld(char **world, int width, int height)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << world[i][j];
        }
        std::cout << "\n";
    }
}

// Used to clear the screen
void clrscr()
{
    system("clear");
}