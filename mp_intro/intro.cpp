#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;
void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG* original = new PNG();
  original->readFromFile(inputFile);

  unsigned width = original->width();
  unsigned height = original->height();

  PNG* output = new PNG(width, height);

  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
          // find the corresponding pixel from input and output PNG
          HSLAPixel&  inputPixel = original->getPixel(x, y);
          //another way to apply this function:
          // HSLAPixel* temp = new HSLAPixel(inputPixel.h, inputPixel.s, inputPixel.l, inputPixel.a);
          HSLAPixel&  outputPixel = output->getPixel(width - x - 1, height - y - 1);
          outputPixel = inputPixel;
          // outputPixel = *temp;

          }
      }
      // Save the output file
      output->writeToFile(outputFile);

      // Clean up memory
      delete output;
      delete original;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
          if (x >= y) {
            HSLAPixel* c = new HSLAPixel((x + y) % 180, 0.5, 0.5, 1);
            png.getPixel(x, y) = *c;
          } else {
            HSLAPixel* c = new HSLAPixel((x - y) % 180 + 180, 0.5, 0.5, 1);
            png.getPixel(x, y) = *c;
          }

      }
  }
  return png;
}
