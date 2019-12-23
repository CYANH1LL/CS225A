/* Your code here! */
#include "maze.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <queue>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze () {
    dsets = new DisjointSets();
    height = 0;
    width = 0;
}

int SquareMaze::convert2Dto1D(int x, int y) const {
    return y + x * height;
}

pair<int,int> SquareMaze::convert1Dto2D(int index) const {
    return pair<int, int> (index / height, index % height);
}

void 	SquareMaze::makeMaze (int width, int height) {
    this->height = height;
    this->width = width;

    walls = vector<vector<vector<bool>>>(width);
    for (int x = 0; x < width; x++) {
    		walls[x] = vector<vector<bool>>(height);
    		for (int y = 0; y < height; y++) {
            //0 is right wall, 1 is down wall
      			walls[x][y] = vector<bool>(2);
      			walls[x][y][0] = true;
      			walls[x][y][1] = true;
    		}
  	}

  	dsets->addelements(width * height);
  	int numOfSets = width * height;


    while (numOfSets > 1) {
          for (int random_x = 0; random_x < width; random_x++) {
            for (int random_y = 0; random_y < width; random_y++) {
              int random_dir = rand() % 2;

              if (walls[random_x][random_y][random_dir] == true) {

                  int index = convert2Dto1D(random_x, random_y);
                  //remove right wall
                  if (random_x < width - 1 && random_dir == 0) {

                    int rightIndex = convert2Dto1D(random_x + 1, random_y);
                    if (dsets->find(index) != dsets->find(rightIndex)) {
                      numOfSets -= 1;
                      dsets->setunion(index, rightIndex);
                      walls[random_x][random_y][0] = false;
                    }

                  }

                  //remove down wall
                  if (random_y < height - 1 && random_dir == 1) {

                    int downIndex = convert2Dto1D(random_x, random_y + 1);
                    if (dsets->find(index) != dsets->find(downIndex)) {
                      numOfSets -= 1;
                      dsets->setunion(index, downIndex);
                      walls[random_x][random_y][1] = false;
                    }

                  }

              }
            }

    }

}
}


bool 	SquareMaze::canTravel (int x, int y, int dir) const {
    if (((x >= 0) && (x < width)) && ((y >= 0) && (y < height))) {

        if (dir == 0 && x + 1 < width && walls[x][y][0] == false) {
          return true;
        } else if (dir == 1 && y + 1 < height && walls[x][y][1] == false) {
          return true;
        } else if (dir == 2 && x - 1 >= 0 && walls[x - 1][y][0] == false) {
          return true;
        } else if (dir == 3 && y - 1 >= 0 && walls[x][y - 1][1] == false) {
          return true;
        }

    }
    return false;
}

void 	SquareMaze::setWall (int x, int y, int dir, bool exists) {
    if (((x >= 0) && (x < width)) && ((y >= 0) && (y < height))) {
      walls[x][y][dir] = exists;
    }

}

int SquareMaze::reverseDirection(int dir) {
  if (dir == 0) {
    return 2;
  } else if (dir == 1) {
    return 3;
  } else if (dir == 2) {
    return 0;
  } else if (dir == 3) {
    return 1;
  } else {
    return -1;
  }

}

vector<int> SquareMaze::findShortestPath() {
    vector<int> path;
    // A map containing the distance and parent of each coordinate
    vector<vector<pair<int, int>>> dist_pre_map;
    //Map initialization
  	for (int x = 0; x < width; x++) {
    		dist_pre_map.push_back(vector<pair<int, int>>());
    		for (int y = 0; y < height; y++) {
    			   dist_pre_map.back().push_back(pair<int, int>(-1,-1));
    		}
  	}

  	solveMazeHelper(&dist_pre_map, pair<int, int>(0,0));
  	pair<int, int> cur_pair(0, height - 1);
  	int cur_largest_distance = dist_pre_map[0][height - 1].first;




  	for (int x = 0; x < width; x++) {

  		if (dist_pre_map[x][height-1].first > cur_largest_distance) {

  			cur_largest_distance = dist_pre_map[x][height - 1].first;
  			cur_pair = pair<int, int>(x, height - 1);

  		}

  	}


	while (cur_pair != pair<int, int>(0,0)) {

		int x = cur_pair.first;
		int y = cur_pair.second;
		int parent_dir = dist_pre_map[x][y].second;
		int dir = -1;
    //backtrace the direction
		dir = reverseDirection(parent_dir);

		path.push_back(dir);

    if (parent_dir == 0) {
      cur_pair = pair<int, int>(x + 1, y);
    } else if (parent_dir == 1) {
      cur_pair = pair<int, int>(x, y + 1);
    } else if (parent_dir == 2) {
      cur_pair = pair<int, int>(x - 1, y);
    } else if (parent_dir == 3) {
      cur_pair = pair<int, int>(x, y - 1);
    }


	}

  return path;
}


