borders-detection
=================

[![npm](https://img.shields.io/npm/v/@wmakeev/borders-detection.svg?maxAge=1800&style=flat-square)](https://www.npmjs.com/package/@wmakeev/borders-detection)

> Detect object borders in 1-bit bmp file

## Install

`$ npm install borders-detection`

## Usage

*Supports only 1-bit bmp images*

```js
const { detectBorders } = require('borders-detection')

detectBorders('/path/to/img.bmp', { maxGap: 0.01 }).then(res => {
  if (err) throw err
  console.log('borders async:', res)
})
```

## Arguments

`detectBorders(path: string, options: object): Promise`

`path` - full path to bmp image
`options.maxGap` - max distance between pixels in group (in percents of largest image side)

## Result object

```js
{
  imgWidth: 10,
  imgHeight: 10,
  borders: [
    { x: 0, y: 0, width: 0.3, height: 0.3, pixelsCount: 4 },
    { x: 0.2, y: 0.7, width: 0.2, height: 0.2, pixelsCount: 3 },
    { x: 0.7, y: 0.1, width: 0.2, height: 0.1, pixelsCount: 2 },
    { x: 0.7, y: 0.3, width: 0.2, height: 0.1, pixelsCount: 2 },
    { x: 0.8, y: 0.9, width: 0.2, height: 0.1, pixelsCount: 2 }
  ]
}
```

- `imgWidth` - inpux image width (pixels)
- `imgHeight` - inpux image height (pixels)
- `borders[].x` - x coordinate of top left border corner (percents of image width)
- `borders[].y` - y coordinate of top left border corner (percents of image height)
- `borders[].width` - width of border (percents of image width)
- `borders[].height` - height of border (percents of image height)
- `borders[].pixelsCount` - pixels count inside border

## Known issues

- [] Incorrect border detection with hires images

## TODO

- Switch to [BPM](http://netpbm.sourceforge.net/doc/pbm.html) file format?
