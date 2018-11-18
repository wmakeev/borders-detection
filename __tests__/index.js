'use strict'

const path = require('path')
const assert = require('assert')
const { pixelsGroups } = require('..')

// #region IMAGE 01
const IMAGE_01 = path.join(__dirname, './img/01.bmp')

pixelsGroups(IMAGE_01, { maxGap: 0.1 })
  .then(result => {
    const RESULT_01 = {
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

    assert.deepEqual(result, RESULT_01)
    console.log('Test 01 - OK')
  })
  .catch(err => { throw err })
// #endregion

// #region IMAGE 02
const IMAGE_02 = path.join(__dirname, './img/02.bmp')

pixelsGroups(IMAGE_02, { maxGap: 0.5 })
  .then(result => {
    assert.deepEqual(result, {
      imgWidth: 10,
      imgHeight: 10,
      groups: [
        { minX: 0, minY: 0, maxX: 0.9, maxY: 0.9, pixelsCount: 56 }
      ]
    })
    console.log('Test 02 - OK')
  })
  .catch(err => { throw err })
// #endregion

// #region IMAGE 03
const IMAGE_03 = path.join(__dirname, './img/03.bmp')

pixelsGroups(IMAGE_03, { maxGap: 0.01 })
  .then(result => {
    assert.equal(result.groups.length, 13)
    assert.equal(result.groups[6].minX, 0.31866666666666665)
    assert.equal(result.groups[6].pixelsCount, 8681)
    console.log('Test 03 - OK')
  })
  .catch(err => { throw err })
// #endregion
