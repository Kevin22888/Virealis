#ifndef VIREALIS_VECTOR3_H
#define VIREALIS_VECTOR3_H

#include <cmath>
#include <algorithm>
#include <iostream>

namespace virealis {

class Vector3 {
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Basic operations
    Vector3 operator*(const float &r) const;
    Vector3 operator/(const float &r) const;
    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
    Vector3& operator+=(const Vector3 &v);
    Vector3& operator-=(const Vector3 &v);
    Vector3 operator-() const;
    Vector3 operator*(const Vector3 &v) const;
    float operator[](int index) const;

    // Vector operations
    float magnitude() const;
    float magnitudeSquared() const;
    Vector3 normalized() const;
    Vector3 cross(const Vector3& v) const;
    float dot(const Vector3& v) const;

    // Static methods
    static Vector3 Min(const Vector3 &p1, const Vector3 &p2);
    static Vector3 Max(const Vector3 &p1, const Vector3 &p2);

    // Friends
    friend Vector3 operator*(const float &r, const Vector3 &v);
    friend std::ostream& operator<<(std::ostream &os, const Vector3 &v);
};

// Inline Definitions

inline Vector3 Vector3::operator*(const float &r) const {
    return Vector3(x * r, y * r, z * r);
}

inline Vector3 Vector3::operator/(const float &r) const {
    return Vector3(x / r, y / r, z / r);
}

inline Vector3 Vector3::operator+(const Vector3 &v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

inline Vector3 Vector3::operator-(const Vector3 &v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

inline Vector3& Vector3::operator+=(const Vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

inline Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator*(const Vector3 &v) const {
    return Vector3(x * v.x, y * v.y, z * v.z);
}

inline float Vector3::operator[](int index) const {
    return (&x)[index];
}

inline float Vector3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

inline float Vector3::magnitudeSquared() const {
    return x * x + y * y + z * z;
}

inline Vector3 Vector3::normalized() const {
    float n = std::sqrt(x * x + y * y + z * z);
    return Vector3(x / n, y / n, z / n);
}

inline Vector3 Vector3::cross(const Vector3& v) const { 
    return Vector3(y * v.z - z * v.y,
                    z * v.x - x * v.z,
                    x * v.y - y * v.x);
}

inline float Vector3::dot(const Vector3& v) const { 
    return x * v.x + y * v.y + z * v.z; 
}

inline Vector3 Vector3::Min(const Vector3 &p1, const Vector3 &p2) {
    return Vector3(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
}

inline Vector3 Vector3::Max(const Vector3 &p1, const Vector3 &p2) {
    return Vector3(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
}

inline Vector3 operator*(const float &r, const Vector3 &v) { 
    return Vector3(v.x * r, v.y * r, v.z * r); 
}

inline std::ostream& operator<<(std::ostream &os, const Vector3 &v) {
    return os << v.x << ", " << v.y << ", " << v.z;
}

}

#endif