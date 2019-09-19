
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

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG cs225; cs225.readFromFile("logo.png");
  FloodFilledImage _myimage(cs225);
  DFS dfs(cs225, Point(10, 10), 0.05);
  BFS bfs(cs225, Point(25, 25), 0.05);
  BFS bfsC(cs225, Point(60, 60), 0.05);
  BFS bfsS(cs225, Point(100, 100), 0.05);
  BFS bfs2(cs225, Point(150, 100), 0.05);
  BFS bfs22(cs225, Point(100, 150), 0.05);
  BFS bfs5(cs225, Point(220, 150), 0.05);
  MyColorPicker mine;

  HSLAPixel blue(216, 1, 0.3);
  SolidColorPicker mine2(blue);

  HSLAPixel orange(11, 1, 0.5);
  SolidColorPicker mine3(orange);

  _myimage.addFloodFill(dfs, mine);
  _myimage.addFloodFill(bfs, mine2);
  _myimage.addFloodFill(bfsC, mine3);
  _myimage.addFloodFill(bfsS, mine3);
  _myimage.addFloodFill(bfs2, mine3);
  _myimage.addFloodFill(bfs22, mine3);
  _myimage.addFloodFill(bfs5, mine3);
  Animation animation = _myimage.animate(450);

  //Animation animation = FloodFilledImage.animate(4);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  //lastFrame.writeToFile("logo.png");
  lastFrame.writeToFile("myFloodFill.png");
  //animation.write("logo.gif");
  animation.write("myFloodFill.gif");

  return 0;
}
