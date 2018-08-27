import pytesseract

from PIL import Image

image = Image.open('1357042419_3300.jpg')

vcode = pytesseract.image_to_string(image)

print (vcode)