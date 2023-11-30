#include "vec3.h"
#include "window.h"
#include "renderer.h"

using namespace engine;
using namespace engine::gfx;
using namespace engine::math;

int main (int argc, char *argv[]) {

  int timer = 0;
  Window *window = new Window("starfighters", 1280, 720);
  Renderer *renderer = new Renderer(window);

  mesh ship("cube.obj");


  while (++timer < 10000) {
    window->update_events();
    renderer->render_add_mesh(&ship, vec3(sin(timer / 500.0f), sin(timer / 250.0f), 5), vec3(0, 0, 0));
    renderer->render();
    window->update_surface();
  }

  delete renderer;
  delete window;

  return 0;
}
