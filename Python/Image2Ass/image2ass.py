# usage: python image2ass.py image.png > image.ass
import sys
from PIL import Image, ImageSequence

argv = sys.argv

pixel_draw = "m 0 0 l 0 1 1 1 1 0"

if len(argv) < 2:
	print("usage: python %s image.png > image.ass" % argv[0])
else:
	im = Image.open(argv[1])
	index = 1
	for frame in ImageSequence.Iterator(im):
		print('-'*40 + str(index) + '-'*40)
		image = frame.convert("RGBA")
		for h in range(image.height):
			draw_content =""
			for w in range(image.width):
				r,g,b,a = image.getpixel((w,h))
				draw_content += r"{\1c&H%02X%02X%02X\1a&H%02X}%s" % (b,g,r,0xFF - a,pixel_draw)
			if len(draw_content) > 0:
				print(r"{\p1\bord0\shad0}" + draw_content + r"{\p0}\N",end="")
		print()
		index = index + 1