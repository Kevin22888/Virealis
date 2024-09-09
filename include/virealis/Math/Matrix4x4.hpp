#ifndef VIREALIS_MATRIX4X4_H
#define VIREALIS_MATRIX4X4_H

#include <virealis/Math/Vector3.hpp>
#include <virealis/Math/Constants.hpp>
#include <array>
#include <iostream>

namespace virealis {

class Matrix4x4 {
private:
    std::array<float, 16> elements;

public:
    // Constructors
    Matrix4x4() : elements{0} {};
    Matrix4x4(const std::array<float, 16>& elements) : elements(elements) {};

    // Static methods for creating specific matrices
    static Matrix4x4 identity();
    static Matrix4x4 translation(const Vector3& translation);
    static Matrix4x4 rotation(float angle, const Vector3& axis);
    static Matrix4x4 scale(const Vector3& scale);
    static Matrix4x4 perspective(float fov, float aspect, float near, float far);
    static Matrix4x4 orthographic(float left, float right, float bottom, float top, float near, float far);

    // Matrix operations
    Matrix4x4 transpose() const;
    Matrix4x4 inverse() const;
    float determinant() const;

    // Operator overloads
    Matrix4x4 operator*(const Matrix4x4& other) const;
    Vector3 operator*(const Vector3& vector) const;
    Matrix4x4& operator*=(const Matrix4x4& other);
    float& operator()(int row, int col);
    float operator()(int row, int col) const;

    // Element-wise scalar operations
    Matrix4x4 operator*(float scalar) const;
    Matrix4x4 operator/(float scalar) const;
    Matrix4x4& operator*=(float scalar);
    Matrix4x4& operator/=(float scalar);

    // Element-wise matrix operations
    Matrix4x4 operator+(const Matrix4x4& other) const;
    Matrix4x4 operator-(const Matrix4x4& other) const;
    Matrix4x4& operator+=(const Matrix4x4& other);
    Matrix4x4& operator-=(const Matrix4x4& other);

    // Utility functions
    static Matrix4x4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
    static Matrix4x4 fromTranslationRotationScale(const Vector3& translation, const Vector3& rotation, const Vector3& scale);

    // Friends for symmetry and I/O
    friend Matrix4x4 operator*(float scalar, const Matrix4x4& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix);

    // Add this function to Matrix4x4
    const float* data() const {
        static std::array<float, 16> columnMajorElements;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                columnMajorElements[col * 4 + row] = elements[row * 4 + col];
            }
        }
        return columnMajorElements.data();
    }
};

// Inline Definitions

inline float& Matrix4x4::operator()(int row, int col) {
    return elements[row * 4 + col];
}

inline float Matrix4x4::operator()(int row, int col) const {
    return elements[row * 4 + col];
}

inline Matrix4x4 Matrix4x4::operator*(float scalar) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; ++i) {
        result.elements[i] = elements[i] * scalar;
    }
    return result;
}

inline Matrix4x4 Matrix4x4::operator/(float scalar) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; ++i) {
        result.elements[i] = elements[i] / scalar;
    }
    return result;
}

inline Matrix4x4& Matrix4x4::operator*=(float scalar) {
    for (int i = 0; i < 16; ++i) {
        elements[i] *= scalar;
    }
    return *this;
}

inline Matrix4x4& Matrix4x4::operator/=(float scalar) {
    for (int i = 0; i < 16; ++i) {
        elements[i] /= scalar;
    }
    return *this;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result(row, col) = 0;
            for (int i = 0; i < 4; ++i) {
                result(row, col) += (*this)(row, i) * other(i, col);
            }
        }
    }

    return result;
}

inline Vector3 Matrix4x4::operator*(const Vector3& vector) const {
    // Assume w = 1 for homogeneous coordinates
    float x = (*this)(0, 0) * vector.x + (*this)(0, 1) * vector.y + (*this)(0, 2) * vector.z + (*this)(0, 3);
    float y = (*this)(1, 0) * vector.x + (*this)(1, 1) * vector.y + (*this)(1, 2) * vector.z + (*this)(1, 3);
    float z = (*this)(2, 0) * vector.x + (*this)(2, 1) * vector.y + (*this)(2, 2) * vector.z + (*this)(2, 3);
    
    return Vector3(x, y, z);
}

inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
    *this = *this * other;  // Use the previously defined operator* for matrix multiplication
    return *this;
}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; ++i) {
        result.elements[i] = elements[i] + other.elements[i];
    }
    return result;
}

inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; ++i) {
        result.elements[i] = elements[i] - other.elements[i];
    }
    return result;
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
    for (int i = 0; i < 16; ++i) {
        elements[i] += other.elements[i];
    }
    return *this;
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
    for (int i = 0; i < 16; ++i) {
        elements[i] -= other.elements[i];
    }
    return *this;
}

inline Matrix4x4 operator*(float scalar, const Matrix4x4& matrix) {
    return matrix * scalar;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            os << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

} // namespace virealis

#endif // VIREALIS_MATRIX4X4_H
