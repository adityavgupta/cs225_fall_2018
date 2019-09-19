#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = new PNG(png);
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ImageTraversal* traPointer = &traversal;
  ColorPicker* cpPointer = &colorPicker;
  tra_.push_back(traPointer);
  colorPicker_.push_back(cpPointer);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  /** @todo [Part 2] */
  Animation animation;

  animation.addFrame(*png_);
  for(unsigned i = 0; i < tra_.size(); i++) {
    ImageTraversal::Iterator b = tra_.at(i)->begin();
    ImageTraversal::Iterator e = tra_.at(i)->end();
    unsigned j = 0;
    for(ImageTraversal::Iterator it = b; it != e; ++it) {
      if(j == frameInterval) {
        animation.addFrame(*png_);
        j= 0;
      }
      HSLAPixel &original = png_->getPixel((*it).x, (*it).y);
      HSLAPixel p = colorPicker_.at(i)->getColor((*it).x, (*it).y);
      original.h = p.h;
      original.s = p.s;
      original.l = p.l;
      original.a = p.a;
      j++;
    }
    animation.addFrame(*png_);
  }
  return animation;
}
