#include <cmath>
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

 MyColorPicker::MyColorPicker(int interval) : interval(interval) {

 }
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  if ( ((x + y) % interval) % 2 == 1) {
    HSLAPixel pixel(0, 0, 1);
    return pixel;
  } else {
    HSLAPixel pixel2(0, 0, 0);
    return pixel2;
  }

}
