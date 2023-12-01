#include "vec3.h"
#include "window.h"
#include "renderer.h"
#include <iterator>

using namespace engine;
using namespace engine::gfx;
using namespace engine::math;

int main (int argc, char *argv[]) {
  vec3 campos, camrot;

  // Init systems
  Window *window = new Window("starfighters", 320, 180, 1280, 720);
  Renderer *renderer = new Renderer(window, campos, camrot);

  // Load assets
  mesh *ship = new mesh("ship.obj");

  // Delta time 
  int updateDelay = 16; //16 ticks ~ 60 fps
  Uint32 lastUpdateTime = window->get_ticks();
  Uint32 nextUpdateTime = window->get_ticks();

  vec3 shippos(0, 0, 8);

  while (lastUpdateTime < 10000) {
    // Hold update untill it's time
    Uint32 currentTime = window->get_ticks();
    if (currentTime < nextUpdateTime) { continue; }


    lastUpdateTime = currentTime;
    nextUpdateTime = currentTime - currentTime % updateDelay + updateDelay;

    float timeScaled = currentTime / 1000.0f;

    window->update_events();
    shippos.x += window->input_check(SDL_SCANCODE_D) - window->input_check(SDL_SCANCODE_A);
    renderer->render_add_mesh(ship, shippos, vec3(cos(timeScaled), 0, 0));
    renderer->render();
    window->update_surface();
  }

  // Clean up
  delete ship;

  delete renderer;
  delete window;

  return 0;
}
