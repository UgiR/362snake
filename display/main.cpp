#include "Display.h"
#include <unistd.h>

int main() {
  Display& d = Display::get();
  d.startDisplay();
  while(true){
  for (int x = 0; x < 16; ++x) {
    d.setPixel(x, x, 1);
    d.setPixel(15-x, 15-x, 1);
    d.setPixel(15-x, x, 1);
    d.setPixel(x, 15-x, 1);
    d.update();
    usleep(200 * 1000);
    d.setPixel(x, x, 0);
    d.setPixel(15-x, 15-x, 0);
    d.setPixel(15-x, x, 0);
    d.setPixel(x, 15-x, 0);
    d.update();
  }
  }
  return 0;
}
