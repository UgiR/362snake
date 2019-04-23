#include <unistd.h>
#include <signal.h>
#include "../display/Display.h"

volatile sig_atomic_t interupt = 0;

void sigint_handler(int sig) {
  interupt = 1;
}

int main() {
  signal(SIGINT, sigint_handler);
  Display& d = Display::get();
  d.startDisplay();
  for (int i = 0; i < 16; ++i) {
    d.setPixel(i, i, 1);
    d.setPixel(15-i, i, 1);
  }
  d.update();
  int i = 0;
  while(i < 10) {
    if (interupt) exit(0);
    sleep(1);
    ++i;
  }
}
