#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;
int main() {


  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image zane;
  zane.readFromFile("zane.png");
  Image amara;
  amara.readFromFile("amara.png");
  Image moze;
  moze.readFromFile("moze.png");
  Image hunter;
  hunter.readFromFile("fl4k.png");
  Image logo;
  logo.readFromFile("borderlands-3.png");
  Image cross;
  cross.readFromFile("redcross.png");
  StickerSheet mine(logo, 5);
  mine.addSticker(zane, 600, 600);
  mine.addSticker(amara, 300, 200);
  mine.addSticker(hunter, 200, 200);
  mine.addSticker(moze, 100, 200);
  mine.addSticker(cross, 700, 600);

  mine.render().writeToFile("myImage.png");
  return 0;
}
