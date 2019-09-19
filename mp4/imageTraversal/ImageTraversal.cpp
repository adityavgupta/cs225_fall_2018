#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
//can pass an argument which takes in pointer or can pass a reference to DFS or BFS)
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  position_ = Point(0, 0);
}
ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start) {

  traversal_ = traversal;
  position_ = start;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!(traversal_->empty())) {
    position_ = traversal_->pop();
    traversal_->point_vector[position_.x][position_.y] = true;

    Point p1 = Point(position_.x + 1, position_.y);
    Point p2 = Point(position_.x, position_.y + 1);
    Point p3 = Point(position_.x - 1, position_.y);
    Point p4 = Point(position_.x, position_.y - 1);

    traversal_->add(p1);
    traversal_->add(p2);
    traversal_->add(p3);
    traversal_->add(p4);

    if (traversal_->empty())
      return *this;
    position_ = traversal_->peek();

    while(traversal_->point_vector[position_.x][position_.y] == true && !(traversal_->empty())) {
      traversal_->pop();
      position_ = traversal_->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
	//Point x = this.current();
	//return x;
  return position_;
  //return Point(0, 0);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  /*if(traversal_ == NULL && other.traversal_ == NULL) {
    //std::cout << 1 << std::endl;
    return false;
  }
  if(traversal_ == NULL && other.traversal_->empty()) {
    //std::cout << 2 << std::endl;
    return false;
  }
  if(traversal_->empty() && other.traversal_ == NULL) {
    //std::cout << 3 << std::endl;
    return false;
  }
  if(traversal_->empty() && other.traversal_->empty()) {
    //std::cout << 4 << std::endl;
    return false;
  }*/
  //the following part checks when one of them is at the end and the other isn't
  bool this_end = !traversal_ || traversal_->empty();
  bool that_end = !other.traversal_ || other.traversal_->empty();
  if (this_end != that_end)
    return true;
  if(position_ == other.position_) {
    return false;
  }
  else {
    return true;
  }
}
