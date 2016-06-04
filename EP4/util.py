import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np
import random as r



# Variaveis iniciais
n = 5
m = 10
patch_list = []
hexagonRatio = 5
indL = 0
indC = 0
apothem = np.sin(np.pi/3)*hexagonRatio
dx = 1.5 * hexagonRatio


points_Y,points_X = (np.indices((n,m))+1)

cor = [np.random.rand(3,1) if x%2==0 else [0, 1 ,0.3] for x in range(1100)]




for c, x, y in zip(cor, points_X.flat, points_Y.flat):	
	cordI = (x*dx,apothem * (2*indL+1))
	cordP = (cordI[0],cordI[1]+apothem)	
	tCordenadas = (cordP,cordI)	
	if m%2==0:
		cord =  tCordenadas[0] if indC%2==0 else tCordenadas[1]
	else:
		ehPar = (indL%2==0)
		cord = tCordenadas[not(ehPar)] if indC%2==0 else tCordenadas[ehPar]	
	
	indC+=1
	indL+=(indC%m == 0)
	
	#Cria um Hexágono com as características escolhidas
	patch_list.append(
			RegularPolygon(
				xy=cord,
				numVertices=6,
				radius=hexagonRatio,
				orientation=np.pi/2,
				facecolor=c,
				edgecolor = [0,0,0]			
			)
		)


#Coordenadas do primeiro e último hexágono da grid


# set up figure
fig, ax = plt.subplots(1)
fig = plt.figure(figsize=(4,3))
ax = fig.add_subplot(111)
pc = PatchCollection(patch_list, match_original=True)
ax.add_collection(pc)
ax.set_xlim(0,cordI[0]+dx)
ax.set_ylim(-hexagonRatio,cordI[1]+3*apothem)
ax.set_aspect('equal')
ax.set_xticks(())
ax.set_yticks(())
plt.show()
