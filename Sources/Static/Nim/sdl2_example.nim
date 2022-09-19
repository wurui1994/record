## needs sdl2 ("nimble install sdl2")

import sdl2, random

let
  max_it = 50000
  size = [800, 600]
  v = [
    [0, 0],
    [size[0] - 1, 0],
    [size[0] div 2, size[1] - 1]
    ]

discard sdl2.init(INIT_EVERYTHING)

var
  window: WindowPtr
  render: RendererPtr

window = createWindow("chaos", 100, 100, cint(size[0]), cint(size[1]), SDL_WINDOW_SHOWN)
render = createRenderer(window, -1, Renderer_Accelerated or
    Renderer_PresentVsync or Renderer_TargetTexture)

var
  evt = sdl2.defaultEvent
  runGame = true
  it = 0
  r: Point

r.x = cint(rand(size[0] - 1))
r.y = cint(rand(size[1] - 1))
render.setDrawColor(0, 0, 0)
render.clear

while it < max_it:
  let vn = rand(2)
  r.x = cint((r.x + v[vn][0]) div 2)
  r.y = cint((r.y + v[vn][1]) div 2)
  if vn == 0:
    render.setDrawColor(255, 0, 0)
  elif vn == 1:
    render.setDrawColor(0, 255, 0)
  else:
    render.setDrawColor(0, 0, 255)
  render.drawPoint(r.x, r.y)
  inc it

while runGame:
  render.present
  delay(100)
  while pollEvent(evt):
    if evt.kind == QuitEvent:
      runGame = false
      break

destroy render
destroy window