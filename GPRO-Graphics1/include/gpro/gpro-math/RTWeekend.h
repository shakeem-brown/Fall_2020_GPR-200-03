#pragma once

#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// Usings
using namespace std;
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) // Converts the degress to radians
{
    return degrees * pi / 180.0;
}

// Common Headers
#include "gpro/gpro-math/Vector3.h"
#include "gpro/gpro-math/Hittable.h"

#endif