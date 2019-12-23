/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     int row = theSource.getRows();
     int col = theSource.getColumns();
     if (row == 0 || col == 0 || theTiles.empty()) {
       return NULL;
     }
     MosaicCanvas* output = new MosaicCanvas(row, col);

     vector<Point<3>> pointsOfTiles;
     map<Point<3>, TileImage*> map;

     for(unsigned i = 0; i < theTiles.size(); i++) {
       LUVAPixel pixel = theTiles[i].getAverageColor();
       Point<3> point = convertToXYZ(pixel);
       pointsOfTiles.push_back(point);
       map[point] = &theTiles[i];
     }

     KDTree<3> kdtree(pointsOfTiles);


    for (int r = 0; r < row; r++) {
      for (int c = 0; c < col; c++) {
          Point<3> original = convertToXYZ(theSource.getRegionColor(r, c));
          Point<3> closest = kdtree.findNearestNeighbor(original);
          TileImage* tempTile = map[closest];
          output->setTile(r, c, tempTile);
      }
    }
    return output;
}
