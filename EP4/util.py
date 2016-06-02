import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np

# set up figure
fig, ax = plt.subplots(1)

# positions
pixel_x, pixel_y = np.indices((4, 4))
pixel_x = np.array([0,1,2,3,4,5,0,1,2,3,4,5])
pixel_y = np.array([0,0,0,0,0,0,1,1,1,1,1,1])


pixel_color = np.array([[ 0.04502529 , 0.26985885 , 0.45650749] for t in range(11)])


# set static radius
raio = 7
#numLinha
linhas = 2
colunas = 6
poly_radius = raio

dx = 2*poly_radius    # horizontal stride
dy = 2*raio   # vertical stride 


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
ind = 0
for c, x, y in zip(pixel_color, pixel_x.flat, pixel_y.flat):    	
	if(ind%2==-0):
		dx = 0

	patch_list.append(
			RegularPolygon(
				xy=(x*dx, y*dy),
				numVertices=6,
				radius=poly_radius,
				orientation=0.,
				facecolor=c,
				edgecolor='k'  
			)
		)
	controle+=1
	


pc = PatchCollection(patch_list, match_original=True)
ax.add_collection(pc)
ax.grid()
ax.axis([-3, 100, -3, 100])
plt.show()
