/**
 * Object border info
 */
declare interface Border {
  /**
   * Top left x coordinate of border (percents of image width)
   */
  x: number

  /**
   * Top left y coordinate of border (percents of image height)
   */
  y: number

  /**
   * Border width (percents of image width)
   */
  width: number

  /**
   * Border width (percents of image height)
   */
  height: number

  /**
   * Pixels count inside border
   */
  pixelsCount: number
}

declare interface BorderDetectionResult {
  /**
   * Input image width in pixels
   */
  imgWidth: number

  /**
   * Input image heights in pixels
   */
  imgHeight: number

  /**
   * Detected object borders
   */
  borders: Array<Border>
}

declare var bordersDetection: {
  detectBorders (file: string, options: { maxGap: number }): Promise<BorderDetectionResult>
}

export = bordersDetection
