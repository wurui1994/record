## the R code ##

library(diagram)

pos <- coordinates(pos=c(3,3,3,3,3,3))

cc <- c("Start",LETTERS[2:16],"End")

openplotmat(main="Flow Chart")

for(i in seq(1,15,by = 3)) straightarrow(from = pos[i,] ,to = pos[i+3,])

for(i in c(2,5,8)) straightarrow(from = pos[i,] ,to = pos[i+6,])

segmentarrow(from = pos[16,],to=pos[2,],path="RVL",dd=0.15)

bentarrow(from = pos[8,], to=pos[6,],path='H')

bentarrow(from = pos[6,], to=pos[2,],path='V')

straightarrow(from=pos[14,],to = pos[17,])

for(i in c(2,7,13,14,16)) textrect(pos[i,],radx=0.08,rady=0.04,lab = cc[i])

for(i in c(1,17)) textround(pos[i,],radx=0.08,rady=0.04,lab = cc[i])

textdiamond(mid = pos[8,],radx = 0.15,rady = 0.08,lab = c("Has","Detect?"))

textmulti(mid = pos[4,],radx=0.1,rady=0.05,nr=6)

textmulti(mid = pos[6,],radx=0.1,rady=0.05,nr=5)

textellipse(mid = pos[10,],radx = 0.1,rady = 0.05)

text(pos[8,1]+0.2,pos[8,2]+0.03,"YES",cex = 0.8)

text(pos[11,1]+0.04,pos[11,2],"NO",cex = 0.8)