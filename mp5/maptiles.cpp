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

	//a vector to hold the tile as points
	vector <Point<3>> tilePoints;

	//the new image canvas on which our image will be made
	MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

	//set sizex and size y to the rows and columns
	unsigned sizex = canvas->getRows(), sizey = canvas->getColumns();

	//a tile map
	map <Point<3>, TileImage*> tile_map;
	
	//iterate through theTiles vector
	for(size_t i = 0; i < theTiles.size(); i++) {
		//get the average color
		LUVAPixel temp = theTiles[i].getAverageColor();

		//convert the pixel to a point
		Point<3> tilePoint = convertToXYZ(temp);

		//push it back in the tilePoint vector
		tilePoints.push_back(tilePoint);

		//tile map has the adress of the image at the particular index
		tile_map[tilePoint] = &theTiles[i];									    
	}
	
	//construct the k-d tree
	KDTree <3> new_tree(tilePoints);

	//traverse the rows and columns and set the tiles to the respective place where they fill the apt color
	for(unsigned x = 0; x < sizex; x++) {
		for(unsigned y = 0; y < sizey; y++) {
			unsigned index = x * sizey + y;
			LUVAPixel s_color = theSource.getRegionColor(x,y);
			Point<3> s_point = convertToXYZ(s_color);

			//TileImage& c_tile = canvas->getTile(x, y);
			Point<3> nearest = new_tree.findNearestNeighbor(s_point);
			canvas->setTile( x, y, tile_map[nearest]  );
			//c_tile = bestTile;                         
		}
					    
	}

	return canvas;
}
