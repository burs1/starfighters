/*
 * Author: Ilya Buravov
 * 
 * Summary: Simple 4x4 matrix implementation
 *
 */

#pragma once

#include "vec3.h"

namespace engine::math {
  class matrix4x4 {
  public:
    // === Constructors and destructors ===
    /// Constructor
    matrix4x4();

    /// Copy constructor
    matrix4x4(const matrix4x4&);

    // === Methods ===
    /// Set "zero rotation" matrix
    auto setIdentity()                  -> void;

    /// Set translation by vector
    auto setTranslation(const vec3&) -> void;

    /// Return translation vector
    auto getTranslation()               -> vec3;

    /// Return rightward vector
    auto right()                        -> vec3;

    /// Return upward vector
    auto up()                           -> vec3;

    /// Return forward vector
    auto forward()                      -> vec3;

    /// Set scale by vector
    auto setScale(const vec3&)          -> void;

    /// Set rotation
    auto setRot(double, double, double) -> void;

    /// Set rotation
    auto setRot(const vec3&)            -> void;

    /// Set x rotation
    auto setRotX(double)                -> void;
    
    /// Set y rotation
    auto setRotY(double)                -> void;

    /// Set x rotation
    auto setRotZ(double)                -> void;

    /// Set perspective 
    auto setPerspective(double, double, double, double) -> void;

    // === Overloads ===
    /// Copy
    auto operator=(const matrix4x4&)    -> void;

  private:
    /// Copy values from other matrix
    auto __copy__(const matrix4x4&)     -> void;

    double values[4][4];
  };
}
