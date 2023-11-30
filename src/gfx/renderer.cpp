#include "renderer.h"

#include <iostream>

using namespace std;
using namespace engine::math;

namespace engine::gfx {
  Renderer::Renderer(Window* window)
    : _window(window) {
      set_perspective(60, 0.1f, 1000);
  }

  auto Renderer::set_perspective(float fov, float near, float far) -> void {
    float aspratio = (float)_window->resh / _window->resw;
    _projmat.set_perspective(fov, aspratio, near, far);
  }

  auto Renderer::render_add_mesh(mesh *mesh, vec3 pos, vec3 rot) -> void {
    _meshesToDraw.push_back( rend_info{mesh, pos, rot} );
  }

  auto Renderer::render() -> void {
    for(auto [mesh, pos, rot] : _meshesToDraw) {
      // Draw faces
      for(auto [p1, p2, p3] : mesh->faces) {
        // Project verticies
        vec3 projVerts[] = {mesh->verts[p1], mesh->verts[p2], mesh->verts[p3]};
        for(int i = 0; i < 3; ++i)
          projVerts[i] = (projVerts[i] + pos) * _projmat;

        // Find normal
        vec3 l1, l2, nrml;
        l1 = projVerts[1] - projVerts[0];
        l2 = projVerts[2] - projVerts[1];
        nrml = vec3::cross(l1, l2);

        // Don't draw if normal look in other direction
        if (nrml.z > 0)
          continue;

        // scale to screen
        for(int i = 0; i < 3; ++i) {
          projVerts[i].x += 1;
          projVerts[i].y += 1;

          projVerts[i].x *= 0.5 * _window->resw;
          projVerts[i].y *= 0.5 * _window->resh;
        }

        // Draw lines
        for (int i = 0; i < 3; ++i)
          _window->draw_line(
            projVerts[i].x, projVerts[i].y,
            projVerts[(i + 1)%3].x, projVerts[(i + 1)%3].y
          );
      }
    }

    _meshesToDraw.clear();
  }
}
