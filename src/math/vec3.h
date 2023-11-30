/*
 * Author: Ilya Buravov
 *
 * Summary: 3D vector implementation
 *
 */

#pragma once

#include <cmath>

namespace engine::math {
  class vec3 {
  public:
    // === Constructors & Destructors ===
    /// Constructor
    explicit vec3(double p_x = 0, double p_y = 0, double p_z = 0);
    
    /// Copy constructor
    vec3(const vec3&);

    // === Methods ===
    /// vector's length
    constexpr auto magnitude()        const -> double;
    
    /// normalize components
    auto normalize()                        -> void;

    /// linear interpolation
    auto lerp(const vec3&, double)       -> void;

    // === Static methods ===
    /// normalize components
    static auto normalized(const vec3&)                          -> vec3;

    /// dot product
    constexpr static auto dot(const vec3&, const vec3&)       -> double;

    /// cross product
    static auto cross(const vec3&, const vec3&)               -> vec3;

    /// linear interpolation
    static auto lerp(const vec3&, const vec3&, double value)  -> vec3;

    // === Overloads ===
    /// Copy 
    auto operator=(const vec3&)          -> void;

    /// Summary
    auto operator+(const vec3&)    const -> vec3;

    auto operator+=(const vec3&)         -> void;

    /// Substract
    auto operator-(const vec3&)    const -> vec3;

    auto operator-=(const vec3&)         -> void;

    /// Scale
    auto operator*(const double&)     const -> vec3;

    auto operator*=(const double&)          -> void;

    auto operator/(const double&)     const -> vec3;

    auto operator/=(const double&)          -> void;

    /// Components comparison
    auto operator==(const vec3&)   const -> bool;

    auto operator!=(const vec3&)   const -> bool;

    /// Length comparison
    auto operator>(const vec3&)    const -> bool;

    auto operator>=(const vec3&)   const -> bool;

    auto operator<(const vec3&)    const -> bool;

    auto operator<=(const vec3&)   const -> bool;

    // === Attributes ===
    double x, y, z;
  };
}
