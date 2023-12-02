#pragma once

#include <SDL_scancode.h>
#include <map>
#include <vector>
#include <string>
#include "camera.h"
#include "window.h"
#include "entity.h"
#include "renderer.h"

namespace engine::gmpl {
  class Entity;
  class Scene {
  public:
    Scene(Window*, gfx::Renderer*, const float&);

    ~Scene();


    // - Methods -------------------------
    // ~ main
    auto update() -> void;

    template<class T>
    auto instantiate_entity(const char* meshname="\0", const char* tag="\0") -> T* {
      static_assert(std::is_base_of<Entity, T>(), "This class doesn't derrives from the Entity class");

      T *entity = new T();
      _initialize_entity(entity, meshname, typeid(entity).name(), tag);
      return entity;
    }

    // ~ camera
    auto get_camera() -> Camera*;


    // ~ input
    auto input_check(SDL_Scancode) -> bool;

    auto input_axis(SDL_Scancode, SDL_Scancode) -> int;


    // ~ entities
    auto find_entity_by_type(const char*, int) -> Entity*;

    auto find_entity_by_tag(const char*)       -> Entity*;


    // ~ draw
    auto draw_spirte(const char*, int, int, float, float) -> void;
    
    auto draw_spirte_ex(const char*, int, int, float, float, float, int xcent=0, int ycent=0) -> void;

    auto render_mesh(const char*, math::vec3, math::vec3) -> void;


    // - Variables -----------------------
    const float &deltaTime;

  private:
    // - Internal methods ----------------
    auto _initialize_entity(Entity*, const char*, const char*, const char*) -> void;


    // - Variables -----------------------
    Camera _camera;

    Window *_window;
    gfx::Renderer *_renderer;

    std::map< const char*, Entity* >              _entitiesByTag;
    std::map< const char*, std::vector<Entity*> > _entitiesByType;


  };
}
