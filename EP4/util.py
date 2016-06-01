"""Simple matshow() example."""
import matplotlib.pyplot as plt
import numpy as np
import random as r 

def samplemat(dims):
	#dim = (n,m)
    
    aa = np.zeros(dims)   
    for x in np.nditer(aa,op_flags=['readwrite']):
    	x[...] = r.randint(0,1)
    print(aa[7][3])
    return aa

print(samplemat((5,10)))
#plt.matshow(samplemat((100,1000)))

plt.show()