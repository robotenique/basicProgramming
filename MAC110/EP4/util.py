import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np
import random as r
'''
l55 =[(2,4),(2,3)]
l1 = [(2,3),(2,4),(6,7),(3,4),(5,5),(7,7)]
l2 = [(2,3),(2,4),(6,7),(5,5),(7,7)]
l3 = [(2,4),(3,4),(5,5),(7,7)]
l4 = [(2,4),(3,4),(5,5)]
l5 = [(2,3),(2,4)]
listOriginal = [l55,l1,l2,l3,l4,l5]
for padrao in listOriginal:
	nLista = list(listOriginal)	
	nLista.remove(padrao)	
	if any((set(padrao) == set(confCel) for confCel in nLista)):
		print("TRUE")
'''
	



#Gerador de Células Vivas Aleatórias (20 por vez. copiar do terminal p/ arquivox.txt)

n = 9
m = 8



s = [(np.random.randint(0,n-1),np.random.randint(0,m-1)) for t in range(23)]
s = set(s)
for t in s:
	t =  str(t).replace(" ","")
	print(t.strip("() "),sep="")


'''
for x,y in lista:		
	vizinhos.extend(calculaVizinhosH((x,y),matriz,n,m,cord=True))

for x,y in vizinhos:		
	cor[auxC[x]+y] = nColor	
'''