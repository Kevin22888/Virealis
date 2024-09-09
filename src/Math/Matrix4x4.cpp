#include <virealis/Math/Matrix4x4.hpp>

namespace virealis {

// Identity Matrix
Matrix4x4 Matrix4x4::identity() {
    return Matrix4x4({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

// Translation Matrix
Matrix4x4 Matrix4x4::translation(const Vector3& translation) {
    Matrix4x4 result = Matrix4x4::identity();
    result(0, 3) = translation.x;
    result(1, 3) = translation.y;
    result(2, 3) = translation.z;
    return result;
}

// Rotation Matrix (using the axis-angle method)
Matrix4x4 Matrix4x4::rotation(float angle, const Vector3& axis) {
    Matrix4x4 result = Matrix4x4::identity();
    float cosTheta = std::cos(angle);
    float sinTheta = std::sin(angle);
    float oneMinusCos = 1.0f - cosTheta;

    Vector3 n = axis.normalized();
    float x = n.x;
    float y = n.y;
    float z = n.z;

    result(0, 0) = cosTheta + x * x * oneMinusCos;
    result(0, 1) = x * y * oneMinusCos - z * sinTheta;
    result(0, 2) = x * z * oneMinusCos + y * sinTheta;

    result(1, 0) = y * x * oneMinusCos + z * sinTheta;
    result(1, 1) = cosTheta + y * y * oneMinusCos;
    result(1, 2) = y * z * oneMinusCos - x * sinTheta;

    result(2, 0) = z * x * oneMinusCos - y * sinTheta;
    result(2, 1) = z * y * oneMinusCos + x * sinTheta;
    result(2, 2) = cosTheta + z * z * oneMinusCos;

    return result;
}

// Scale Matrix
Matrix4x4 Matrix4x4::scale(const Vector3& scale) {
    Matrix4x4 result = Matrix4x4::identity();
    result(0, 0) = scale.x;
    result(1, 0) = scale.y;
    result(2, 0) = scale.z;
    return result;
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
    Matrix4x4 projection = Matrix4x4::identity();

    float tanHalfFovy = tan((fov / 2.0f) * Constants::PI / 180.0f);  // Make sure to define MY_PI if it's not already done

    projection(0, 0) = 1.0f / (aspectRatio * tanHalfFovy);
    projection(1, 1) = 1.0f / tanHalfFovy;
    projection(2, 2) = (nearPlane + farPlane) / (nearPlane - farPlane);
    projection(2, 3) = -2.0f * nearPlane * farPlane / (nearPlane - farPlane);
    projection(3, 2) = 1.0f;
    projection(3, 3) = 0.0f;

    return projection;
}

Matrix4x4 Matrix4x4::orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    Matrix4x4 ortho = Matrix4x4::identity();

    ortho(0, 0) = 2.0f / (right - left);
    ortho(1, 1) = 2.0f / (top - bottom);
    ortho(2, 2) = 2.0f / (nearPlane - farPlane);
    ortho(0, 3) = -(right + left) / (right - left);
    ortho(1, 3) = -(top + bottom) / (top - bottom);
    ortho(2, 3) = -(nearPlane + farPlane) / (nearPlane - farPlane);

    return ortho;
}

// LookAt Matrix
Matrix4x4 Matrix4x4::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
    Vector3 f = (target - eye).normalized();
    Vector3 s = f.cross(up.normalized());
    Vector3 u = s.cross(f);

    Matrix4x4 result = Matrix4x4::identity();
    result(0, 0) = s.x;
    result(0, 1) = s.y;
    result(0, 2) = s.z;
    result(1, 0) = u.x;
    result(1, 1) = u.y;
    result(1, 2) = u.z;
    result(2, 0) = -f.x;
    result(2, 1) = -f.y;
    result(2, 2) = -f.z;

    result(0, 3) = -s.dot(eye);
    result(1, 3) = -u.dot(eye);
    result(2, 3) = f.dot(eye);

    return result;
}

// Transpose Matrix
Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = (*this)(j, i);
        }
    }
    return result;
}

// Determinant of the Matrix
float Matrix4x4::determinant() const {
    // Assuming the matrix is 4x4, we calculate the determinant using cofactor expansion.
    // Here, we'll calculate using the first row for simplicity.
    float subFactor00 = (*this)(2, 2) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 2);
    float subFactor01 = (*this)(2, 1) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 1);
    float subFactor02 = (*this)(2, 1) * (*this)(3, 2) - (*this)(2, 2) * (*this)(3, 1);
    float subFactor03 = (*this)(2, 0) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 0);
    float subFactor04 = (*this)(2, 0) * (*this)(3, 2) - (*this)(2, 2) * (*this)(3, 0);
    float subFactor05 = (*this)(2, 0) * (*this)(3, 1) - (*this)(2, 1) * (*this)(3, 0);

    return (*this)(0, 0) * ((*this)(1, 1) * subFactor00 - (*this)(1, 2) * subFactor01 + (*this)(1, 3) * subFactor02)
        - (*this)(0, 1) * ((*this)(1, 0) * subFactor00 - (*this)(1, 2) * subFactor03 + (*this)(1, 3) * subFactor04)
        + (*this)(0, 2) * ((*this)(1, 0) * subFactor01 - (*this)(1, 1) * subFactor03 + (*this)(1, 3) * subFactor05)
        - (*this)(0, 3) * ((*this)(1, 0) * subFactor02 - (*this)(1, 1) * subFactor04 + (*this)(1, 2) * subFactor05);
}

// Inverse Matrix
Matrix4x4 Matrix4x4::inverse() const {
    Matrix4x4 result;
    // Implementation of matrix inversion can be quite involved; for simplicity, assume a valid invertible matrix.
    // Calculate the inverse using an appropriate method (e.g., Gaussian elimination or cofactor method).
    // ...
    return result;
}

} // namespace virealis
