import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np
import random as r

# set up figure
fig, ax = plt.subplots(1)

# positions
pixel_x, pixel_y = np.indices((4, 4))
pixel_x = np.array([1,2,3,4,5,6,1,2,3,4,5,6])
pixel_y = np.array([1,1,1,1,1,1,2,2,2,2,2,2])


pixel_color = cor = [[0.862745, 0.0784314, 0.235294] if x%2==0 else [0.541176, 0.168627 ,0.886275] for x in range(13)]
#,[1,0.407421725309,0],[1,0,0],[ 1, 0, 0.85],[ 0.4,0,0.8520772],[0,0,1],[0.2,1,1]

# set static radius
raio = 5
#numLinha
linhas = 2
colunas = 6
poly_radius = raio


'''
		dx = 5
		dy = 5
	else:
		dx = 10
		dy = 2.5
'''
# list to hold patches
patch_list = []

# creat the patches
controle = 0
indL = 1
indC = 0
for c, x, y in zip(pixel_color, pixel_x.flat, pixel_y.flat):	
	#Se a coluna é par
	apotema = np.sin(np.pi/3)*poly_radius
	if (indC%linhas)%2==0: 
		dx = 1.5*poly_radius
		dy = apotema
	#Se a coluna é ímpar
	else:		
		dx = 1.5*poly_radius
		dy = 0
	if(indL==2):
		dy = 0
		if(indC%linhas)%2!=0:
			y = 1 + 2*apotema #1 + 2* apotema
		else:
			#CONSERTAR AQUI
			y = 1 + 3*apotema

	cord = (x*dx, y+dy)

	patch_list.append(
			RegularPolygon(
				xy=cord,
				numVertices=6,
				radius=poly_radius,
				orientation=np.pi/2,
				facecolor=c				
			)
		)

	indC+=1
	if indC == colunas:
		indL+=1
	print(indC)
	

	
	


pc = PatchCollection(patch_list, match_original=True)
ax.add_collection(pc)
ax.grid()
ax.axis([-3, 50, -3, 50])
ax.set_aspect('equal')
plt.show()
