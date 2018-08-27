# -*- coding: utf-8 -*- 
from PyPDF2 import PdfFileReader,PdfFileWriter,ContentStream
filename = r'E:\Download\TCP-IP详解卷1：协议.pdf'
input = PdfFileReader(file(filename.decode('utf-8'),'rb'))
print input.getNumPages()
page = input.pages[4]
content = page["/Contents"].getObject()
content = ContentStream(content, page.pdf)
# output = PdfFileWriter()
# out = file('test.pdf','wb')
# output.addPage(input.pages[0])
# output.addPage(input.pages[1])
# output.addPage(input.pages[2])
# output.addPage(input.pages[3])
# output.addPage(input.pages[4])
# output.write(out)
# out.close()