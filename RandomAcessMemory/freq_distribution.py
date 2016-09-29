"""
Demo of spines using custom bounds to limit the extent of the spine.
"""
import numpy as np
import matplotlib.pyplot as plt



fRelMatrix = [[] for y in range(6)]
lim = int(input("Digite N: "))
x_axis = [x for x in range(1, lim+1)]
uniform_list = np.random.randint(1, size=lim, high=7)
cor = [[1, 0, 0.85], [0.4, 0, 0.8520772], [0, 0, 1], [0.2, 1, 1], [0.2, 1, 0], [0.9, 0.973553065884, 0.09], [1, 0.407421725309, 0], [1, 0, 0]]
data_freq = np.array([0, 0, 0, 0, 0, 0])
i = 0

for num in uniform_list:
    i += 1
    data_freq[num-1] += 1
    for j in range(6):
        fRelMatrix[j].append(data_freq[j]/i)

for j in range(6):
    plt.plot(x_axis, fRelMatrix[j], color=cor[j])
    #plt.scatter(x_axis, fRelMatrix[j], marker='x', c=cor[j], zorder=10)
plt.show()
