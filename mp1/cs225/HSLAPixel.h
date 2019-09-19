/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{
    //declaration of the constructors to be used in HSLAPixel.cpp
    //HSLAPixel() is a completely opaque and white HSLAPixel
    //HSLAPixel(double 	hue, double saturation, double luminance) constructs an opaque HSLAPixel with the given hue, saturation, and luminance values.
    //HSLApixel(double hue, double saturation, double luminance, double alpha) constructs an HSLAPixel with the given hue, saturation, luminance, and alpha values.
  public:

    HSLAPixel();
    HSLAPixel(double 	hue, double saturation, double luminance);
    HSLAPixel(double hue, double saturation, double luminance, double alpha);


    double h;
    double s;
    double l;
    double a;
  };
}

#endif
