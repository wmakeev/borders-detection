'use strict'

const path = require('path')
const assert = require('assert')
const { detectBorders } = require('..')

// #region IMAGE 01
const IMAGE_01 = path.join(__dirname, './img/01.bmp')

detectBorders(IMAGE_01, { maxGap: 0.1 })
  .then(result => {
    const RESULT_01 = {
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

    assert.deepEqual(result, RESULT_01)
  })
  .catch(err => { throw err })
// #endregion

// #region IMAGE 02
const IMAGE_02 = path.join(__dirname, './img/02.bmp')

detectBorders(IMAGE_02, { maxGap: 0.5 })
  .then(result => {
    assert.deepEqual(result, {
      imgWidth: 10,
      imgHeight: 10,
      borders: [
        { x: 0, y: 0, width: 1, height: 1, pixelsCount: 56 }
      ]
    })
  })
  .catch(err => { throw err })
// #endregion

// #region IMAGE 03
const IMAGE_03 = path.join(__dirname, './img/03.bmp')

detectBorders(IMAGE_03, { maxGap: 0.01 })
  .then(result => {
    assert.equal(result.borders.length, 13)
    assert.equal(result.borders[6].x, 0.31866666666666665)
    assert.equal(result.borders[6].pixelsCount, 8681)
  })
  .catch(err => { throw err })
// #endregion
