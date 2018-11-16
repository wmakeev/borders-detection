#include <iostream>
#include <string>
#include <list>

#include "detect_borders.hpp"

#define MAX_GAP 0.1

int main(int argc, char *argv[])
{
  const char *filename = "/Users/mvv/Dropbox/_Developer/_CPP/borders-detection/__tests__/img/01.bmp";

  LONG width, height;

  std::list<PixelsGroup> *pixels_groups = detect_borders(filename, MAX_GAP, width, height);

  print_pixels_groups(*pixels_groups);

  return 0;
}
