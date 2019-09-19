/* Your code here! */
#include "maze.h"
#include <iostream>

SquareMaze::SquareMaze ()
{
	width = 0;
	height = 0;
	cells.clear();
}

void SquareMaze::makeMaze (int width, int height)
{
	this->width = width;
	this->height = height;
	cells.clear();
	for(int i = 0; i < width*height; i++) {
		cells.push_back(new MazeCell(true, true, false));
		cells[i]->cellNum = i;
	}

	DisjointSets dsets;
	int numsElemsToAdd = width*height;
	dsets.addelements(numsElemsToAdd);

	while (numsElemsToAdd > 1) {
		int whichwall = std::rand() % 2;
		int randX = std::rand() % width;
		int randY = std::rand() % height;

		if (whichwall == 0) {
			//destroy right wall
			if (randX < (width -1)) {
				if(dsets.find(cells[(randY*width) + randX]->cellNum) != dsets.find(cells[(randY*width) + (randX+1)]->cellNum)) {
					setWall(randX, randY, whichwall, false);
					dsets.setunion(cells[(randY*width) + randX]->cellNum, cells[(randY*width) + (randX+1)]->cellNum);
					numsElemsToAdd--;
				}
			}
		}
		else {
			//destroy down wall
			if (randY < (height-1)) {
				if(dsets.find(cells[(randY*width) + randX]->cellNum) != dsets.find(cells[((randY+1)*width) + randX]->cellNum)) {
					setWall(randX, randY, whichwall, false);
					dsets.setunion(cells[(randY*width) + randX]->cellNum, cells[((randY+1)*width) + randX]->cellNum);
					numsElemsToAdd--;
				}
			}
		}
	}
}

bool SquareMaze::canTravel (int x, int y, int dir) const
{
	if(dir == 0) {
		//move right (+1 x)
		if((x+1 < width) && !(cells[(y*width) + x]->right)) {
			return true;
		}
		return false;
	}

	else if(dir == 1) {
		//move down (+1 y)
		if((y+1 < height) && !(cells[(y*width) + x]->down)) {
			return true;
		}
		return false;
	}
	else if(dir == 2) {
		//move left (-1 x)
		if((x-1 >= 0) && (x < width) && !(cells[(y*width) + (x-1)]->right)) {
			return true;
		}
		return false;
	}
	else if(dir == 3) {
		//move up (-1 y)
		if((y-1 >= 0) && (y < height) && !(cells[((y-1)*width) + x]->down)) {
			return true;
		}
		return false;
	}
	else {
		return false;
	}
}

void SquareMaze::setWall (int x, int y, int dir, bool exists)
{
	if(x >= 0 && y >= 0 && x < width && y < height) {
		if(dir == 0) {
			//right
			cells[(y*width) + x]->right = exists;
		}
		else if(dir == 1) {
			//down
			cells[(y*width) + x]->down = exists;
		}
	}
}

std::vector<int> SquareMaze::solveMaze ()
{
	std::queue<MazeCell*> path;
	path.push(cells[0]);
	while(!path.empty()) {
		int currX = (path.front()->cellNum) % width;
		int currY = (path.front()->cellNum) / width;
		MazeCell* currCell = path.front();

		if(canTravel(currX, currY, 0) && !cells[currCell->cellNum + 1]->visited) { //can travel right
			cells[currCell->cellNum + 1]->visited = true;
			cells[currCell->cellNum + 1]->travDirection = 0;
			cells[currCell->cellNum + 1]->prevCellNum = currCell->cellNum;
			path.push(cells[currCell->cellNum + 1]);
		}

		if (canTravel(currX, currY, 1) && !cells[currCell->cellNum + width]->visited) { //canTravel down
			cells[currCell->cellNum + width]->visited = true;
			cells[currCell->cellNum + width]->travDirection = 1;
			cells[currCell->cellNum + width]->prevCellNum = currCell->cellNum;
			path.push(cells[currCell->cellNum + width]);
		}

		if (canTravel(currX, currY, 2) && !cells[currCell->cellNum - 1]->visited) { //canTravel left
			cells[currCell->cellNum - 1]->visited = true;
			cells[currCell->cellNum - 1]->travDirection = 2;
			cells[currCell->cellNum - 1]->prevCellNum = currCell->cellNum;
			path.push(cells[currCell->cellNum - 1]);
		}

		if (canTravel(currX, currY, 3) && !cells[currCell->cellNum - width]->visited) { //canTravel up
			cells[currCell->cellNum - width]->visited = true;
			cells[currCell->cellNum - width]->travDirection = 3;
			cells[currCell->cellNum - width]->prevCellNum = currCell->cellNum;
			path.push(cells[currCell->cellNum - width]);
		}

		path.pop();
	}
	std::vector<int> maxPath;
	std::vector<int> currPath;
	maxPath.resize(0);

	for (int i = 0; i < width; i++) {
		MazeCell* travCell = cells[((height - 1) * width) + i];
		currPath.clear();
		while (travCell->cellNum != 0) {
			currPath.push_back(travCell->travDirection);
			travCell = cells[travCell->prevCellNum];
		}

		if (currPath.size() > maxPath.size()) {
			maxPath = currPath;
		}
	}

	std::reverse(maxPath.begin(), maxPath.end());

	return maxPath;
}

