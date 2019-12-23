/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using namespace std;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool ifVisited(unsigned x, unsigned y);
  void setVisited(unsigned x, unsigned y);
  PNG * getPng();
  double getTolerance();

private:
	/** @todo [Part 1] */
	/** add private members here*/
  vector<vector<bool>> visited;
  PNG picture;
  double tlr;
  Point head;
  stack<Point> travis;

};
