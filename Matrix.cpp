#include "Matrix.h"
#include "MathUtil.h"
#include "MathTypes.h"
#include "../Log.h"

#include <assert.h>
#include <math.h>

namespace gameplay
{

static const float MATRIX_IDENTITY[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

Matrix::Matrix()
{
    *this = Matrix::identity();
}

Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

Matrix::Matrix(const float* m)
{
    set(m);
}

Matrix::Matrix(const Matrix& copy)
{
    memcpy(m, copy.m, MATRIX_SIZE);
}

Matrix::~Matrix()
{
}

const Matrix& Matrix::identity()
{
    static Matrix m(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 );
    return m;
}

const Matrix& Matrix::zero()
{
    static Matrix m(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0 );
    return m;
}

void Matrix::createLookAt(const Vector3& eyePosition, const Vector3& targetPosition, const Vector3& up, Matrix* dst)
{
    createLookAt(eyePosition.x, eyePosition.y, eyePosition.z, targetPosition.x, targetPosition.y, targetPosition.z,
                 up.x, up.y, up.z, dst);
}

void Matrix::createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                          float targetPositionX, float targetPositionY, float targetPositionZ,
                          float upX, float upY, float upZ, Matrix* dst)
{
    assert(dst);

    Vector3 eye(eyePositionX, eyePositionY, eyePositionZ);
    Vector3 target(targetPositionX, targetPositionY, targetPositionZ);
    Vector3 up(upX, upY, upZ);
    up.normalize();

    Vector3 zaxis;
    Vector3::subtract(eye, target, &zaxis);
    zaxis.normalize();

    Vector3 xaxis;
    Vector3::cross(up, zaxis, &xaxis);
    xaxis.normalize();

    Vector3 yaxis;
    Vector3::cross(zaxis, xaxis, &yaxis);
    yaxis.normalize();

    dst->m[0] = xaxis.x;
    dst->m[1] = yaxis.x;
    dst->m[2] = zaxis.x;
    dst->m[3] = 0.0f;

    dst->m[4] = xaxis.y;
    dst->m[5] = yaxis.y;
    dst->m[6] = zaxis.y;
    dst->m[7] = 0.0f;

    dst->m[8] = xaxis.z;
    dst->m[9] = yaxis.z;
    dst->m[10] = zaxis.z;
    dst->m[11] = 0.0f;

    dst->m[12] = -Vector3::dot(xaxis, eye);
    dst->m[13] = -Vector3::dot(yaxis, eye);
    dst->m[14] = -Vector3::dot(zaxis, eye);
    dst->m[15] = 1.0f;
}

void Matrix::createPerspective(float fieldOfView, float aspectRatio,
                                     float zNearPlane, float zFarPlane, Matrix* dst)
{
    assert(dst);
    assert(zFarPlane != zNearPlane);

    float f_n = 1.0f / (zFarPlane - zNearPlane);
    float theta = MATH_DEG_TO_RAD(fieldOfView) * 0.5f;
    if (fabs(fmod(theta, MATH_PIOVER2)) < MATH_EPSILON)
    {
		HSG_ERROR("Invalid field of view value (%d) causes attempted calculation tan(%d), which is undefined.", fieldOfView, theta);
        return;
    }
    float divisor = tan(theta);
    assert(divisor);
    float factor = 1.0f / divisor;

    memset(dst, 0, MATRIX_SIZE);

    assert(aspectRatio);
    dst->m[0] = (1.0f / aspectRatio) * factor;
    dst->m[5] = factor;
    dst->m[10] = (-(zFarPlane + zNearPlane)) * f_n;
    dst->m[11] = -1.0f;
    dst->m[14] = -2.0f * zFarPlane * zNearPlane * f_n;
}

void Matrix::createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix* dst)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, dst);
}

