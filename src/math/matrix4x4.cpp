/*
 * Author: Ilya Buravov
 *
 * Summary: Simple 4x4 matrix implementation
 *
 */

#include "matrix4x4.h"

#include <cmath>

namespace engine::math {
  // === Constructors and destructors ===
  /// Constructor
  matrix4x4::matrix4x4() {
    setIdentity();
  }

  /// Copy constructor
  matrix4x4::matrix4x4(const matrix4x4& other) {
    __copy__(other);
  }

  // === Methods ===
  /// Set identity
  auto matrix4x4::setIdentity() -> void {
    // fill matrix 
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j)
        values[i][j] = i == j ? 1 : 0;
    }

    // final matrix:
    // [1, 0, 0, 0]
    // [0, 1, 0, 0]
    // [0, 0, 1, 0]
    // [0, 0, 0, 1]
  }

  /// Set translation
  auto matrix4x4::setTranslation(const vec3& v) -> void {
    values[3][0] = v.x;
    values[3][1] = v.y;
    values[3][2] = v.z;
  }

  /// Return tranlslation v
  auto matrix4x4::getTranslation() -> vec3 {
    return vec3(values[3][0], values[3][1], values[3][2]);
  }

  /// Return rightward v
  auto matrix4x4::right() -> vec3 {
    return vec3(values[0][0], values[0][1], values[0][2]);
  }

  /// Return upward v
  auto matrix4x4::up() -> vec3 {
    return vec3(values[1][0], values[1][1], values[1][2]);
  }

  /// Return forward v
  auto matrix4x4::forward() -> vec3 {
    return vec3(values[2][0], values[2][1], values[2][2]);
  }

  /// Set scale
  auto matrix4x4::setScale(const vec3& v) -> void {
    values[0][0] = v.x;
    values[1][1] = v.y;
    values[2][2] = v.z;
  }

  /// Set rotation
  auto matrix4x4::setRot(double x, double y, double z) -> void {
    setRotX(x);
    setRotY(y);
    setRotZ(z);
  }

  /// Set rotation
  auto matrix4x4::setRot(const vec3& v) -> void {
    setRotX(v.x);
    setRotY(v.y);
    setRotZ(v.z);
  }

  /// Set x rotation
  auto matrix4x4::setRotX(double rot) -> void {
    values[1][1] = cos(rot);
    values[1][2] = sin(rot);
    values[2][1] = -sin(rot);
    values[2][2] = cos(rot);
  }
 
  /// Set y rotation
  auto matrix4x4::setRotY(double rot) -> void {
    values[0][0] = cos(rot);
    values[0][2] = -sin(rot);
    values[2][0] = sin(rot);
    values[2][2] = cos(rot);
  }

  /// Set z rotation
  auto matrix4x4::setRotZ(double rot) -> void {
    values[0][0] = cos(rot);
    values[0][1] = sin(rot);
    values[1][0] = -sin(rot);
    values[1][1] = cos(rot);
  }

  /// Set persprective
  auto matrix4x4::setPerspective(double fov, double aspect, double znear, double zfar) -> void {
		double yscale = 1.0f / tan(fov / 2.0f);
		double xscale = yscale / aspect;
		values[0][0] = xscale;
		values[1][1] = yscale;
		values[2][2] = zfar / (zfar - znear);
		values[2][3] = 1.0f;
		values[3][2] = (-znear * zfar) / (zfar - znear);
		values[3][3] = 0.0f;

	}
	auto matrix4x4::__copy__(const matrix4x4& other) -> void {
	  for (int i = 0; i < 4; ++i) {
	    for (int j = 0; j < 4; ++j)
	      values[i][j] = other.values[i][j];
	  }
	}

	// === Overloads ===
	/// Copy
	auto matrix4x4::operator=(const matrix4x4& other) -> void {
	  __copy__(other);
	}
}
