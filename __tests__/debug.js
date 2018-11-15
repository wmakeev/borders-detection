const path = require('path')

const {
  detectBordersSync,
  detectBorders
} = require('../build/Debug/borders-detection.node')

const IMAGE_01_URL = path.join(__dirname, './img/03.bmp')

let borders = detectBordersSync(IMAGE_01_URL, { minGap: 1 })

console.log('borders sync:', borders)

detectBorders(IMAGE_01_URL, { minGap: 1 }, (err, data) => {
  if (err) throw err
  console.log('borders async:', data)
})