void Matrix::createOrthographicOffCenter(float left, float right, float bottom, float top,
                                         float zNearPlane, float zFarPlane, Matrix* dst)
{
    assert(dst);
    assert(right != left);
    assert(top != bottom);
    assert(zFarPlane != zNearPlane);

    float r_l = 1.0f / (right - left);
    float t_b = 1.0f / (top - bottom);
    float f_n = 1.0f / (zFarPlane - zNearPlane);

    memset(dst, 0, MATRIX_SIZE);
    dst->m[0] = 2.0f * r_l;
    dst->m[5] = 2.0f * t_b;
    dst->m[10] = -2.0f * f_n;
    dst->m[12] = (-(right + left)) * r_l;
    dst->m[13] = (-(top + bottom)) * t_b;
    dst->m[14] = (-(zFarPlane + zNearPlane)) * f_n;
    dst->m[15] = 1.0f;
}
    
void Matrix::createScale(const Vector3& scale, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[0] = scale.x;
    dst->m[5] = scale.y;
    dst->m[10] = scale.z;
}

void Matrix::createScale(float xScale, float yScale, float zScale, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[0] = xScale;
    dst->m[5] = yScale;
    dst->m[10] = zScale;
}

void Matrix::createRotation(const Vector3& axis, float angle, Matrix* dst)
{
    assert(dst);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    // Make sure the input axis is normalized.
    float n = x*x + y*y + z*z;
    if (n != 1.0f)
    {
        // Not normalized.
        n = sqrt(n);
        // Prevent divide too close to zero.
        if (n > 0.000001f)
        {
            n = 1.0f / n;
            x *= n;
            y *= n;
            z *= n;
        }
    }

    float c = cos(angle);
    float s = sin(angle);

    float t = 1.0f - c;
    float tx = t * x;
    float ty = t * y;
    float tz = t * z;
    float txy = tx * y;
    float txz = tx * z;
    float tyz = ty * z;
    float sx = s * x;
    float sy = s * y;
    float sz = s * z;

    dst->m[0] = c + tx*x;
    dst->m[1] = txy + sz;
    dst->m[2] = txz - sy;
    dst->m[3] = 0.0f;

    dst->m[4] = txy - sz;
    dst->m[5] = c + ty*y;
    dst->m[6] = tyz + sx;
    dst->m[7] = 0.0f;

    dst->m[8] = txz + sy;
    dst->m[9] = tyz - sx;
    dst->m[10] = c + tz*z;
    dst->m[11] = 0.0f;

    dst->m[12] = 0.0f;
    dst->m[13] = 0.0f;
    dst->m[14] = 0.0f;
    dst->m[15] = 1.0f;
}

void Matrix::createRotationX(float angle, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    float c = cos(angle);
    float s = sin(angle);

    dst->m[5]  = c;
    dst->m[6]  = s;
    dst->m[9]  = -s;
    dst->m[10] = c;
}

void Matrix::createRotationY(float angle, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    float c = cos(angle);
    float s = sin(angle);

    dst->m[0]  = c;
    dst->m[2]  = -s;
    dst->m[8]  = s;
    dst->m[10] = c;
}

void Matrix::createRotationZ(float angle, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    float c = cos(angle);
    float s = sin(angle);

    dst->m[0] = c;
    dst->m[1] = s;
    dst->m[4] = -s;
    dst->m[5] = c;
}

void Matrix::createTranslation(const Vector3& translation, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[12] = translation.x;
    dst->m[13] = translation.y;
    dst->m[14] = translation.z;
}

void Matrix::createTranslation(float xTranslation, float yTranslation, float zTranslation, Matrix* dst)
{
    assert(dst);

    memcpy(dst, MATRIX_IDENTITY, MATRIX_SIZE);

    dst->m[12] = xTranslation;
    dst->m[13] = yTranslation;
    dst->m[14] = zTranslation;
}

void Matrix::add(float scalar)
{
    add(scalar, this);
}

void Matrix::add(float scalar, Matrix* dst)
{
    assert(dst);

    MathUtil::addMatrix(m, scalar, dst->m);
}

void Matrix::add(const Matrix& m)
{
    add(*this, m, this);
}

void Matrix::add(const Matrix& m1, const Matrix& m2, Matrix* dst)
{
    assert(dst);

    MathUtil::addMatrix(m1.m, m2.m, dst->m);
}

