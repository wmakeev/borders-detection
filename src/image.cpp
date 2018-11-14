#include "image.hpp"

Border get_object_border(std::list<Pixel> &pixels)
{
  unsigned int min_x, min_y, max_x, max_y;

  Pixel *first = &*(pixels.begin());

  min_x = max_x = first->x;
  min_y = max_y = first->y;

  std::list<Pixel>::iterator it, end;
  for (it = std::next(pixels.begin()), end = pixels.end(); it != end; it++)
  {
    // auto item = *it; // DEBUG
    if (it->x < min_x)
      min_x = it->x;
    if (it->x > max_x)
      max_x = it->x;
    if (it->y < min_y)
      min_y = it->y;
    if (it->y > max_y)
      max_y = it->y;
  }

  Border border{min_x, min_y, max_x - min_x + 1, max_y - min_y + 1};

  return border;
}
