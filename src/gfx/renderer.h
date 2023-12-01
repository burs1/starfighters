#pragma once

#include <cmath>
#include <vector>
#include "mesh.h"
#include "vec3.h"
#include "matrix4x4.h"
#include "window/window.h"

namespace engine::gfx {

  class Renderer {
  public:
    Renderer(Window*, math::vec3&, math::vec3&);

    auto set_perspective(float, float, float)           -> void;

    auto render_add_mesh(mesh*, math::vec3, math::vec3) -> void;

    auto render() -> void;

  private:
    struct rend_info {
      mesh *mesh;
      math::vec3 pos, rot;
    };

    math::vec3 &campos, &camrot;

    std::vector< rend_info > _meshesToDraw;
    math::matrix4x4 _projmat;

    Window *_window;
  };
}
