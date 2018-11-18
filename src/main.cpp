#include <iostream>
#include <string>
#include <list>

#include "pixels_groups.hpp"

#define MAX_GAP 0.1

int main(int argc, char *argv[])
{
  const char *filename = "/Users/mvv/Dropbox/_Developer/_CPP/borders-detection/__tests__/img/01.bmp";

  LONG width, height;

  std::list<PixelsGroup> *pixels_groups = get_pixels_groups(filename, MAX_GAP, width, height);

  print_pixels_groups(*pixels_groups);

  return 0;
}
