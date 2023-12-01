#pragma once

#include <sdl.h>
#include <stdexcept>

namespace engine {
  class Window {
  public:
    explicit Window (const char*, int, int, int, int, bool fullscreen=false);

    ~Window();

    // methods
    auto update_events()                            -> void;

    auto update_surface()                           -> void;

    auto get_ticks()                                -> Uint32;

    auto input_check(SDL_Scancode)                  -> bool;

    auto toggle_fullscreen()                        -> void;

    auto set_draw_color(Uint8, Uint8, Uint8, Uint8) -> void;

    auto draw_line(int, int, int, int)              -> void;
    
    const bool &isOpened;
    const int &w, &h, &resw, &resh;

  private:
    // vars
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    const Uint8 *inputs;

    SDL_Color _clearColor = SDL_Color{0, 0, 0, 255};
    SDL_Color _drawColor = SDL_Color{255, 255, 255, 255};

    int _w, _h, _resw, _resh;

    bool _fullscreen;
    bool _isOpened;
  };
}
