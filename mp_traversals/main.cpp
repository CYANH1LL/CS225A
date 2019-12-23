
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG mountain;
  mountain.readFromFile("mountain.png");
  FloodFilledImage image(mountain);

   SolidColorPicker cyan(HSLAPixel(199, 1, 0.476));
   SolidColorPicker darkcyan(HSLAPixel(187, 0.783, 0.271));
   SolidColorPicker lightcyan(HSLAPixel(185, 0.857, 0.412));
   SolidColorPicker brightcyan(HSLAPixel(187, 0.356, 0.769));
   MyColorPicker mycolor(10);



   DFS dfs1(mountain, Point(0, 600), 0.1);
   DFS dfs2(mountain, Point(0, 315), 0.1);
   DFS dfs3(mountain, Point(0, 300), 0.1);


   BFS bfs1(mountain, Point(799, 300), 0.1);
   BFS bfs2(mountain, Point(799, 200), 0.1);
   BFS bfs3(mountain, Point(200, 200), 0.1);
   BFS bfs4(mountain, Point(0, 200), 0.1);

   DFS dfs4(mountain, Point(0, 600), 0.1);

   image.addFloodFill(dfs1, cyan);
   image.addFloodFill(dfs2, darkcyan);
   image.addFloodFill(dfs3, lightcyan);
   image.addFloodFill(bfs1, lightcyan);
   image.addFloodFill(bfs2, brightcyan);
   image.addFloodFill(bfs3, brightcyan);
   image.addFloodFill(bfs4, brightcyan);
   image.addFloodFill(dfs4, mycolor);


  Animation animation = image.animate(50000);
  PNG outputFrame = animation.getFrame( animation.frameCount() - 1 );

  outputFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
