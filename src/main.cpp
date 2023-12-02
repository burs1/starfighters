#include <cmath>
#include "vec3.h"
#include "scene.h"
#include "entity.h"
#include "window.h"
#include "renderer.h"

using namespace std;
using namespace engine;
using namespace engine::gfx;
using namespace engine::math;
using namespace engine::gmpl;

class Ship : public Entity {
private:
  void on_create() override {
    pos.z = 5;
  }

  void on_update() override {
    float deltaTime = get_delta_time();

    // input
    float rollAxis = input_axis(SDL_SCANCODE_A, SDL_SCANCODE_D);
    float tiltAxis = input_axis(SDL_SCANCODE_S, SDL_SCANCODE_W);
    float yawAxis = input_axis(SDL_SCANCODE_Q, SDL_SCANCODE_E);

    // velocity change
    rotVel.x = lerp(rotVel.x, tiltAxis * rotSp, rotAcc * deltaTime);
    rotVel.y = lerp(rotVel.y, yawAxis * rotSp, rotAcc * deltaTime);
    rotVel.z = lerp(rotVel.z, rollAxis * rotSp, rotAcc * deltaTime);

    // rotate
    rot += rotVel * deltaTime;
  }

  vec3 rotVel;
  float rotSp = 10;
  float rotAcc = 2;
  
};

int main (int argc, char *argv[]) {
  vec3 campos, camrot;

  // Init systems
  Window *window = new Window("starfighters", 400, 225, 1280, 720);
  Renderer *renderer = new Renderer(window, campos, camrot);
  float deltaTime = 0.016;

  Scene *scene = new Scene(window, renderer, deltaTime);

  // Load assets
  renderer->load_mesh("cube.obj", "ship");

  scene->instantiate_entity<Ship>("ship");

  // Delta time 
  int updateDelay = 16; //16 ticks ~ 60 fps
  Uint32 lastUpdateTime = window->get_ticks();
  Uint32 nextUpdateTime = window->get_ticks();

  vec3 shippos(0, 0, 8);
  vec3 shiprot(0, 0, 0);

  while (lastUpdateTime < 10000) {
    // Hold update untill it's time
    Uint32 currentTime = window->get_ticks();
    if (currentTime < nextUpdateTime) { continue; }


    lastUpdateTime = currentTime;
    nextUpdateTime = currentTime - currentTime % updateDelay + updateDelay;

    float timeScaled = currentTime / 1000.0f;

    window->update_events();
    scene->update();
    renderer->render();
    window->update_surface();
  }

  // Clean up
  delete scene;
  delete renderer;
  delete window;

  return 0;
}
