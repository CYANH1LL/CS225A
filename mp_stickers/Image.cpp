#include "Image.h"
#include <cmath>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;


// Image::Image() : PNG() {
//
// }
//
// Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {
//
//
// }
//
// Image::Image(Image const & other) : PNG(other){
//
// }


void Image::lighten() {

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {

            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l <= (1.0 - 0.1)) {
                pixel.l += 0.1;
            } else {
                pixel.l = 1.0;
            }

        }
    }

}

void Image::lighten(double amount) {

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {

            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l + amount <= 1.0) {
                pixel.l += amount;
            } else {
                pixel.l = 1.0;
            }

        }
    }

}

void Image::darken() {

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {

            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l >= 0.1) {
                pixel.l -= 0.1;
            } else {
                pixel.l = 0.0;
            }

        }
    }

}

void Image::darken(double amount) {

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {

            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l - amount >= 0.0) {
                pixel.l -= amount;
            } else {
                pixel.l = 0.0;
            }

        }
    }

}

void Image::saturate() {
  for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {

          HSLAPixel & pixel = getPixel(x, y);
          if (pixel.s <= (1.0 - 0.1)) {
              pixel.s += 0.1;
          } else {
              pixel.s = 1.0;
          }

      }
  }
}

void Image::saturate(double amount) {

  for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {

          HSLAPixel & pixel = getPixel(x, y);
          if (pixel.s + amount <= 1.0) {
              pixel.s += amount;
          } else {
              pixel.s = 1.0;
          }

      }
  }

}

void Image::desaturate() {
  for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {

          HSLAPixel & pixel = getPixel(x, y);
          if (pixel.s >= 0.1) {
              pixel.s -= 0.1;
          } else {
              pixel.s = 0.0;
          }

      }
  }
}

void Image::desaturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {

          HSLAPixel & pixel = getPixel(x, y);
          if (pixel.s - amount >= 0.0) {
              pixel.s -= amount;
          } else {
              pixel.s = 0.0;
          }

      }
  }
}

void Image::grayscale() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {

      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;

    }
  }

}

void Image::rotateColor(double degrees) {
  double amount = fmod(degrees, 360);
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      double temp = pixel.h;
      if (degrees >= 0) {
        pixel.h = fmod((temp + amount), 360);
      } else {
        pixel.h = fmod((temp + amount + 360), 360);
      }

    }
  }

}

void Image::illinify() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {

      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.h >= 114 && pixel.h <= 293) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }

    }
  }

}

void Image::scale(double factor) {

    unsigned width = this->width();
    unsigned height = this->height();
    PNG* temp = new PNG(*this);
    this->resize(width * factor, height * factor);

        if (factor > 1) {
          //copying the temp image pixel to the original one according to the rule of scaling bigger
          for (unsigned x = 0; x < temp->width(); x++) {
              for (unsigned y = 0; y < temp->height(); y++) {

                  HSLAPixel & outputpixel = temp->getPixel(x, y);
                  for (unsigned i = 0; i < factor; i++) {
                    for (unsigned j = 0; j < factor; j++) {
                      HSLAPixel & pixel = this->getPixel((int)(x * factor) + i, (int)(y * factor) + j);
                      pixel = outputpixel;
                    }
                  }

              }
        }


      } else if (0 < factor && factor < 1) {

        for (unsigned x = 0; x < this->width(); x++) {
          for (unsigned y = 0; y < this->height(); y++) {

            HSLAPixel & outputpixel = temp->getPixel((int)(x / factor), (int)(y / factor));
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel = outputpixel;

          }
        }


    }
    delete temp;
}

void Image::scale(unsigned w, unsigned h) {

    //determine whether to fit height or width
    double hfactor = h / this->height();
    double wfactor  = w / this->width();
    double factor;
    if (h > w) {
      factor = w;
    } else {
      factor = h;
    }
    //resize the original image
    this->scale(factor);

}
