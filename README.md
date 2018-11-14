borders-detection
=================

> Detect object borders in 1-bit bmp file

## Install

`$ npm install borders-detection`

## Usage

```js
const path = require('path')

const { detectBorders } = require('../build/Debug/borders-detection.node')

const IMAGE_PATH = path.join(__dirname, '../img/01.bmp')

let borders = detectBorders(IMAGE_01_URL, { minGap: 1 })

console.log('borders:', JSON.stringify(borders))
```

## Links

- [](https://github.com/JamesMGreene/napi-async-callback-example/blob/master/addon.cc)



