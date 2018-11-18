/**
 * Object bound info
 */
declare interface PixelsGroup {
  /**
   * Top left x coordinate of bound (percents of image width)
   */
  minX: number

  /**
   * Top left y coordinate of bound (percents of image height)
   */
  minY: number

  /**
   * Bottom right x coordinate of bound (percents of image width)
   */
  max_x: number

  /**
   * Bottom right y coordinate of bound (percents of image height)
   */
  maxY: number

  /**
   * Pixels count inside bound
   */
  pixelsCount: number
}

declare interface PixelsGroupsDetectionResult {
  /**
   * Input image width in pixels
   */
  imgWidth: number

  /**
   * Input image heights in pixels
   */
  imgHeight: number

  /**
   * Extract object pixels groups
   */
  groups: Array<PixelsGroup>
}

declare interface PixelsGroupsOptions {
  /**
   * Maximum gap between tow nearby pixels in group (percents of greatest image side)
   */
  maxGap: number
}

declare var bordersDetection: {
  pixelsGroups (file: string, options: PixelsGroupsOptions): Promise<PixelsGroupsDetectionResult>
}

export = bordersDetection
