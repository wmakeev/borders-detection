#include <iostream>
#include <stdexcept>

#include "read_pixels.hpp"

std::list<Pixel> *read_pixels(const char *filename)
{
  FILE *f = fopen(filename, "rb");

  if (f == NULL)
    throw std::runtime_error("File not found");

  // read BITMAPFILEHEADER
  BITMAPFILEHEADER *file_header = new BITMAPFILEHEADER;
  fread(&(file_header->bfType), 1, sizeof(file_header->bfType), f);
  fread(&(file_header->bfSize), 1, sizeof(file_header->bfSize), f);
  fread(&(file_header->bfReserved1), 1, sizeof(file_header->bfReserved1), f);
  fread(&(file_header->bfReserved2), 1, sizeof(file_header->bfReserved2), f);
  fread(&(file_header->bfOffBits), 1, sizeof(file_header->bfOffBits), f);

  // read BITMAPINFOHEADER
  BITMAPINFOHEADER *info_header = new BITMAPINFOHEADER;

  fread(&(info_header->biSize), 1, sizeof(info_header->biSize), f);
  if (info_header->biSize < 40)
    throw std::runtime_error("Unsupported BMP file format");

  fread(&(info_header->biWidth), 1, sizeof(info_header->biWidth), f);
  fread(&(info_header->biHeight), 1, sizeof(info_header->biHeight), f);
  fread(&(info_header->biPlanes), 1, sizeof(info_header->biPlanes), f);

  fread(&(info_header->biBitCount), 1, sizeof(info_header->biBitCount), f);
  if (info_header->biBitCount != 1)
    throw std::runtime_error("Expected 1-bit image");

  fread(&(info_header->biCompression), 1, sizeof(info_header->biCompression), f);
  fread(&(info_header->biSizeImage), 1, sizeof(info_header->biSizeImage), f);
  fread(&(info_header->biXPelsPerMeter), 1, sizeof(info_header->biXPelsPerMeter), f);
  fread(&(info_header->biYPelsPerMeter), 1, sizeof(info_header->biYPelsPerMeter), f);
  fread(&(info_header->biClrUsed), 1, sizeof(info_header->biClrUsed), f);
  fread(&(info_header->biClrImportant), 1, sizeof(info_header->biClrImportant), f);

  if (info_header->biSize > 40) // if BITMAPV4HEADER (108) or other
    fseek(f, info_header->biSize - 40, SEEK_CUR);

  // read color table
  const int color_table_length = 2;
  RGBQUAD color_table[color_table_length];

  for (int i = 0; i < color_table_length; i++)
  {
    fread(&(color_table[i]), 1, sizeof(RGBQUAD), f);
  }

  // read image data
  const int row_bits = info_header->biWidth + (32 - (info_header->biWidth % 32));
  const int row_bytes = row_bits / 8;
  unsigned char *data = (unsigned char *)(malloc(row_bytes));

  unsigned char row_byte;
  int row, col, pixel, bit;
  bool row_end;

  std::list<Pixel> *pixels_list = new std::list<Pixel>;

  for (row = (int)info_header->biHeight - 1; row >= 0; row--)
  {
    fread(data, 1, row_bytes, f);
    col = 0; // bits in row
    row_end = false;
    do
    {
      row_byte = data[col / 8];
      for (bit = 7; bit >= 0; bit--)
      {
        pixel = (row_byte >> bit) & 1;

        // std::cout << (pixel == 1 ? "*" : "-"); // DEBUG

        if (pixel == 1)
          pixels_list->push_back(Pixel(col, row));

        if (++col == (int)info_header->biWidth)
        {
          row_end = true;
          // std::cout << std::endl; // DEBUG
          break;
        };
      }
    } while (!row_end);
  }

  fclose(f);

  return pixels_list;
}
