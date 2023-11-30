#include "vec3.h"

namespace engine::math {
  // === Constructors & Destructors
  /// Constructor
  vec3::vec3(double p_x, double p_y, double p_z)
    : x(p_x), y(p_y), z(p_z) {}

  /// Copy constructor
  vec3::vec3(const vec3& other)
    : x(other.x), y(other.y), z(other.z) {}

  // === Methods ===
  /// Vector's length
  constexpr auto vec3::magnitude() const -> double {
    return sqrt(x * x + y * y + z * z);
  }

  /// Normalize components
  auto vec3::normalize() -> void {
    double length = magnitude();
    x /= length;
    y /= length;
    z /= length;
  }

  /// linear interpolation
  auto vec3::lerp(const vec3& other, double value) -> void {
    x = (other.x - x) * value;
    y = (other.y - y) * value;
    z = (other.z - z) * value;
 }

  // === Static methods ===
  /// normalize components
  auto vec3::normalized(const vec3& v) -> vec3 {
    double length = v.magnitude();
    return vec3(
      v.x / length,
      v.y / length,
      v.z / length
    );
  } 

  /// dot product
  constexpr auto vec3::dot(const vec3& v1, const vec3& v2) -> double {
    return v1.x * v2.x + v1.y * v2.y + v1.z + v2.z;
  }

  /// cross product
  auto cross(const vec3& v1, const vec3& v2) -> vec3 {
    return vec3(
      v1.y * v2.z - v1.y * v2.z,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x
    );
  }

  /// linear interpolation
  auto lerp(const vec3& v1, const vec3& v2, double value)  -> vec3 {
    return vec3(
      (v2.x - v1.x) * value,
      (v2.y - v1.y) * value,
      (v2.z - v1.z) * value
    );
  }

  // === Overloads ===
  // Copy
  auto vec3::operator=(const vec3& other) -> void {
    x = other.x;
    y = other.y;
    z = other.z;
  }

  /// Summary
  auto vec3::operator+(const vec3 &other) const -> vec3 {
    return vec3(x + other.x, y + other.y, z + other.z);
  }

  auto vec3::operator+=(const vec3 &other) -> void {
    x += other.x;
    y += other.y;
    z += other.z;
  }

  /// Substract
  auto vec3::operator-(const vec3 &other) const -> vec3 {
    return vec3(x - other.x, y - other.y, z - other.z);
  }

  auto vec3::operator-=(const vec3 &other) -> void {
    x -= other.x;
    y -= other.y;
    z -= other.z;
  }

  /// Matrix4x4 multiplication

  /// Scale
  auto vec3::operator*(const double &value) const -> vec3 {
    return vec3(x * value, y * value, z * value);
  }

  auto vec3::operator*=(const double &value) -> void {
    x *= value;
    y *= value;
    z *= value;
  }

  auto vec3::operator/(const double &value) const -> vec3 {
    return vec3(x / value, y / value, z / value);
  }

  auto vec3::operator/=(const double &value) -> void {
    x /= value;
    y /= value;
    z /= value;
  }

  /// Components comparison
  auto vec3::operator==(const vec3 &other) const -> bool {
    return x == other.x && y == other.y && z == other.z;
  }

  auto vec3::operator!=(const vec3 &other) const -> bool {
    return !(*this == other);
  }

  /// Length comparsion
  auto vec3::operator>(const vec3 &other) const -> bool {
    return this->magnitude() > other.magnitude();
  }

  auto vec3::operator>=(const vec3 &other) const -> bool {
    return this->magnitude() >= other.magnitude();
  }

  auto vec3::operator<(const vec3 &other) const -> bool {
    return this->magnitude() < other.magnitude();
  }

  auto vec3::operator<=(const vec3 &other) const -> bool {
    return this->magnitude() <= other.magnitude();
  }
}
