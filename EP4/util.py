import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np

# set up figure
fig, ax = plt.subplots(1)

# positions
pixel_x, pixel_y = np.indices((2, 2))

pixel_color = np.random.random_sample(12).reshape(4, 3)
print(len(pixel_color))
dx = 5    # horizontal stride
dy = 5    # vertical stride 

# set static radius
poly_radius = 2.5
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
for c, x, y in zip(pixel_color, pixel_x.flat, pixel_y.flat):    
	if controle%3==0:
		dx = 5
		dy = 5
	else:
		dx = 10
		dy = 2.5
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
	


pc = PatchCollection(patch_list, match_original=True)
ax.add_collection(pc)

ax.axis([-3, 80, -3, 80])
plt.show()
