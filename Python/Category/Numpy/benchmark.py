# 20000*20000 163
# 30000*30000 746 14.1G with 23G Virtual MemoryError
# 40000*40000 MemoryError!!!
from numpy import dot, float32, dtype
from numpy.random import rand
from time import clock
st = clock()
f = dot(rand(5000, 5000).astype(float32), rand(5000, 5000).astype(float32))
et = clock()
print(et-st)

# import torch
# import numpy as np
# x = np.random.rand(5000,5000)
# y = np.random.rand(5000,5000)
# x = torch.from_numpy(x)
# y = torch.from_numpy(y)
# from time import clock
# st=clock()
# xx = x.cuda()
# yy = y.cuda()
# for _ in range(500):
# zz=xx.mm(yy)
# zz=yy.mm(xx)
# et=clock()
# print(et-st)
