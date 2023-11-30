#include "renderer.h"

#include <iostream>

using namespace std;
using namespace engine::math;

namespace engine::gfx {
  Renderer::Renderer(Window* window)
    : _window(window) {
      set_perspective(90, 0.1f, 1000);
  }

  auto Renderer::set_perspective(float fov, float near, float far) -> void {
    float aspratio = (float)_window->h / _window->w;
    _projmat.set_perspective(fov, aspratio, near, far);
  }

  auto Renderer::render_add_mesh(mesh *mesh, vec3 pos, vec3 rot) -> void {
    _meshesToDraw.push_back( rend_info{mesh, pos, rot} );
  }

  auto Renderer::render() -> void {
    for(auto [mesh, pos, rot] : _meshesToDraw) {
      // Project verticies
      vec3 *projVerts = new vec3[mesh->verts.size()];
      for(int i = 0; i < mesh->verts.size(); ++i) {
        projVerts[i] = (mesh->verts[i] + pos) * _projmat;

        // scale to screen
        projVerts[i].x += 1;
        projVerts[i].y += 1;

        projVerts[i].x *= 0.5 * _window->w;
        projVerts[i].y *= 0.5 * _window->h;
      }

      // Draw faces
      for(auto [p1, p2, p3] : mesh->faces) {
        _window->draw_line(projVerts[p1].x, projVerts[p1].y, projVerts[p2].x, projVerts[p2].y);
        _window->draw_line(projVerts[p2].x, projVerts[p2].y, projVerts[p3].x, projVerts[p3].y);
        _window->draw_line(projVerts[p3].x, projVerts[p3].y, projVerts[p1].x, projVerts[p1].y);
      }

      delete [] projVerts;
    }

    _meshesToDraw.clear();
  }
}
