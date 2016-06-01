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
		d[x][j] = r.randint(0,1)
print(d)
print(vizinhosComuns)
vetor = sum([d[item[0]][item[1]] for item in vizinhosComuns])
print(vetor)



