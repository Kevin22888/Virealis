#ifndef VIREALIS_VECTOR2_H
#define VIREALIS_VECTOR2_H

#include <cmath>
#include <algorithm>
#include <iostream>

namespace virealis {

class Vector2 {
public:
    float x, y;

    // Constructors
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    // Basic operations
    Vector2 operator*(const float &r) const;
    Vector2 operator/(const float &r) const;
    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    Vector2& operator+=(const Vector2 &v);
    Vector2& operator-=(const Vector2 &v);
    Vector2 operator-() const;
    Vector2 operator*(const Vector2 &v) const;
    float operator[](int index) const;

    // Vector operations
    float magnitude() const;
    float magnitudeSquared() const;
    Vector2 normalized() const;
    float cross(const Vector2& v) const;
    float dot(const Vector2& v) const;

    // Static methods
    static Vector2 Min(const Vector2 &p1, const Vector2 &p2);
    static Vector2 Max(const Vector2 &p1, const Vector2 &p2);

    // Friends
    friend Vector2 operator*(const float &r, const Vector2 &v);
    friend std::ostream& operator<<(std::ostream &os, const Vector2 &v);
};

// Inline Definitions

inline Vector2 Vector2::operator*(const float &r) const {
    return Vector2(x * r, y * r);
}

inline Vector2 Vector2::operator/(const float &r) const {
    return Vector2(x / r, y / r);
}

inline Vector2 Vector2::operator+(const Vector2 &v) const {
    return Vector2(x + v.x, y + v.y);
}

inline Vector2 Vector2::operator-(const Vector2 &v) const {
    return Vector2(x - v.x, y - v.y);
}

inline Vector2& Vector2::operator+=(const Vector2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}

inline Vector2& Vector2::operator-=(const Vector2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

inline Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

inline Vector2 Vector2::operator*(const Vector2 &v) const {
    return Vector2(x * v.x, y * v.y);
}

inline float Vector2::operator[](int index) const {
    return (&x)[index];
}

inline float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

inline float Vector2::magnitudeSquared() const {
    return x * x + y * y;
}

inline Vector2 Vector2::normalized() const {
    float n = std::sqrt(x * x + y * y);
    return Vector2(x / n, y / n);
}

inline float Vector2::cross(const Vector2& v) const {
    return x * v.y - y * v.x;
}

inline float Vector2::dot(const Vector2& v) const {
    return x * v.x + y * v.y;
}

inline Vector2 Vector2::Min(const Vector2 &p1, const Vector2 &p2) {
    return Vector2(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
}

inline Vector2 Vector2::Max(const Vector2 &p1, const Vector2 &p2) {
    return Vector2(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
}

inline Vector2 operator*(const float &r, const Vector2 &v) { 
    return Vector2(v.x * r, v.y * r); 
}

inline std::ostream& operator<<(std::ostream &os, const Vector2 &v) {
    return os << v.x << ", " << v.y;
}

}

#endif
