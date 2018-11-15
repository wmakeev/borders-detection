#ifndef BMP_H
#define BMP_H

using BYTE = unsigned char;      // 1 byte
using UINT = unsigned short int; // 2 byte
using WORD = short int;          // 2 byte
using DWORD = unsigned int;      // 4 byte
using LONG = unsigned int;       // 4 byte

struct BITMAPFILEHEADER
{ /* bmfh */
  /* Specifies the type of file. This member must be BM. */
  UINT bfType;

  /* Specifies the size of the file, in bytes. */
  DWORD bfSize;

  /* Reserved; must be set to zero. */
  UINT bfReserved1;

  /* Reserved; must be set to zero. */
  UINT bfReserved2;

  /* Specifies the byte offset from the BITMAPFILEHEADER structure
  to the actual bitmap data in the file. */
  DWORD bfOffBits;
};

struct BITMAPINFOHEADER
{ /* bmih */
  /* Specifies the number of bytes required by the BITMAPINFOHEADER structure. */
  DWORD biSize;

  /* Specifies the width of the bitmap, in pixels. */
  LONG biWidth;

  /* Specifies the height of the bitmap, in pixels. */
  LONG biHeight;

  /* Specifies the number of planes for the target device. This member must be set to 1. */
  WORD biPlanes;

  /* Specifies the number of bits per pixel. This value must be 1, 4, 8, or 24. */
  WORD biBitCount;

  /* Specifies the type of compression for a compressed bitmap. It
  can be one of the following values:
    Value           Meaning

    BI_RGB          Specifies that the bitmap is not compressed.

    BI_RLE8         Specifies a run-length encoded format for bitmaps with 8 bits
    per pixel. The compression format is a 2-byte format consisting of a count
    byte followed by a byte containing a color index.  For more information, see
    the following Comments section.

    BI_RLE4         Specifies a run-length encoded format for bitmaps with 4 bits
    per pixel. The compression format is a 2-byte format consisting of a count
    byte followed by two word-length color indexes.  For more information, see
    the following Comments section. */
  DWORD biCompression;

  /* Specifies the size, in bytes, of the image. It is valid to
  set this member to zero if the bitmap is in the BI_RGB format. */
  DWORD biSizeImage;

  /* Specifies the horizontal resolution, in pixels per meter, of
  the target device for the bitmap. An application can use this value to select
  a bitmap from a resource group that best matches the characteristics of the
  current device. */
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;

  /* Specifies the number of color indexes in the color table
  actually used by the bitmap. If this value is zero, the bitmap uses the
  maximum number of colors corresponding to the value of the biBitCount member.
  For more information on the maximum sizes of the color table, see the
  description of the BITMAPINFO structure earlier in this topic.

  If the biClrUsed member is nonzero, it specifies the actual number of colors
  that the graphics engine or device driver will access if the biBitCount
  member is less than 24. If biBitCount is set to 24, biClrUsed specifies the
  size of the reference color table used to optimize performance of Windows
  color palettes.  If the bitmap is a packed bitmap (that is, a bitmap in which
  the bitmap array immediately follows the BITMAPINFO header and which is
  referenced by a single pointer), the biClrUsed member must be set to zero or
  to the actual size of the color table. */
  DWORD biClrUsed;

  /* Specifies the number of color indexes that are considered
  important for displaying the bitmap. If this value is zero, all colors are
  important. */
  DWORD biClrImportant;
};

// TODO Type length consistent with BITMAPINFOHEADER?
struct BITMAPV4HEADER
{                        /* http://www.fileformat.info/format/bmp/egff.htm */
  WORD Size;             /* Size of this header in bytes */
  LONG Width;            /* Image width in pixels */
  LONG Height;           /* Image height in pixels */
  WORD Planes;           /* Number of color planes */
  WORD BitsPerPixel;     /* Number of bits per pixel */
  DWORD Compression;     /* Compression methods used */
  DWORD SizeOfBitmap;    /* Size of bitmap in bytes */
  LONG HorzResolution;   /* Horizontal resolution in pixels per meter */
  LONG VertResolution;   /* Vertical resolution in pixels per meter */
  DWORD ColorsUsed;      /* Number of colors in the image */
  DWORD ColorsImportant; /* Minimum number of important colors */
  /* Fields added for Windows 4.x follow this line */

  DWORD RedMask;    /* Mask identifying bits of red component */
  DWORD GreenMask;  /* Mask identifying bits of green component */
  DWORD BlueMask;   /* Mask identifying bits of blue component */
  DWORD AlphaMask;  /* Mask identifying bits of alpha component */
  DWORD CSType;     /* Color space type */
  LONG RedX;        /* X coordinate of red endpoint */
  LONG RedY;        /* Y coordinate of red endpoint */
  LONG RedZ;        /* Z coordinate of red endpoint */
  LONG GreenX;      /* X coordinate of green endpoint */
  LONG GreenY;      /* Y coordinate of green endpoint */
  LONG GreenZ;      /* Z coordinate of green endpoint */
  LONG BlueX;       /* X coordinate of blue endpoint */
  LONG BlueY;       /* Y coordinate of blue endpoint */
  LONG BlueZ;       /* Z coordinate of blue endpoint */
  DWORD GammaRed;   /* Gamma red coordinate scale value */
  DWORD GammaGreen; /* Gamma green coordinate scale value */
  DWORD GammaBlue;  /* Gamma blue coordinate scale value */
};

struct RGBQUAD
{ /* rgbq */
BYTE rgbBlue;
BYTE rgbGreen;
BYTE rgbRed;
BYTE rgbReserved;
};

struct BITMAPINFO
{ /* bmi */
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[1];
};

struct BITMAPCOREHEADER
{ /* bmch */
  DWORD bcSize;
  short bcWidth;
  short bcHeight;
  WORD bcPlanes;
  WORD bcBitCount;
};

struct RGBTRIPLE
{ /* rgbt */
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
};

struct BITMAPCOREINFO
{ /* bmci */
  BITMAPCOREHEADER bmciHeader;
  RGBTRIPLE bmciColors[1];
};

#endif
