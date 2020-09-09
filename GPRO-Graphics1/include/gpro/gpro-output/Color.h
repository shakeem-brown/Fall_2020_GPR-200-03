#pragma once

#ifndef COLOR_H
#define COLOR_H

#include "gpro/gpro-math/Vector3.h"

#include <iostream>

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

