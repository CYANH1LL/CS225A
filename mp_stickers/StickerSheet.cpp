

#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
using namespace cs225;
using namespace std;

void StickerSheet::copy(const StickerSheet& other)
{
  count = new int[other.capacity];
  x_coord = new int[other.capacity];
  y_coord = new int[other.capacity];
  capacity = other.capacity;
  stickers = new Image*[other.capacity];
  background = new Image(*(other.background));
  amount = other.amount;
  for (unsigned i = 0; i < capacity; i++) {
      if (other.count[i] != 0) {
        x_coord[i] = other.x_coord[i];
        y_coord[i] = other.y_coord[i];
        stickers[i] = new Image(*(other.stickers[i]));
        count[i] = other.count[i];
      } else {
        count[i] = 0;
        x_coord[i] = 0;
        y_coord[i] = 0;
        stickers[i] = NULL;
      }
  }
}

void StickerSheet::destroy() {
  for (unsigned i = 0; i < capacity; i++) {
    if (count[i] != 0) {
      delete stickers[i];
      stickers[i] = NULL;
    }
  }
  delete[] stickers;
  delete[] x_coord;
  delete[] y_coord;
  delete[] count;
  delete background;
  stickers = NULL;
  x_coord = NULL;
  y_coord = NULL;
  count = NULL;
  background = NULL;
  }

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
  amount = 0;
  capacity = max;
  stickers = new Image*[capacity];
  x_coord = new int[capacity];
  y_coord = new int[capacity];
  count = new int[capacity];
  for (unsigned i = 0; i < max; i++) {
        stickers[i] = NULL;
        count[i] = 0;
        x_coord[i] = 0;
        y_coord[i] = 0;
  }
  this->background = new Image(picture);
}

StickerSheet::~StickerSheet() {
  destroy();
}

StickerSheet::StickerSheet(const StickerSheet& other) {
  copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet& other) {
  if (this == &other) {
      return *this;
  }
  destroy();
  copy(other);
  return *this;
}




void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == capacity) return;

    Image** newStickers = new Image*[max];
    int* newXlist = new int[max];
    int* newYlist = new int[max];
    int* newClist = new int[max];
    unsigned newAmount = 0;
    Image* newBase = new Image(*background);

    if (max < capacity) {
      for (unsigned i = max; i < capacity; i++){
        if (count[i] != 0) {
          delete stickers[i];
          stickers[i] = NULL;
          count[i]--;
        }
      }
      capacity = max;
    }
    if (max > capacity) {
      for (unsigned j = 0; j < max; j++){
          newStickers[j] = NULL;
          newClist[j] = 0;
        }
      }
      for (unsigned i = 0; i < capacity; i++) {
        if (count[i] != 0){
          newStickers[i] = new Image(*stickers[i]);
          newXlist[i] = x_coord[i];
          newYlist[i] = y_coord[i];
          newClist[i] = count[i];
          newAmount++;
        }
        else{
          newClist[i] = 0;
        }
      }

    destroy();
    capacity = max;
    stickers = newStickers;
    x_coord = newXlist;
    y_coord = newYlist;
    count = newClist;
    amount = newAmount;
    background = newBase;
    stickers = newStickers;

}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
  if (amount < capacity) {
    for (unsigned i = 0; i < capacity; i++){
       if (count[i] == 0) {
           stickers[i] = new Image(sticker);
           x_coord[amount] = x;
           y_coord[amount] = y;
           count[i]++;
           amount ++;
           return i;
       }
     }
  }
  return -1;

}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index < capacity && count[index] != 0) {
      x_coord[index] = x;
      y_coord[index] = y;
      return true;
    } else {
      return false;
    }
}

void StickerSheet::removeSticker (unsigned index) {
    if (index < capacity && count[index] != 0) {
          delete stickers[index];
          stickers[index] = NULL;
   	      x_coord[index] = 0;
   	      y_coord[index] = 0;
          count[index]--;
        	amount--;
    }

}

Image* StickerSheet::getSticker (unsigned index) const{
  if (index >= capacity || count[index] == 0) {
    return NULL;
  } else {
    return stickers[index];
  }

}

Image StickerSheet::render () const {

    unsigned xMost = background->width();
    unsigned yMost = background->height();
    for (unsigned i = 0; i < capacity; i++){

      if (count[i] != 0){
        unsigned x = x_coord[i] + stickers[i]->width();
        unsigned y = y_coord[i] + stickers[i]->height();
        if (xMost < x) xMost = x;
        if (yMost < y) yMost = y;
      }
    }
    Image *output = new Image(*background);
    output->resize(xMost,yMost);

    for(unsigned i = 0; i < amount; i++) {
      if (count[i] != 0) {
        Image sticker = *stickers[i];
        for (unsigned x = x_coord[i]; x < x_coord[i] + sticker.width(); x++) {
            for (unsigned y = y_coord[i]; y < y_coord[i] + sticker.height(); y++) {

                    HSLAPixel &pixel = sticker.getPixel(x - x_coord[i], y - y_coord[i]);
                    HSLAPixel &outputpixel = output->getPixel(x, y);
                    if (pixel.a > 0) {
                      outputpixel.h = pixel.h;
                      outputpixel.s = pixel.s;
                      outputpixel.l = pixel.l;
                      outputpixel.a = pixel.a;
                    }
        }
      }
    }
    }


    Image newoutput = (*output);

    delete output;
    output = NULL;

    return newoutput;
}
