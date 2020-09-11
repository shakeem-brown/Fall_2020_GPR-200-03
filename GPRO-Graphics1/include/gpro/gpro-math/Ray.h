#pragma once

/*
    Modified by : ____Shakeem Brown & Andrew Barnett________
    Modified because : ___Needed to Add the ray class provided in Peter Shirley's
    "Ray Tracing in one Weekend" in order to create a ray which may or may not hit the object_________
*/

#ifndef RAY_H
#define RAY_H

#include "gpro/gpro-math/Vector3.h"

class ray
{
    public:
        ray() {} // Default constructor
        ray(const point3& origin, const vector3& direction) // Constructor
            : orig(origin), dir(direction)
        {}

        point3 origin() const { return orig; }
        vector3 direction() const { return dir; }

        point3 at(double t) const // point three is created by adding the orignal point
        {                         // with the time multiplied by the direction
            return orig + t * dir;
        }

    public:
        point3 orig;
        vector3 dir;
};

#endif