vector<int> SquareMaze::solveMaze () {
  vector<int> path = findShortestPath();
	reverse(path.begin(), path.end());
	return path;

}

void SquareMaze::solveMazeHelper(vector<vector<pair<int, int>>> * dist_pre_map, pair<unsigned, unsigned> start) {

	int x = start.first;
	int y = start.second;
	// Check base case where we reach end
	if ((!canTravel(x, y, 0) || (*dist_pre_map)[x + 1][y].second == 0) &&
		(!canTravel(x, y, 1) || (*dist_pre_map)[x][y + 1].second == 1) &&
		(!canTravel(x, y, 2) || (*dist_pre_map)[x - 1][y].second == 2) &&
		(!canTravel(x, y, 3) || (*dist_pre_map)[x][y - 1].second == 3) ) {
		return;
	}
	// Check each direction, if can travel, then travel
	pair<int, int> cur_pair = (*dist_pre_map)[x][y];
	// right
	if (canTravel(x, y, 0) && (*dist_pre_map)[x + 1][y].first == -1) {

		(*dist_pre_map)[x + 1][y] = pair<int, int>(cur_pair.first + 1, 2);
		solveMazeHelper(dist_pre_map, pair<int, int>(x + 1, y));

	}
	// down
	if (canTravel(x, y, 1) && (*dist_pre_map)[x][y + 1].first == -1) {

		(*dist_pre_map)[x][y + 1] = pair<int, int>(cur_pair.first + 1, 3);
		solveMazeHelper(dist_pre_map, pair<int, int>(x, y + 1));

	}
	// left
	if (canTravel(x, y, 2) && (*dist_pre_map)[x - 1][y].first == -1) {

		(*dist_pre_map)[x - 1][y] = pair<int, int>(cur_pair.first + 1, 0);
		solveMazeHelper(dist_pre_map, pair<int, int>(x - 1, y));

	}
	// up
	if (canTravel(x, y, 3) && (*dist_pre_map)[x][y - 1].first == -1) {

		(*dist_pre_map)[x][y - 1] = pair<int, int>(cur_pair.first + 1, 1);
		solveMazeHelper(dist_pre_map, pair<int, int>(x, y - 1));

	}
}

PNG * SquareMaze::drawMaze () const {

    PNG * maze = new PNG(width * 10 + 1, height * 10 + 1);

    for (int x = 0; x < width; x++) {
    		for (int y = 0; y < height; y++) {
            if (y == 0) {
                for (int k = 0; k < 10; k++) {
                  if ((x * 10 + k < 1) || (x * 10 + k > 9)) {
                    HSLAPixel & pixel = maze->getPixel(x * 10 + k, 0);
                    pixel.h = 0;
          					pixel.s = 0;
                    pixel.l = 0;
                  }
                }
            }

            if (x == 0) {
                for (int k = 0; k < 10; k++) {
                  HSLAPixel & pixel = maze->getPixel(0, y * 10 + k);
                  pixel.h = 0;
        					pixel.s = 0;
                  pixel.l = 0;
                }
            }

      			if (!canTravel(x, y, 0)) {
        				for (int k = 0; k <= 10; k++) {
        					HSLAPixel & pixel = maze->getPixel((x + 1) * 10, y * 10 + k);
        					pixel.h = 0;
        					pixel.s = 0;
        					pixel.l = 0;
        				}
      			}
      			if (!canTravel(x, y, 1)) {
        				for (int k = 0; k <= 10; k++) {
        					HSLAPixel & pixel = maze->getPixel(x * 10 + k, (y + 1) * 10);
        					pixel.h = 0;
        					pixel.s = 0;
        					pixel.l = 0;
        				}
      			}
    		}
  	}

    return maze;
}

