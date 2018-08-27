import numpy as np
import matplotlib.pyplot as pl
x = np.linspace(0,2*np.pi,100)
y = np.sin(x)
line = pl.plot(x,y,'d')
pl.setp(line,mew = 0.5,mec ='blue',markersize = 8,mfc = 'pink')
pl.show()
