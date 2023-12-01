#include "renderer.h"

using namespace std;
using namespace engine::math;

namespace engine::gfx {
  Renderer::Renderer(Window* window, vec3 &campos, vec3 &camrot)
    : _window(window), campos(campos), camrot(camrot) {
      set_perspective(90, 0.1f, 1000);
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
      matrix4x4 rotmat;
      rotmat.set_rotX(rot.x);

      // Draw faces
      for(auto [p1, p2, p3] : mesh->faces) {
        vec3 curVerts[] = {mesh->verts[p1], mesh->verts[p2], mesh->verts[p3]};

        // Rotate, translate and project verticies
        for(int i = 0; i < 3; ++i) {
          curVerts[i] *= rotmat;
          curVerts[i] += pos;
          curVerts[i] = curVerts[i] * _projmat;
        }

        // Find normal
        vec3 nrml;
        nrml = vec3::cross(curVerts[2] - curVerts[0], curVerts[2] - curVerts[1]);
        nrml.normalize();

        // Don't draw if normal look in other direction
        if (vec3::dot(nrml, vec3::normalized(curVerts[0])) >= 0.0f) { continue; }

        // Scale to screen
        for(int i = 0; i < 3; ++i) {
          curVerts[i].x += 1;
          curVerts[i].y += 1;

          curVerts[i].x *= 0.5 * _window->resw;
          curVerts[i].y *= 0.5 * _window->resh;
        }

        // Draw lines
        for (int i = 0; i < 3; ++i)
          _window->draw_line(
            curVerts[i].x, curVerts[i].y,
            curVerts[(i + 1)%3].x, curVerts[(i + 1)%3].y
          );
      }
    }

    _meshesToDraw.clear();
  }
}
