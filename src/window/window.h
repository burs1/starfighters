#pragma once

#include <map>
#include <sdl.h>
#include <string>
#include "sprite.h"
#include <stdexcept>
#include <sdl_image.h>

namespace engine {
  class Window {
  public:
    explicit Window (const char*, int, int, int, int, bool fullscreen=false);

    ~Window();

    // methods
    // ~ main
    auto update_events()                            -> void;

    auto update_surface()                           -> void;


    // ~ window
    auto toggle_fullscreen()                        -> void;


    // ~ user
    auto get_ticks()                                -> Uint32;

    // ~ input
    auto input_check(SDL_Scancode)                  -> bool;

    auto input_axis(SDL_Scancode, SDL_Scancode)     -> int;


    // ~ resources
    auto load_sprite(const char*, const char*) -> void;


    // ~ draw
    auto set_draw_color(Uint8, Uint8, Uint8, Uint8) -> void;

    auto draw_line(int, int, int, int)              -> void;
     
    auto draw_sprite(const char*, int, int, float, float) -> void;
    
    auto draw_sprite_ex(const char*, int, int, float, float, float, int, int) -> void;


    const bool &isOpened;
    const int &w, &h, &resw, &resh;

  private:
    // vars
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    const Uint8 *inputs;

    SDL_Color _clearColor = SDL_Color{0, 0, 0, 255};
    SDL_Color _drawColor = SDL_Color{255, 255, 255, 255};

    std::map< const char*, window::Sprite* > _sprites;

    int _w, _h, _resw, _resh;

    bool _fullscreen;
    bool _isOpened;
  };
}
