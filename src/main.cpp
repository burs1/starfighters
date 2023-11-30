#include "window.h"

using namespace engine;

int main (int argc, char *argv[]) {
  int i = 0;

  Window *window = new Window("starfighters", 1280, 720);
  
  while (++i < 10000) {
    window->update_events();
    window->update_surface();
  }

  delete window;

  return 0;
}
