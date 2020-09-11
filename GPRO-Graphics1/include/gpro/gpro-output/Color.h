#pragma once

/*
    Modified by : ____Shakeem Brown & Andrew Barnett________
    Modified because : ___Needed to Add the specific three colors provided in Peter Shirley's
    "Ray Tracing in one Weekend" in order to color the object correctly_________
*/

#ifndef COLOR_H
#define COLOR_H

#include "gpro/gpro-math/Vector3.h"

#include <iostream>

// Constants
const double IMAGE_EDGE = 255.999;

// Color utility Function
void write_color(std::ostream& out, color pixel_color)
{
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(IMAGE_EDGE * pixel_color.x()) << ' '
        << static_cast<int>(IMAGE_EDGE * pixel_color.y()) << ' '
        << static_cast<int>(IMAGE_EDGE * pixel_color.z()) << endl;
}

#endif

