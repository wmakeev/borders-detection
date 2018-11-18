const path = require('path')

const { pixelsGroups } = require('../build/Debug/borders-detection.node')

const IMAGE_PATH = path.join(__dirname, './img/01.bmp')

pixelsGroups(IMAGE_PATH, { maxGap: 0.1 }, (err, result) => {
  if (err) throw err
  console.log('Result:', result)
})
