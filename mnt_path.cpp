
#include "Bridges.h"
#include "ColorGrid.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "DataSource.h"
#include "data_src/ElevationData.h"
using namespace std;
using namespace bridges;

// This program implements the mountain paths assignment in C++. See the README.md for a
// detailed description


// takes in the processed elevation data and returns a color grid for
// visualization using BRIDGES
ColorGrid getImage(const ElevationData& elev_data) {
	//TODO
	//
	//return a Color Grid that represents the elevation as gray scale
	//
	// access elevation with elev_data.getVal(row, col)
	// compute the intensity by linear interpolation between elev_data.getMinVal(); and elev_data.getMaxVal();
	//
	// create ColorGrid with ColorGrid(nbrows, nbcols)
	// fill ColorGrid with .set(row, col, color)
	ColorGrid cg (1,1);

	return cg;
}

// determines the least effort path through the mountain starting a point on
// the left edge of the image
void findPath(const ElevationData&  elev_data, int startRow, ColorGrid& cg) {
	//        Run the greedy path from (0, startRow) to the right of the image
	//
	// always move right, but select the right cell, the top right cell, or bottom right cell
	// by minimizing the difference of elevation.
	//
	// Write path to the colorgrid
	int rows = cg.getHeight();
	int cols = cg.getWidth();

	Color red(255, 0, 0);

	//cg.set(startRow, 0, Color(255, 0, 0));

	for (int currCol = 0; currCol < cols - 1; currCol++) {
//		cg.set(startRow, currCol, red);
		int currPos = elev_data.getVal(startRow, currCol);
		int straight = elev_data.getVal(startRow, currCol + 1) - currPos;
		int best = straight;
		int nextRow = startRow;

		if (startRow > 0) {
			// I believe that you have to do - 1 for the row because of how the terminal is flipped from cartesian coords
			int upRight = elev_data.getVal(startRow - 1, currCol + 1) - currPos;
			if (upRight < 0) upRight *= -1;
			if (upRight < best) {
				best = upRight;
				nextRow = startRow - 1;
			}
		}

		if (startRow < rows - 1) {
			int downRight = elev_data.getVal(startRow + 1, currCol + 1) - currPos;
			if (downRight < 0) downRight *= -1;
			if (downRight < best) {
				best = downRight;
				nextRow = startRow + 1;
			}
		}

		startRow = nextRow;
		cg.set(startRow, currCol, red);
	}

	//startRow = nextRow;
}

//cg(startRow, cols - 1, red);



int main(int argc, char **argv) {

	// bridges object initialization


	// initialize Bridges
	Bridges bridges(1, "mabumaali1", "1396668946656");

	// defaults for row number and data file
	int startRow = 50;

	// set title
	bridges.setTitle("Mountain Paths - Greedy Algorithms Example");
	bridges.setDescription("Your goal is to find a path that takes you through the points with the lowest elevation changes, in an effort to minimize the overall effort in walking through the path.");

	// get elevation data

	DataSource ds;
	ElevationData elev_data = ds.getElevationData(6.02, 44.10, 9.70, 47.77, 0.02);

	// color grid for visualization
	ColorGrid cg = getImage(elev_data);

	// find path by applying a greedy algorithm
	startRow = elev_data.getRows()/2;
	findPath(elev_data, startRow, cg);

	// visualize
	bridges.setDataStructure(cg);
	bridges.visualize();

	//delete bridges;

	return 0;
}
