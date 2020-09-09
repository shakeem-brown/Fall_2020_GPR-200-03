#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

using namespace std;
using std::sqrt;

class vector3
{
    public:
        vector3() : e{ 0,0,0 } {} // e is an instance of a vector
        vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

        double x() const { return e[0]; } // e's x postion
        double y() const { return e[1]; } // e's y postion
        double z() const { return e[2]; } // e's z postion

        // Overloading operators using e's generated array
        // and returing the pointers to new arrays
        vector3 operator-() const { return vector3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vector3& operator+=(const vector3& v) 
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vector3& operator*=(const double t)
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vector3& operator/=(const double t) 
        {
            return *this *= 1 / t;
        }

        double length() const 
        {
            return sqrt(squared_length());
        }

        double squared_length() const 
        {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

    public:
        double e[3];
};

// Type aliases for vector3
using point3 = vector3;   // 3D point
using color = vector3;    // RGB color

#endif

//Constants for array postions
const int X_COORDINATE = 0, Y_COORDINATE = 1, Z_COORDINATE = 2;

// vector3 Utility Functions
// Overloads the standard operators to allow the vector to run
inline ostream& operator<<(ostream& out, const vector3& v) 
{
    return out << v.e[X_COORDINATE] << ' ' << v.e[Y_COORDINATE] << ' ' << v.e[Z_COORDINATE];
}

inline vector3 operator+(const vector3& u, const vector3& v) 
{
    return vector3(u.e[X_COORDINATE] + v.e[X_COORDINATE], u.e[Y_COORDINATE] + v.e[Y_COORDINATE], u.e[Z_COORDINATE] + v.e[Z_COORDINATE]);
}

inline vector3 operator-(const vector3& u, const vector3& v) 
{
    return vector3(u.e[X_COORDINATE] - v.e[X_COORDINATE], u.e[Y_COORDINATE] - v.e[Y_COORDINATE], u.e[Z_COORDINATE] - v.e[Z_COORDINATE]);
}

inline vector3 operator*(const vector3& u, const vector3& v)
{
    return vector3(u.e[X_COORDINATE] * v.e[X_COORDINATE], u.e[Y_COORDINATE] * v.e[Y_COORDINATE], u.e[Z_COORDINATE] * v.e[Z_COORDINATE]);
}

inline vector3 operator*(double t, const vector3& v) 
{
    return vector3(t * v.e[X_COORDINATE], t * v.e[Y_COORDINATE], t * v.e[Z_COORDINATE]);
}

inline vector3 operator*(const vector3& v, double t)
{
    return t * v;
}

inline vector3 operator/(vector3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vector3& u, const vector3& v) 
{
    return u.e[X_COORDINATE] * v.e[X_COORDINATE]
        + u.e[Y_COORDINATE] * v.e[Y_COORDINATE]
        + u.e[Z_COORDINATE] * v.e[Z_COORDINATE];
}

inline vector3 cross(const vector3& u, const vector3& v)
{
    return vector3(u.e[Y_COORDINATE] * v.e[Z_COORDINATE] - u.e[Z_COORDINATE] * v.e[Y_COORDINATE],
        u.e[Z_COORDINATE] * v.e[X_COORDINATE] - u.e[X_COORDINATE] * v.e[Z_COORDINATE],
        u.e[X_COORDINATE] * v.e[Y_COORDINATE] - u.e[Y_COORDINATE] * v.e[X_COORDINATE]);
}

inline vector3 unit_vector(vector3 v)
{
    return v / v.length();
}