PNG * SquareMaze::drawMazeWithSolution () {

  PNG * maze = drawMaze();
  vector<int> path = solveMaze();
  int x = 5;
	int y = 5;
  int i;

  for (auto itr : path) {
    if (itr == 0) {
        for (i = 0; i < 10; i++) {
  				HSLAPixel & pixel = maze->getPixel(x, y);
  				pixel.h = 0;
  				pixel.s = 1;
  				pixel.l = 0.5;
          x++;
  			}

    } else if (itr == 1) {
        for (i = 0; i < 10; i++) {
          HSLAPixel & pixel = maze->getPixel(x, y);
  				pixel.h = 0;
  				pixel.s = 1;
  				pixel.l = 0.5;
          y++;
        }

    } else if (itr == 2) {
        for (i = 0; i < 10; i++) {
          HSLAPixel & pixel = maze->getPixel(x, y);
  				pixel.h = 0;
  				pixel.s = 1;
  				pixel.l = 0.5;
          x--;
  			}

    } else if (itr == 3) {
        for (i = 0; i < 10; i++) {
          HSLAPixel & pixel = maze->getPixel(x, y);
  				pixel.h = 0;
  				pixel.s = 1;
  				pixel.l = 0.5;
          y--;
        }
    }
  }

  HSLAPixel & pixel = maze->getPixel(x, y);
	pixel.h = 0;
	pixel.s = 1.0;
	pixel.l = 0.5;

	x -= 4;
	y += 5;
	for (i = x; i < x + 9; i++) {
		HSLAPixel & pixel = maze->getPixel(i, height * 10);
		pixel.l = 1.0;
	}

  return maze;
}

PNG * SquareMaze::drawCreativeMaze (unsigned int num) const {

  PNG * maze = new PNG(width * 10 + 1, height * 10 + 1);

  for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
          if (y == 0) {
              for (int k = 0; k < 10; k++) {
                if ((x * 10 + k < 1) || (x * 10 + k > 9)) {
                  HSLAPixel & pixel = maze->getPixel(x * 10 + k, 0);
                  pixel.h = 0;
                  pixel.s = 0;
                  pixel.l = 0;
                }
              }
          }


          if (x == 0) {
              for (int k = 0; k < 10; k++) {
                HSLAPixel & pixel = maze->getPixel(0, y * 10 + k);
                pixel.h = 0;
                pixel.s = 0;
                pixel.l = 0;
              }
          }

          if (!canTravel(x, y, 0)) {
              for (int k = 0; k <= 10; k++) {
                HSLAPixel & pixel = maze->getPixel((x + 1) * 10, y * 10 + k);
                pixel.h = 0;
                pixel.s = 0;
                pixel.l = 0;
              }
          }
          if (!canTravel(x, y, 1)) {
              for (int k = 0; k <= 10; k++) {
                if (y == height - 1 && x == width - 1) {
                  break;
                }
                HSLAPixel & pixel = maze->getPixel(x * 10 + k, (y + 1) * 10);
                pixel.h = 0;
                pixel.s = 0;
                pixel.l = 0;
              }
          }
      }
  }


    PNG * output = new PNG(maze->width() * num, maze->height() * num);

    for (unsigned int i = 0; i < num; i++) {
      for (unsigned int x = 0; x < maze->width(); x++) {
        for (unsigned int y = 0; y < maze->height(); y++) {

            HSLAPixel & pixel = output->getPixel(i * (maze->width() - 10) + x, i * maze->height() + y);
            pixel = maze->getPixel(x, y);


        }
      }
    }



    return output;
}
