/**
 * Object bound info
 */
export interface PixelsGroup {
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
  maxX: number

  /**
   * Bottom right y coordinate of bound (percents of image height)
   */
  maxY: number

  /**
   * Pixels count inside bound
   */
  pixelsCount: number
}

export interface PixelsGroupsDetectionResult {
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

export interface PixelsGroupsOptions {
  /**
   * Maximum gap between tow nearby pixels in group (percents of greatest image side)
   */
  maxGap: number
}

export function pixelsGroups (file: string, options: PixelsGroupsOptions): Promise<PixelsGroupsDetectionResult>
