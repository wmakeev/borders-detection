#ifndef READ_PIXELS_H
#define READ_PIXELS_H

#include <list>

#include "bmp.hpp"
#include "image.hpp"

std::list<Pixel> *read_pixels(const char *filename, LONG &width, LONG &height);

#endif
