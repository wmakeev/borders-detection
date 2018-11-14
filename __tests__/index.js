'use strict'

const path = require('path')
const assert = require('assert')
const { detectBordersSync, detectBorders } = require('..')

// #region IMAGE 01

const IMAGE_01_URL = path.join(__dirname, './img/01.bmp')

let borders01 = detectBordersSync(IMAGE_01_URL, { minGap: 1 })

const BORDERS_01 = [
  {
    'border': { 'x': 0, 'y': 0, 'width': 3, 'height': 3 },
    'pixels': [[0, 0], [1, 1], [2, 1], [1, 2]]
  },
  {
    'border': { 'x': 2, 'y': 7, 'width': 2, 'height': 2 },
    'pixels': [[2, 7], [2, 8], [3, 8]]
  },
  {
    'border': { 'x': 7, 'y': 1, 'width': 2, 'height': 1 },
    'pixels': [[7, 1], [8, 1]]
  },
  {
    'border': { 'x': 7, 'y': 3, 'width': 2, 'height': 1 },
    'pixels': [[7, 3], [8, 3]]
  },
  {
    'border': { 'x': 8, 'y': 9, 'width': 2, 'height': 1 },
    'pixels': [[8, 9], [9, 9]]
  }
]

assert.deepEqual(borders01, BORDERS_01)

// #endregion

// #region IMAGE 03

const IMAGE_03_URL = path.join(__dirname, './img/03.bmp')

let borders03 = detectBordersSync(IMAGE_03_URL, { minGap: 10 })

// console.log(JSON.stringify(borders03))

assert.equal(borders03.length, 12)
assert.equal(borders03[6].border.x, 560)
assert.equal(borders03[6].pixels[3][1], 53)

// #endregion

// #region IMAGE 02 (async)

const IMAGE_02_URL = path.join(__dirname, './img/02.bmp')

detectBorders(IMAGE_02_URL, { minGap: 1 }, (err, data) => {
  if (err) throw err
  assert.equal(1, data.length)
})

// #endregion
