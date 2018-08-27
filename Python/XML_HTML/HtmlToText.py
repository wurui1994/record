# -*- coding: utf-8 -*-  
import re

urllist = open('items.info','r')
urls = urllist.readlines()
urllist.close()

DBUG   = 0

reBODY =re.compile( r'<body.*?>([\s\S]*?)<\/body>', re.I)
reCOMM = r'<!--.*?-->'
reTRIM = r'<{0}.*?>([\s\S]*?)<\/{0}>'
reTAG  = r'<[\s\S]*?>|[ \t\r\f\v]'

reIMG  = re.compile(r'<img[\s\S]*?src=[\'|"]([\s\S]*?)[\'|"][\s\S]*?>')

class Extractor():
    def __init__(self, data, blockSize=3, timeout=5, image=False):
        self.data = data
        # self.url       = url
        self.blockSize = blockSize
        self.timeout   = timeout
        self.saveImage = image
        self.rawPage   = ""
        self.ctexts    = []
        self.cblocks   = []

    def processTags(self):
        self.body = re.sub(reCOMM, "", self.body)
        self.body = re.sub(reTRIM.format("script"), "" ,re.sub(reTRIM.format("style"), "", self.body))
        # self.body = re.sub(r"[\n]+","\n", re.sub(reTAG, "", self.body))
        self.body = re.sub(reTAG, "", self.body)

    def processBlocks(self):
        self.ctexts   = self.body.split("\n")
        self.textLens = [len(text) for text in self.ctexts]

        self.cblocks  = [0]*(len(self.ctexts) - self.blockSize - 1)
        lines = len(self.ctexts)
        for i in range(self.blockSize):
            self.cblocks = list(map(lambda x,y: x+y, self.textLens[i : lines-1-self.blockSize+i], self.cblocks))

        # print(self.cblocks)
        if self.cblocks == []:return []
        maxTextLen = max(self.cblocks)

        if DBUG: print(maxTextLen)

        self.start = self.end = self.cblocks.index(maxTextLen)
        while self.start > 0 and self.cblocks[self.start] > min(self.textLens):
            self.start -= 1
        while self.end < lines - self.blockSize and self.cblocks[self.end] > min(self.textLens):
            self.end += 1

        return "".join(self.ctexts[self.start:self.end])

    def processImages(self):
        self.body = reIMG.sub(r'{{\1}}', self.body)

    def getContext(self):
        self.rawPage = self.data
        # self.rawPage = self.getRawPage()
        self.body = re.findall(reBODY, self.rawPage)[0]

        # if DBUG: print(code, self.rawPage)

        if self.saveImage:
            self.processImages()
        self.processTags()
        return self.processBlocks()
        # print(len(self.body.strip("\n")))


def trycode(filename,encode):
    try:
        print("try " + encode)
        file = open(filename,'rt',encoding = encode)
        data = file.read()
        file.close()
        return data
    except:
        print("not " + encode)
        return None

def tryread(filename):
    #
    encodelist = ['utf-8','gb2312','gb18030']
    
    for encode in encodelist:
        data = trycode(filename,encode)
        # print(data)
        if data != None:
            return data
    
    print("file cannot open")
    return None
    #
    # raise ValueError("not chinese code")
    
def mainloop(file):
    for line in urls:
        # remove '\n'
        url = line[:-1]
        filename = url.split('/')[-1]
        print(filename)

        # try read file
        data = tryread(filename)
        if data == None:continue

        try:
            ext = Extractor(data,blockSize=5,image=False)
            text = ext.getContext()
        except:
            continue
        # print(text)
        if len(text) ==  0:
            print("error")
            continue

        file.write(text+'\n\n')

##
filetxt = open("allinone.txt",'wt',encoding='UTF-8')
mainloop(filetxt)
filetxt.close()