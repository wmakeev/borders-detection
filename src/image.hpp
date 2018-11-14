#ifndef IMAGE_H
#define IMAGE_H

#include <list>

struct Pixel
{
  unsigned int x, y;
  Pixel(unsigned int _x, unsigned int _y) : x(_x), y(_y){};
};

struct Border
{
  unsigned int x, y, width, height;
};

Border get_object_border(std::list<Pixel> &pixels);

struct PixelsGroup
{
  std::list<Pixel> pixels;
  Border border;
  PixelsGroup(std::list<Pixel> _pixels) : pixels(_pixels)
  {
    border = get_object_border(pixels);
  }
};

#endif
