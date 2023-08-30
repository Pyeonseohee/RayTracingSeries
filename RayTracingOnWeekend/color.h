#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>
using namespace std;

void write_color(ostream &out, color pixel_color){
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
    << static_cast<int>(255.999 * pixel_color.y()) << ' '
    << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif