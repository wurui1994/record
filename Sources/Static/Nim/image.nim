# nimble install imageman
import math
import random

import imageman

const
  Width = 400
  Height = 400
  Margin = 20

type Coords = tuple[x, y: float]

# The triangle.
const T = [Coords (0.0, 0.0), (1.0, 0.0), (0.5, 0.5 * tan(PI / 3))]

#---------------------------------------------------------------------------------------------------

func toPoint(v: Coords): Point =
  ## Convert [0..1] coordinates to image coordinates.
  ## We have to change scale, then to change position of y-axis.
  result = ((Margin + v.x * (Width - 2 * Margin)).toInt,
            ((Height - Margin) - v.y * (Height - 2 * Margin)).toInt)

#---------------------------------------------------------------------------------------------------

func side(p, p1, p2: Coords): float =
  ## Auxiliary function to check if a point is in a triangle.
  (p2.y - p1.y) * (p.x - p1.x) + (p1.x - p2.x) * (p.y - p1.y)

#---------------------------------------------------------------------------------------------------

proc firstPoint(): Coords =
  ## Choose the first point.

  while true:
    result = (x: rand(1.0), y: rand(1.0))
    let b1 = side(result, T[0], T[1]) >= 0
    let b2 = side(result, T[1], T[2]) >= 0
    let b3 = side(result, T[2], T[0]) >= 0
    if b1 == b2 and b2 == b3:
      # The point is in the triangle. Keep it.
      return

#———————————————————————————————————————————————————————————————————————————————————————————————————

const
  Iterations = 50_000
  Black = ColorRGBU [byte 0, 0, 0]
  White = ColorRGBU [byte 255, 255, 255]
  PointColor = ColorRGBU [byte 255, 255, 0]   # Color for points.

# Points in image coordinates.
const
  A = T[0].toPoint
  B = T[1].toPoint
  C = T[2].toPoint


randomize()
var image = initImage[ColorRGBU](Width, Height)
image.fill(Black)

# Draw the triangle.
image.drawLine(A, B, White)
image.drawLine(B, C, White)
image.drawLine(C, A, White)

var p = firstPoint()

for _ in 1..Iterations:
  let pt = p.toPoint
  image[pt.x, pt.y] = PointColor
  # Find position of next point.
  let idx = rand(2)
  p = ((p.x + T[idx].x) / 2, (p.y + T[idx].y) / 2)

image.savePNG("chaos_game.png", compression = 9)