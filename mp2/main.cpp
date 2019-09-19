#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  Image chrome; chrome.readFromFile("chrome.png"); chrome.scale(0.15);
  Image safari; safari.readFromFile("Safari.png"); safari.scale(0.10);
  Image firefox; firefox.readFromFile("firefox.png"); firefox.scale(0.05);
  Image waterfox; waterfox.readFromFile("Waterfox.png"); waterfox.scale(0.117);
  Image netscape; netscape.readFromFile("netscape.png"); netscape.scale(0.5);
  Image alma; alma.readFromFile("alma.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(chrome, 20, 20);
  sheet.addSticker(safari, 780, 480);
  sheet.addSticker(firefox, 20, 480);
  sheet.addSticker(waterfox, 780, 10);
  sheet.addSticker(netscape, 388, 250);

  sheet.render().writeToFile("myImage.png");

  return 0;
}
