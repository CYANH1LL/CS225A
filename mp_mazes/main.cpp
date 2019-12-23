#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here

    SquareMaze maze;

    maze.makeMaze(50, 50);


    PNG * image = maze.drawCreativeMaze(3);
    image->writeToFile("creative.png");

    delete image;
    return 0;
}
