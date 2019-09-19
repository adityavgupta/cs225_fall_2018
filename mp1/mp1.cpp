#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cmath>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
    PNG p;
    p.readFromFile(inputFile);

    //when the width of the image is even
    if(p.width() % 2 == 0){
         for(unsigned x = 0; x < p.width()/2; x++){

             //even width of the PNG file means that the entire height is traversed at all times
            for(unsigned y = 0; y < p.height(); y++){

                //using a temp pixel to hold the current pixel's data
                HSLAPixel temp = p.getPixel(x, y);

                //replace the current pixel's data with the pixel data of the corresponding swap pixel
                p.getPixel(x, y) = p.getPixel(p.width() - 1 - x, p.height() - 1 - y);

                //assign the current pixel's data to the swap pixel.
                p.getPixel(p.width() - 1 - x, p.height() - 1 - y) = temp;

            }
             
         }

    }

    //when the width of the image is odd
    else if(p.width() % 2 == 1){
        for(unsigned x = 0; x < (p.width()+1)/2; x++){
            //condition check for the pixel when the two pixel to be swapped are the same ones
            if(x == (p.width()-1)/2){

                //when x value in the loop reaches half the width value, traverse only half the height to avoid double swapping
                for(unsigned y = 0; y < p.height()/2; y++){
                    HSLAPixel temp = p.getPixel(x, y);
                    p.getPixel(x, y) = p.getPixel(p.width() - 1 - x, p.height() - 1 - y);
                    p.getPixel(p.width() - 1 - x, p.height() - 1 - y) = temp;

                }   
            }
            //for all other x values traverse the entore height
            else{
                for(unsigned y = 0; y < p.height(); y++){
                    HSLAPixel temp = p.getPixel(x, y);
                    p.getPixel(x, y) = p.getPixel(p.width() - 1 - x, p.height() - 1 - y);
                    p.getPixel(p.width() - 1 - x, p.height() - 1 - y) = temp;
                }   
            }
        }
    }
    p.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  for(unsigned x = 0; x < png.width(); x++){
      for(unsigned y = 0; y < png.height(); y++){
          png.getPixel(x, y).h = 120 + 120*sin(x*y/20) + 60*cos(y*x/10);
          png.getPixel(x, y).l = 0.5;
          png.getPixel(x, y).s = 1;
          png.getPixel(x, y).a = 1;

      }
  }

  return png;
}
