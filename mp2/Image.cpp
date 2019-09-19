#include "Image.h"
#include <cmath>
#include <string>

using namespace cs225;

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l += amount;
            if(pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l -= amount;
            if(pixel.l > 1){
                pixel.l = 1.0;
            }
            if(pixel.l < 0){
                pixel.l = 0.0;
            }
        }
    }
}

void Image::saturate(){
    saturate(0.1);
}

void Image::saturate(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s += amount;
            if(pixel.s > 1.0){
                pixel.s = 1.0;
            }
        }
    }
}

void Image::desaturate(){
    desaturate(0.1);
}

void Image::desaturate(double amount){
     for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s -= amount;
            if(pixel.s > 1.0){
                pixel.s = 1.0;
            }
            if(pixel.s < 0.0){
                pixel.s = 0.0;
            }
        }
    }
}

void Image::grayscale(){
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::illinify(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){

            HSLAPixel & pixel = this->getPixel(x, y);

            double diffblue = std::abs(pixel.h - 11);
            if(diffblue > 180){
                diffblue = 360 - diffblue;
            }

            double difforange = std::abs(pixel.h - 216);
            if(difforange > 180){
                difforange = 360 - difforange;
            }

            if(diffblue < difforange){
                pixel.h = 11;
            }
            else{
                pixel.h = 216;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.h += degrees;
            while(pixel.h > 360){
                pixel.h = pixel.h - 360;
            }
            while(pixel.h < 0){
                pixel.h += 360;
            }
        }
    }
}

void Image::scale(double factor){
    scale(this->width() * factor, this->height() * factor);
}

void Image::scale(unsigned w, unsigned h){
    Image copied_image(*this);
    this->resize(w, h);
    double scale_width = (double) copied_image.width()/this->width();
    double scale_height = (double)copied_image.height()/this->height();
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel & pixel = copied_image.getPixel(x*scale_width, y*scale_height);
            HSLAPixel & pixel1 = this->getPixel(x, y);
            pixel1 = pixel;
        }
    } 
}
