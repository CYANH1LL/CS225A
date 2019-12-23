#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : travis(NULL), ifFinished(true) {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, const Point start)
	:travis(&traversal), head(start), ifFinished(false) {
	curr = traversal.peek();
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point point = travis->pop();
  travis->setVisited(point.x, point.y);

  int x_coord = (int)point.x;
  int y_coord = (int)point.y;

  Point right(x_coord + 1, y_coord);
  Point left(x_coord - 1, y_coord );
  Point above(x_coord, y_coord - 1);
  Point below(x_coord, y_coord + 1);

  PNG * picture = travis->getPng();
  int w = picture->width();
  int h = picture->height();
  HSLAPixel & p1 = picture->getPixel(head.x, head.y);
  double tlr = travis->getTolerance();

  // if ((int)right.x < w && calculateDelta(p1, picture->getPixel(right.x, right.y)) < tlr && !travis->ifVisited(right.x, right.y)) {
  if ((int)right.x < w && calculateDelta(p1, picture->getPixel(right.x, right.y)) < tlr) {
    travis->add(right);
  }

  // if ((int)below.y < h && calculateDelta(p1, picture->getPixel(below.x, below.y)) < tlr && !travis->ifVisited(below.x, below.y)) {
  if ((int)below.y < h && calculateDelta(p1, picture->getPixel(below.x, below.y)) < tlr) {
    travis->add(below);
  }

  // if ((int)left.x >= 0  && calculateDelta(p1, picture->getPixel(left.x, left.y)) < tlr && !travis->ifVisited(left.x, left.y)) {
  if ((int)left.x >= 0  &&  calculateDelta(p1, picture->getPixel(left.x, left.y)) < tlr) {
    travis->add(left);
  }

  // if ((int)above.y >= 0 && calculateDelta(p1, picture->getPixel(above.x, above.y)) < tlr && !travis->ifVisited(above.x, above.y)) {
  if ((int)above.y >= 0 &&  calculateDelta(p1, picture->getPixel(above.x, above.y)) < tlr) {
    travis->add(above);
  }

  while(!travis->empty() && (travis->ifVisited(travis->peek().x, travis->peek().y))) {
    travis->pop();
  }
  if (travis->empty()) {
    ifFinished = true;
    return *this;
  }
  curr = travis->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  return !(ifFinished && other.ifFinished);
}
