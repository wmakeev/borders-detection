#ifndef IMAGE_H
#define IMAGE_H

#include <list>

struct Pixel
{
  unsigned int x, y;
  Pixel(unsigned int _x, unsigned int _y) : x(_x), y(_y){};
};

struct Bound
{
  unsigned int min_x, min_y, max_x, max_y;
};

Bound get_object_bound(std::list<Pixel> &pixels);

struct PixelsGroup
{
  std::list<Pixel> pixels;
  Bound bound;
  PixelsGroup(std::list<Pixel> _pixels) : pixels(_pixels)
  {
    bound = get_object_bound(pixels);
  }
};

#endif
