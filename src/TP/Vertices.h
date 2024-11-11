#ifndef VERTICES_HPP
#define VERTICES_HPP

#include <vector>
#include <functional>
#include <iostream>
#include <cmath>

struct Vertices
{
    float x, y, z;
    unsigned face;
    Vertices() : x(0), y(0), z(0)
    {
        face = 0;
    }
    Vertices(float p) : x(p), y(p), z(p)
    {
        face = 0;
    }
    Vertices(const Vertices &vertices) : x(vertices.x), y(vertices.y), z(vertices.z)
    {
        face = vertices.face;
    }

    Vertices(Vertices &&vertices)
        : x(vertices.x), y(vertices.y), z(vertices.z), face(vertices.face)
    {
    }
    Vertices &operator=(const Vertices &vertices)
    {
        x = vertices.x;
        y = vertices.y;
        z = vertices.z;
        face = vertices.face;
        return *this;
    }
/*
    Vertices &operator=(Vertices &&vertices)
    {
        if (this != &vertices)
        {
            x = vertices.x;
            y = vertices.y;
            z = vertices.z;
            face = vertices.face;
        }
        return *this;
    }
*/
    void swap(Vertices &vertices)
    {
        using std::swap;
        swap(x, vertices.x);
        swap(y, vertices.y);
        swap(z, vertices.z);
        swap(face, vertices.face);
    }
    Vertices(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z)
    {
        face = 0;
    }
    Vertices operator+(const Vertices &rhs)
    {
        return Vertices((x + rhs.x), (y + rhs.y), (z + rhs.z));
    }
    Vertices operator-(const Vertices &rhs) const
    {
        return Vertices((x - rhs.x), (y - rhs.y), (z - rhs.z));
    }

    // TODO TEMplate
    Vertices operator*(float a) const
    {
        return Vertices((x * a), (y * a), (z * a));
    }

    Vertices operator*(double a) const
    {
        return Vertices((x * a), (y * a), (z * a));
    }

    Vertices operator*(int a) const
    {

        return Vertices((x * a), (y * a), (z * a));
    }

    Vertices operator/(float a) const
    {

        return Vertices((x / a), (y / a), (z / a));
    }

    Vertices operator/(int a) const
    {

        return Vertices((x / a), (y / a), (z / a));
    }

    friend std::ostream &operator<<(std::ostream &os, const Vertices &vec)
    {
        os << "x: " << vec.x
           << " y: " << vec.y
           << " z: " << vec.z << std::endl;
        return os;
    }

    bool operator>(const Vertices &rhs) const
    {
        if (x > rhs.x)
        {
            return true;
        }
        else if (x == rhs.x)
        {
            return y > rhs.y;
        }
        else
        {
            return false;
        }
    }
    bool operator<(const Vertices &rhs) const
    {
        if (x < rhs.x)
        {
            return true;
        }
        else if (x == rhs.x)
        {
            return y < rhs.y;
        }
        else
        {
            return false;
        }
    }
    bool operator==(const Vertices &rhs) const
    {
        return rhs.x == x && rhs.y == y && rhs.z == z;
    }

    bool operator!=(const Vertices &rhs) const
    {
        return !(*this == rhs);
    }
};

inline float dotProduct(const Vertices &v1, const Vertices &v2)
{
    // Example operation with the templated class instance
    return v1.x * v2.x + (v1.y * v2.y) + (v1.z * v2.z);
}
inline Vertices crossProduct(const Vertices &v1, const Vertices &v2)
{
    // Example operation with the templated class instance
    float x = (v1.y * v2.z) - (v1.z * v2.y);
    float y = (v1.z * v2.x) - (v1.x * v2.z);
    float z = (v1.x * v2.y) - (v1.y * v2.x);
    return Vertices(x, y, z);
}

inline float magn(const Vertices &vector)
{
    return std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

#endif
