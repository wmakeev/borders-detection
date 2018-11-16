'use strict'

const { detectBorders } = require('bindings')('borders-detection')

module.exports = {
  detectBorders: (...args) => new Promise((resolve, reject) => {
    detectBorders(...args, (err, data) => {
      if (err) return reject(err)
      resolve(data)
    })
  })
}
