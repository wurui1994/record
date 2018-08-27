library(showtext)
showtext.auto(enable = TRUE)
font.add('Consolas', 'consola.ttf')
pdf('test.pdf')
t<-seq(-3.14,3.14,0.5)
plot(t,sin(t), xlab = '', ylab = '',type='b',col='blue', 
     main = '', family = 'Consolas')
dev.off()
system('cmd /c start test.pdf')