#include "detect_borders.hpp"

void print_pixels(std::list<Pixel> &pixels)
{
  for (auto it = pixels.begin(), end = pixels.end(); it != end; it++)
    std::cout << "(" << (it->x) << "," << (it->y) << ") ";
  std::cout << std::endl;
}

void print_pixels_groups(std::list<std::list<Pixel>> &pixels_groups)
{
  for (auto it = pixels_groups.begin(), end = pixels_groups.end(); it != end; it++)
  {
    std::cout << "=> ";
    print_pixels(*it);
  }
}

void print_pixels_groups(std::list<PixelsGroup> &pixels_groups)
{
  int i = 1;
  for (auto it = pixels_groups.begin(), end = pixels_groups.end(); it != end; it++)
  {
    // auto item = *it; // DEBUG
    // auto border = *(it->border); // DEBUG
    // auto pixels = *(it->pixels); // DEBUG
    // auto size = it->pixels->size(); // DEBUG
    // auto bg = it->pixels->begin();
    // auto px = *(std::next(bg, 3));

    std::cout << "Group " << i << " - x:" << (it->border.x) << " y:" << (it->border.y);
    std::cout << " width:" << (it->border.width) << " height:" << (it->border.height);
    std::cout << " size:" << (it->pixels.size());
    std::cout << std::endl;

    // print_pixels(*(it->pixels));

    i++;
  }
}

// TODO Не выносится в отдельный заголовочный файл
// ошибка - unction is used but not defined in this translation unit
template <typename Func>
std::list<std::list<Pixel>> *split_by(std::list<Pixel> &pixels, Func selector,
                                      const unsigned int min_gap)
{
  std::list<std::list<Pixel>> *pixels_groups = new std::list<std::list<Pixel>>;
  std::list<Pixel> *pixels_group;
  std::list<Pixel>::iterator it, next_it, end;

  pixels.sort([selector](const Pixel &p1, const Pixel &p2) {
    // DEBUG
    // auto res1 = selector(p1);
    // auto res2 = selector(p2);

    return selector(p1) < selector(p2);
  });

  // std::cout << "sorted: ";
  // print_pixels(pixels); // DEBUG

  for (
      it = pixels.begin(), end = pixels.end(), next_it = std::next(it);
      next_it != end;
      next_it = std::next(++it))
  {
    // DEBUG
    // auto res1 = selector(*it);
    // auto res2 = selector(*next_it);

    if (selector(*next_it) - selector(*it) > min_gap)
    {
      it = next_it;

      pixels_group = new std::list<Pixel>;
      pixels_group->splice(
          pixels_group->begin(),
          pixels,
          pixels.begin(),
          it);

      // std::cout << "pixels_group: ";
      // print_pixels(*pixels_group); // DEBUG

      pixels_groups->push_back(*pixels_group);
    }
  }

  if (pixels.begin() != pixels.end())
    pixels_groups->push_back(pixels);

  return pixels_groups;
}

std::list<PixelsGroup> *detect_borders(const char *filename, const unsigned int min_gap)
{
  std::list<Pixel> *pixels_list = read_pixels(filename);
  // print_pixels(pixels_list); // DEBUG

  std::list<std::list<Pixel>> groups;
  std::list<std::list<Pixel>> *x_groups, *y_groups;
  std::list<std::list<Pixel>>::iterator x_group_it, y_group_it, group_it;

  x_groups = split_by(*pixels_list, [](const Pixel &px) { return px.x; }, min_gap);

  // print_pixels_groups(x_groups); // DEBUG

  for (x_group_it = x_groups->begin(); x_group_it != x_groups->end(); x_group_it++)
  {
    y_groups = split_by(*x_group_it, [](const Pixel &px) { return px.y; }, min_gap);
    for (y_group_it = y_groups->begin(); y_group_it != y_groups->end(); y_group_it++)
      groups.push_back(*y_group_it);
  }

  // print_pixels_groups(groups); // DEBUG

  std::list<PixelsGroup> *pixels_groups = new std::list<PixelsGroup>;
  for (group_it = groups.begin(); group_it != groups.end(); group_it++)
  {
    pixels_groups->push_back(PixelsGroup(*group_it));
  }

  // print_pixels_groups(*pixels_groups); // DEBUG

  return pixels_groups;
}