PNG* SquareMaze::drawMaze() const
{
	PNG* retPng = new PNG(width*10 + 1, height*10 + 1);
	//left most column
	for (unsigned int y = 0; y < retPng->height(); y++) {
		retPng->getPixel(0, y).l = 0;
	}

	//top most row
	for (unsigned int x = 0; x < retPng->width(); x++) {
		if (x > 9 || x < 1) {
			retPng->getPixel(x, 0).l = 0;
		}
	}

	//for each square in the maze,
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (cells[(y * width) + x]->right) {
				//if the right wall exists, blacken ((x+1)*10, y*10 + k) from k = 0 to 10
				for (int k = 0; k < 11; k++) {
					retPng->getPixel((x+1) * 10, y * 10 + k).l = 0;
				}
			}

			if (cells[(y * width) + x]->down) {
				//if the down wall exists, blacken ((x*10 + k, (y+1)*10) from k = 0 to 10
				for (int k = 0; k < 11; k++) {
					retPng->getPixel(x*10 + k, (y+1)*10).l = 0;
				}
			}
		}
	}

	return retPng;
}

PNG* SquareMaze::drawMazeWithSolution()
{
	PNG * retPng = drawMaze();
	std::vector<int> solVec = solveMaze();

	int xPos = 5;
	int yPos = 5;
	//make the red line
	for (int direction : solVec) {
		int incX = 0;
		int incY = 0;
		if (direction == 0) { //go right
			incX = 1;
		}
		else if (direction == 1) { //go down
			incY = 1;
		}
		else if (direction == 2) { //go left
			incX = -1;
		}
		else if (direction == 3) { //go up
			incY = -1;
		}

		for (int i = 0; i <= 10; i++) {
			HSLAPixel & pix = retPng->getPixel(xPos, yPos);
			pix.h = 0;
			pix.s = 1;
			pix.l = 0.5;
			pix.a = 1;

			xPos += incX;
			yPos += incY;
		}

		xPos -= incX;
		yPos -= incY;
	}

	//make the exit door
	for (int k = 1; k <= 9; k++) {
		retPng->getPixel((xPos/10)*10 + k, ((yPos/10)+1)*10).l = 1;
	}

	return retPng;
}

PNG* SquareMaze::creativeMaze(int width, int height)
{
	//seed rand
	std::srand(42);
	makeMaze(width, height);
	PNG* retPng = new PNG(width*10 + 1, height*10 + 1);
	//left most column
	for (unsigned int y = 0; y < retPng->height(); y++) {
		retPng->getPixel(0, y).l = 0;
	}

	//top most row
	for (unsigned int x = 0; x < retPng->width(); x++) {
		if (x > 9 || x < 1) {
			retPng->getPixel(x, 0).l = 0;
		}
	}

	//for each square in the maze,
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (cells[(y * width) + x]->right) {
				//if the right wall exists, blacken ((x+1)*10, y*10 + k) from k = 0 to 10
				for (int k = 0; k < 11; k++) {
					retPng->getPixel((x+1) * 10, y * 10 + k).l = 0;
				}
			}

			if (cells[(y * width) + x]->down) {
				//if the down wall exists, blacken ((x*10 + k, (y+1)*10) from k = 0 to 10
				for (int k = 0; k < 11; k++) {
					retPng->getPixel(x*10 + k, (y+1)*10).l = 0;
				}
			}
		}
	}

	// custom stuff
	for (unsigned int x = 0; x < retPng->width(); x++) {
		for (unsigned int y = 0; y < retPng->height(); y++) {
				/*if (x <= 300) {
					if (y >= 210) {
						retPng->getPixel(x,y).l = 0;
					}
				}*/

				if (x >= 1500 && x <= 2000) {
					if (y <= 400 && y >= 200) {
						retPng->getPixel(x, y).l = 0.5;
						retPng->getPixel(x, y).h = 11;
						retPng->getPixel(x, y).s = 0.7;
					}
				}

				if (x >= (1500+125) && x <= (2000-125)) {
					if(y > 400 && y <= 800) {
						retPng->getPixel(x,y).l = 0.5;
						retPng->getPixel(x,y).h = 11;
						retPng->getPixel(x, y).s = 0.7;
					}
				}

				if (x >= 1500 && x <= 2000) {
					if (y <= 1000 && y >= 800) {
						retPng->getPixel(x,y).l = 0.5;
						retPng->getPixel(x,y).h = 11;
						retPng->getPixel(x, y).s = 0.7;
					}
				}

		}
	}

	std::vector<int> solVec = solveMaze();

	int xPos = 5;
	int yPos = 5;
	//make the red line
	for (int direction : solVec) {
		int incX = 0;
		int incY = 0;
		if (direction == 0) { //go right
			incX = 1;
		}
		else if (direction == 1) { //go down
			incY = 1;
		}
		else if (direction == 2) { //go left
			incX = -1;
		}
		else if (direction == 3) { //go up
			incY = -1;
		}

		for (int i = 0; i <= 10; i++) {
			HSLAPixel & pix = retPng->getPixel(xPos, yPos);
			pix.h = 0;
			pix.s = 1;
			pix.l = 0.5; //see its funny because it looks like "pixel"
			pix.a = 1;

			xPos += incX;
			yPos += incY;
		}

		xPos -= incX;
		yPos -= incY;
	}

	//make the exit door
	for (int k = 1; k <= 9; k++) {
		retPng->getPixel((xPos/10)*10 + k, ((yPos/10)+1)*10).l = 1;
	}

	return retPng;
}
