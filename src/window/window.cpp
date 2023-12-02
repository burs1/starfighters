#include "window.h"
#include <SDL_render.h>
#include <SDL_scancode.h>

using namespace std;
using namespace engine::window;

namespace engine {
  Window::Window (const char *title, int resw, int resh, int winw, int winh, bool fullscreen)
    : _fullscreen(fullscreen), isOpened(_isOpened),
    _w(winw), _h(winh), w(_w), h(_h),
    _resw(resw), _resh(resh), resw(_resw), resh(_resh) {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      throw runtime_error(SDL_GetError());

    // Create window
    _window = SDL_CreateWindow(
      title, 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      _w, _h, 
      _fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN
    );

    if (_window == NULL)
      throw runtime_error(SDL_GetError());

    // Create renderer
    _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED
    );

    if (_renderer == NULL)
      throw runtime_error(SDL_GetError());

    SDL_RenderSetLogicalSize(_renderer, resw, resh);
  }

  Window::~Window() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_Quit();
  }

  // methods
  // ~ main
  auto Window::update_events() -> void {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {}

    inputs = SDL_GetKeyboardState(NULL);
  }

  auto Window::update_surface() -> void {
    SDL_RenderPresent(_renderer);

    // Clear renderer
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    // Set draw color back
    SDL_SetRenderDrawColor(_renderer,
      _drawColor.r,
      _drawColor.g,
      _drawColor.b,
      _drawColor.a
    );
  }

  // ~ user
  auto Window::get_ticks() -> Uint32 {
    return SDL_GetTicks();
  }

  // ~ input
  auto Window::input_check(SDL_Scancode scancode) -> bool {
    return inputs[scancode];
  }

  auto Window::input_axis(SDL_Scancode l, SDL_Scancode r) -> int {
    return inputs[r] - inputs[l];
  }


  
  // ~ window
  auto Window::toggle_fullscreen() -> void {
    _fullscreen = !_fullscreen;
    SDL_SetWindowFullscreen(_window, _fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
  }

  // ~ resources
  auto Window::load_sprite(const char *path, const char *name) -> void {
    // Check if sprite was already opened
    if (_sprites.contains(name))
      throw runtime_error("Sprite with name \"" + string(name) + "\" already exists");

    SDL_Texture* texture = IMG_LoadTexture(_renderer, path);

    // Check if texture was successfuly loaded
    if (not texture)
      throw runtime_error( SDL_GetError() );

    _sprites[name] = new Sprite(texture);

  }


  // ~ draw
  auto Window::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) -> void {
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    _drawColor = SDL_Color{r, g, b, a};
  }
  
  auto Window::draw_line(int x1, int y1, int x2, int y2) -> void {
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
  }
  
  auto Window::draw_sprite(const char* sprname, int x, int y, float xscale, float yscale) -> void {
    Sprite *spr = _sprites[sprname];
    SDL_Rect draw_rect{x, y, int(spr->w * xscale), int(spr->h * yscale)};

    if (SDL_RenderCopy(_renderer, spr->texture, &spr->rect, &draw_rect) < 0)
      throw runtime_error( SDL_GetError() );
  }

  auto Window::draw_sprite_ex(const char* sprname, int x, int y, float xscale, float yscale, float angle, int xcent, int ycent) -> void {
    Sprite *spr = _sprites[sprname];
    SDL_Rect draw_rect{x, y, int(spr->w * xscale), int(spr->h * yscale)};
    SDL_Point center{xcent, ycent};

    if (SDL_RenderCopyEx(_renderer, spr->texture, &spr->rect, &draw_rect, angle, &center, SDL_FLIP_NONE) < 0)
      throw runtime_error( SDL_GetError() );
  }

}
