/* Your code here! */
#pragma once

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>

using namespace std;
using namespace cs225;

class SquareMaze {
  public:
      SquareMaze ();
      void 	makeMaze (int width, int height);
      bool 	canTravel (int x, int y, int dir) const;
      void 	setWall (int x, int y, int dir, bool exists);
      vector<int> solveMaze ();
      void solveMazeHelper(vector<vector<pair<int, int>>> * solution, pair<unsigned, unsigned> start);
      PNG * drawMaze () const;
      PNG * drawMazeWithSolution ();
      PNG * drawCreativeMaze (unsigned int num) const;


  private:
      vector<vector<vector<bool>>> walls;
      DisjointSets * dsets;
      int height;
      int width;
      int convert2Dto1D(int x, int y) const ;
		  pair<int,int> convert1Dto2D(int position) const ;
      vector<int> findShortestPath();
      int reverseDirection(int dir);

};
