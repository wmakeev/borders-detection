#ifndef DETECT_BORDERS_H
#define DETECT_BORDERS_H

#include <iostream>
#include <string>
#include <list>

#include "image.hpp"
#include "read_pixels.hpp"

std::list<PixelsGroup> *detect_borders(const char *filename, const unsigned int min_gap);

void print_pixels_groups(std::list<std::list<Pixel>> &pixels_groups);

void print_pixels_groups(std::list<PixelsGroup> &pixels_groups);

#endif
