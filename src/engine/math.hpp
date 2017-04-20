#ifndef MATH_HPP
#define MATH_HPP

namespace enhuiz
{
namespace engine
{
struct Vector3
{
    float x = 0;
    float y = 0;
    float z = 0;

    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vector3 &operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3 &operator*=(float a)
    {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    Vector3 &operator/=(float a)
    {
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }

    Vector3 operator+(const Vector3 &other) const
    {
        Vector3 ret(*this);
        ret += other;
        return ret;
    }

    Vector3 operator-(const Vector3 &other) const
    {
        Vector3 ret(*this);
        ret -= other;
        return ret;
    }

    Vector3 operator*(float a) const
    {
        Vector3 ret(*this);
        ret *= a;
        return ret;
    }

    Vector3 operator/(float a) const
    {
        Vector3 ret(*this);
        ret /= a;
        return ret;
    }
};
}
}

#endif