float Matrix::determinant() const
{
    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];

    // Calculate the determinant.
    return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
}

void Matrix::getUpVector(Vector3* dst) const
{
    assert(dst);

    dst->x = m[4];
    dst->y = m[5];
    dst->z = m[6];
}

void Matrix::getDownVector(Vector3* dst) const
{
    assert(dst);
    
    dst->x = -m[4];
    dst->y = -m[5];
    dst->z = -m[6];
}

void Matrix::getLeftVector(Vector3* dst) const
{
    assert(dst);

    dst->x = -m[0];
    dst->y = -m[1];
    dst->z = -m[2];
}

void Matrix::getRightVector(Vector3* dst) const
{
    assert(dst);

    dst->x = m[0];
    dst->y = m[1];
    dst->z = m[2];
}

void Matrix::getForwardVector(Vector3* dst) const
{
    assert(dst);

    dst->x = -m[8];
    dst->y = -m[9];
    dst->z = -m[10];
}

void Matrix::getBackVector(Vector3* dst) const
{
    assert(dst);

    dst->x = m[8];
    dst->y = m[9];
    dst->z = m[10];
}

bool Matrix::invert()
{
    return invert(this);
}

bool Matrix::invert(Matrix* dst) const
{
    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];

    // Calculate the determinant.
    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

    // Close to zero, can't invert.
    if (fabs(det) <= MATH_TOLERANCE)
        return false;

    // Support the case where m == dst.
    Matrix inverse;
    inverse.m[0]  = m[5] * b5 - m[6] * b4 + m[7] * b3;
    inverse.m[1]  = -m[1] * b5 + m[2] * b4 - m[3] * b3;
    inverse.m[2]  = m[13] * a5 - m[14] * a4 + m[15] * a3;
    inverse.m[3]  = -m[9] * a5 + m[10] * a4 - m[11] * a3;

    inverse.m[4]  = -m[4] * b5 + m[6] * b2 - m[7] * b1;
    inverse.m[5]  = m[0] * b5 - m[2] * b2 + m[3] * b1;
    inverse.m[6]  = -m[12] * a5 + m[14] * a2 - m[15] * a1;
    inverse.m[7]  = m[8] * a5 - m[10] * a2 + m[11] * a1;

    inverse.m[8]  = m[4] * b4 - m[5] * b2 + m[7] * b0;
    inverse.m[9]  = -m[0] * b4 + m[1] * b2 - m[3] * b0;
    inverse.m[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
    inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;

    inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
    inverse.m[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
    inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
    inverse.m[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;

    multiply(inverse, 1.0f / det, dst);

    return true;
}

bool Matrix::isIdentity() const
{
    return (memcmp(m, MATRIX_IDENTITY, MATRIX_SIZE) == 0);
}

void Matrix::multiply(float scalar)
{
    multiply(scalar, this);
}

void Matrix::multiply(float scalar, Matrix* dst) const
{
    multiply(*this, scalar, dst);
}

void Matrix::multiply(const Matrix& m, float scalar, Matrix* dst)
{
    assert(dst);

    MathUtil::multiplyMatrix(m.m, scalar, dst->m);
}

void Matrix::multiply(const Matrix& m)
{
    multiply(*this, m, this);
}

void Matrix::multiply(const Matrix& m1, const Matrix& m2, Matrix* dst)
{
    assert(dst);

    MathUtil::multiplyMatrix(m1.m, m2.m, dst->m);
}

void Matrix::negate()
{
    negate(this);
}

void Matrix::negate(Matrix* dst) const
{
    assert(dst);

    MathUtil::negateMatrix(m, dst->m);
}

void Matrix::rotate(const Vector3& axis, float angle)
{
    rotate(axis, angle, this);
}

void Matrix::rotate(const Vector3& axis, float angle, Matrix* dst) const
{
    Matrix r;
    createRotation(axis, angle, &r);
    multiply(*this, r, dst);
}

void Matrix::rotateX(float angle)
{
    rotateX(angle, this);
}

void Matrix::rotateX(float angle, Matrix* dst) const
{
    Matrix r;
    createRotationX(angle, &r);
    multiply(*this, r, dst);
}

void Matrix::rotateY(float angle)
{
    rotateY(angle, this);
}

void Matrix::rotateY(float angle, Matrix* dst) const
{
    Matrix r;
    createRotationY(angle, &r);
    multiply(*this, r, dst);
}

void Matrix::rotateZ(float angle)
{
    rotateZ(angle, this);
}

void Matrix::rotateZ(float angle, Matrix* dst) const
{
    Matrix r;
    createRotationZ(angle, &r);
    multiply(*this, r, dst);
}

void Matrix::scale(float value)
{
    scale(value, this);
}

void Matrix::scale(float value, Matrix* dst) const
{
    scale(value, value, value, dst);
}

void Matrix::scale(float xScale, float yScale, float zScale)
{
    scale(xScale, yScale, zScale, this);
}

void Matrix::scale(float xScale, float yScale, float zScale, Matrix* dst) const
{
    Matrix s;
    createScale(xScale, yScale, zScale, &s);
    multiply(*this, s, dst);
}

void Matrix::scale(const Vector3& s)
{
    scale(s.x, s.y, s.z, this);
}

void Matrix::scale(const Vector3& s, Matrix* dst) const
{
    scale(s.x, s.y, s.z, dst);
}

void Matrix::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    m[0]  = m11;
    m[1]  = m21;
    m[2]  = m31;
    m[3]  = m41;
    m[4]  = m12;
    m[5]  = m22;
    m[6]  = m32;
    m[7]  = m42;
    m[8]  = m13;
    m[9]  = m23;
    m[10] = m33;
    m[11] = m43;
    m[12] = m14;
    m[13] = m24;
    m[14] = m34;
    m[15] = m44;
}

void Matrix::set(const float* m)
{
    assert(m);
    memcpy(this->m, m, MATRIX_SIZE);
}

void Matrix::set(const Matrix& m)
{
    memcpy(this->m, m.m, MATRIX_SIZE);
}

void Matrix::setIdentity()
{
    memcpy(m, MATRIX_IDENTITY, MATRIX_SIZE);
}

void Matrix::setZero()
{
    memset(m, 0, MATRIX_SIZE);
}

void Matrix::subtract(const Matrix& m)
{
    subtract(*this, m, this);
}

void Matrix::subtract(const Matrix& m1, const Matrix& m2, Matrix* dst)
{
    assert(dst);

    MathUtil::subtractMatrix(m1.m, m2.m, dst->m);
}

void Matrix::transformPoint(Vector3* point) const
{
    assert(point);
    transformVector(point->x, point->y, point->z, 1.0f, point);
}

void Matrix::transformPoint(const Vector3& point, Vector3* dst) const
{
    transformVector(point.x, point.y, point.z, 1.0f, dst);
}

void Matrix::transformVector(Vector3* vector) const
{
    assert(vector);
    transformVector(vector->x, vector->y, vector->z, 0.0f, vector);
}

void Matrix::transformVector(const Vector3& vector, Vector3* dst) const
{
    transformVector(vector.x, vector.y, vector.z, 0.0f, dst);
}

void Matrix::transformVector(float x, float y, float z, float w, Vector3* dst) const
{
    assert(dst);

    MathUtil::transformVector4(m, x, y, z, w, (float*)dst);
}

void Matrix::translate(float x, float y, float z)
{
    translate(x, y, z, this);
}

void Matrix::translate(float x, float y, float z, Matrix* dst) const
{
    Matrix t;
    createTranslation(x, y, z, &t);
    multiply(*this, t, dst);
}

void Matrix::translate(const Vector3& t)
{
    translate(t.x, t.y, t.z, this);
}

void Matrix::translate(const Vector3& t, Matrix* dst) const
{
    translate(t.x, t.y, t.z, dst);
}

void Matrix::transpose()
{
    transpose(this);
}

void Matrix::transpose(Matrix* dst) const
{
    assert(dst);

    MathUtil::transposeMatrix(m, dst->m);
}

}
