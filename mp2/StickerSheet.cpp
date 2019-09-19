#include <string>
#include <iostream>
#include <vector>
#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image& picture, unsigned max): _basePicture(picture), _max(max) {
    //sticker = new Image* [_max];
    //x_coordinate = new unsigned[_max];
   //y_coordinate = new unsigned[_max];

    /*for(unsigned i = 0; i < _max; i++){
        maxSticker[i] = NULL;
        x_coordinate[i] = 0;
        y_coordinate[i] = 0;*/
    //}
}

StickerSheet::~StickerSheet(){
    clear();
}

void StickerSheet::clear(){
    /*for(unsigned i = 0; i < _max; i++) {
       if(maxSticker[i] != NULL) {
            delete maxSticker[i];
       }
       maxSticker[i] = NULL;
    }
    if(maxSticker != NULL) {
        delete[] maxSticker;
    }
    if(x_coordinate != NULL) {
        delete[] x_coordinate;
    }
    if(y_coordinate != NULL) {
        delete[] y_coordinate;
    }
    maxSticker = NULL;
    x_coordinate = NULL;
    y_coordinate = NULL;*/
    stickers.clear();
    x_coordinate.clear();
    y_coordinate.clear();
}

StickerSheet::StickerSheet(const StickerSheet& other){
    copy(other);
}

void StickerSheet::copy(const StickerSheet& other) {
    _max = other._max;
    _basePicture = other._basePicture;
    stickers = other.stickers;
    x_coordinate = other.x_coordinate;
    y_coordinate = other.y_coordinate;
    /*maxSticker = new Image* [_max];
    x_coordinate = new unsigned[_max];
    y_coordinate = new unsigned[_max];*/

    /*for(unsigned i = 0; i < _max; i++){
        if(other.maxSticker[i] != NULL) {
            maxSticker[i] = new Image(*other.maxSticker[i]);
        }   else {
                maxSticker[i] = NULL;
            }
        x_coordinate[i] = other.x_coordinate[i];
        y_coordinate[i] = other.y_coordinate[i];
    }*/
}

const StickerSheet& StickerSheet::operator= (const StickerSheet& other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if(max < _max) {
        stickers.resize(max);
        x_coordinate.resize(max);
        y_coordinate.resize(max);
    }
   _max = max;
    /*if (max == _max) return;
  Image** newMaxSticker = new Image*[max];
  unsigned* x_cor_new = new unsigned[max];
  unsigned* y_cor_new = new unsigned[max];

  for(unsigned i = 0; i < max; i++) {
    if(i > _max) {
        newMaxSticker[i] = NULL;
        x_cor_new[i] = 0;
        y_cor_new[i] = 0;
    }
    else {
        newMaxSticker[i] = maxSticker[i];
        x_cor_new[i] = x_coordinate[i];
        y_cor_new[i] = y_coordinate[i];
    }
  }

  delete[] maxSticker;
  delete[] x_coordinate;
  delete[] y_coordinate;

  maxSticker = newMaxSticker;
  x_coordinate = x_cor_new;
  y_coordinate = y_cor_new;*/
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
    if(stickers.size() >= _max) {
        return -1;
    }
    stickers.push_back(sticker);
    x_coordinate.push_back(x);
    y_coordinate.push_back(y);
    return stickers.size()-1;
    /*unsigned index = -1;

    for(unsigned i = 0; i < _max; i++) {
        if(maxSticker[i] == NULL) {
            Image* placement = new Image(sticker);
            maxSticker[i] = placement;
            x_coordinate[i] = x;
            y_coordinate[i] = y;
            index = i;
            break;
        }
    }
    return index;*/
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if(index >= stickers.size()) {
        return false;
    }
    x_coordinate[index] = x;
    y_coordinate[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if(index < stickers.size()) {
        stickers.erase(stickers.begin() + index);
        x_coordinate.erase(x_coordinate.begin() + index);
        y_coordinate.erase(y_coordinate.begin() + index);
        /*delete maxSticker[index];
        maxSticker[index] = NULL;
        x_coordinate[index] = 0;
        y_coordinate[index] = 0;*/
    }        
}

Image* StickerSheet::getSticker(unsigned index) const {
    if(index >= stickers.size()) {
        return NULL;
    }

    return const_cast<Image*>(&stickers[index]);
}

Image StickerSheet::render() const {
    Image out;
    out = _basePicture;
    
    for(unsigned i = 0; i < stickers.size(); i++) {
        if(x_coordinate[i] + stickers[i].width() > out.width()) {
                out.resize(x_coordinate[i] + stickers[i].width(), out.height());
        }
        if(y_coordinate[i] + stickers[i].height() > out.height()) {
                out.resize(out.width(), y_coordinate[i] + stickers[i].height());
        }
        for(unsigned m = 0; m < stickers[i].width(); m++) {
            for(unsigned n = 0; n < stickers[i].height(); n++) {
                if(stickers[i].getPixel(m, n).a != 0) {
                    out.getPixel(x_coordinate[i] + m, y_coordinate[i] + n) = stickers[i].getPixel(m, n);
                }
            }
        }


    }

    /*for(unsigned i = 0; i < _max; i++) {
        if(maxSticker[i] != NULL) {
            if(x_coordinate[i] + maxSticker[i]->width() > out.width()) {
                out.resize(x_coordinate[i] + maxSticker[i]->width(), out.height());
            }
            if(y_coordinate[i] + maxSticker[i]->height() > out.height()) {
                out.resize(out.width(), y_coordinate[i] + maxSticker[i]->height());
            }
            for(unsigned m = 0; m < maxSticker[i]->width(); m++) {
                for(unsigned n = 0; n < maxSticker[i]->height(); n++) {
                    if(maxSticker[i]->getPixel(m, n).a != 0) {
                        out.getPixel(x_coordinate[i] + m, y_coordinate[i] + n) = maxSticker[i]->getPixel(m, n);
                    }
                }
            }
        }
    }*/
    return out;
}
