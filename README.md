borders-detection
=================

[![npm](https://img.shields.io/npm/v/@wmakeev/borders-detection.svg?maxAge=1800&style=flat-square)](https://www.npmjs.com/package/@wmakeev/borders-detection)

> Native C++ module helps to detect objects bounds in 1-bit bmp image

## Install

> Tested on MacOS 10.14, NodeJs v9.2.0

`$ npm install @wmakeev/borders-detection`

## Usage

> *Supports only 1-bit bmp images*

```js
const { pixelsGroups } = require('borders-detection')

pixelsGroups('/path/to/img.bmp', { maxGap: 0.01 }).then(res => {
  if (err) throw err
  console.log('borders:', res)
})
```

## API

### `pixelsGroups(path: string, options: object): Promise`

- `path` - full path to bmp image

- `options.maxGap` - max distance between pixels in group (percents of largest image side)

#### Returns

```js
{
  imgWidth: 10,
  imgHeight: 10,
  groups: [
    { minX: 0, minY: 0, maxX: 0.2, maxY: 0.2, pixelsCount: 4 },
    { minX: 0.2, minY: 0.7, maxX: 0.3, maxY: 0.8, pixelsCount: 3 },
    { minX: 0.7, minY: 0.1, maxX: 0.8, maxY: 0.1, pixelsCount: 2 },
    { minX: 0.7, minY: 0.3, maxX: 0.8, maxY: 0.3, pixelsCount: 2 },
    { minX: 0.8, minY: 0.9, maxX: 0.9, maxY: 0.9, pixelsCount: 2 }
  ]
}
```

- `imgWidth` - input image width (pixels)

- `imgHeight` - input image height (pixels)

- `groups[]` - pixels groups bounds

- `groups[].minX` - top left x bound coordinate (percents of image width)

- `groups[].minY` - top left y bound coordinate (percents of image height)

- `groups[].maxX` - bottom right x bound coordinate (percents of image width)

- `groups[].maxY` - bottom right y bound coordinate (percents of image height)

- `groups[].pixelsCount` - pixels count inside bound

## Known issues

- Incorrect bound detection with hi-res images

## TODO

- Switch to [BPM](http://netpbm.sourceforge.net/doc/pbm.html) file format?
