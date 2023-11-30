#include "window.h"
#include <SDL_events.h>

using namespace std;

namespace engine {
  Window::Window (const char *title, int w, int h, bool fullscreen)
    : _fullscreen(fullscreen), isOpened(_isOpened) {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      throw runtime_error(SDL_GetError());

    // Create window
    _window = SDL_CreateWindow(
      title, 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      w, h, 
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
  }

  Window::~Window() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_Quit();
  }

  auto Window::update_events() -> void {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {}
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

  auto Window::toggle_fullscreen() -> void {
    _fullscreen = !_fullscreen;
    SDL_SetWindowFullscreen(_window, _fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
  }

  auto Window::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) -> void {
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    _drawColor = SDL_Color{r, g, b, a};
  }
  
  auto Window::draw_line(int x1, int y1, int x2, int y2) -> void {
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
  }
}