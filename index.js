'use strict'

const { pixelsGroups } = require('bindings')('borders-detection')

module.exports = {
  pixelsGroups: (...args) => new Promise((resolve, reject) => {
    pixelsGroups(...args, (err, data) => {
      if (err) return reject(err)
      resolve(data)
    })
  })
}
