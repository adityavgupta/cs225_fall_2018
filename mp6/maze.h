/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <queue>
using namespace cs225;

struct MazeCell {
	bool right, down , visited;
	int cellNum, travDirection, prevCellNum;

	MazeCell(bool right, bool down, bool visited) : right(right), down(down), visited(visited) {
		cellNum = -1;
		travDirection = -1;
		prevCellNum = -1;
	}
};

class SquareMaze {
	public:
		SquareMaze ();
		void makeMaze (int width, int height);
		bool canTravel (int x, int y, int dir) const;
		void setWall (int x, int y, int dir, bool exists);
		std::vector<int> solveMaze ();
		PNG* drawMaze() const;
		PNG* drawMazeWithSolution ();
		PNG * creativeMaze(int width, int height);
	private:
		int width;
		int height;
		std::vector<MazeCell*> cells;

};

#endif
