"""Simple matshow() example."""
import matplotlib.pyplot as plt
import numpy as np
import random as r 

n = 10
x = 0
y = 0
m = 10

vizinhosComuns =[
			[(x+1)%n,(y-1)%m],
			[(x+1)%n,y],
			[(x+1)%n,(y+1)%m],	 			
			[(x-1)%n,(y+1)%m],	 			
			[(x-1)%n,(y-1)%m],
			[(x-1)%n,y],
			[x,(y+1)%m],
			[x,(y-1)%m]
]
d = np.zeros((10,10))
for x in range(10):
	for j in range(10):
		d[x][j] = str(x)+str(j)
print(np.flipud(d))
vetor = sum([d[item[0]][item[1]] for item in vizinhosComuns])
print(vetor)
'''
[[ 90.  91.  92.  93.  94.  95.  96.  97.  98.  99.]
 [ 80.  81.  82.  83.  84.  85.  86.  87.  88.  89.]
 [ 70.  71.  72.  73.  74.  75.  76.  77.  78.  79.]
 [ 60.  61.  62.  63.  64.  65.  66.  67.  68.  69.]
 [ 50.  51.  52.  53.  54.  55.  56.  57.  58.  59.]
 [ 40.  41.  42.  43.  44.  45.  46.  47.  48.  49.]
 [ 30.  31.  32.  33.  34.  35.  36.  37.  38.  39.]
 [ 20.  21.  22.  23.  24.  25.  26.  27.  28.  29.]
 [ 10.  11.  12.  13.  14.  15.  16.  17.  18.  19.]
 [  0.   1.   2.   3.   4.   5.   6.   7.   8.   9.]]
'''