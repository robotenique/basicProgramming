import matplotlib.pyplot as plt
import numpy as np
import random as r 
def main():
	n = m = 25
	n = 17
	t = 9
	tipo, listaVivas = leEntrada("arquivo.txt")
	
	nova = simulaQuad(n,m,listaVivas,t)	

	matriz = geraMatriz2(n,m,nova)
	
	for x in range(n):
		for j in range(m):
			print(matriz[x][j],end="")
			print(" | ",end="")
		print("\n")

	desenhaQuad(n,m,nova,"nome")

def geraMatriz(n,m,listaVivas):	
	dim = (n,m)
	matriz = np.zeros(dim)
	vivas = list(listaVivas)
	for cel in vivas:
		matriz[cel[0]][cel[1]] = 1
	return matriz

def geraMatriz2(n,m,listaVivas):	
	dim = (n,m)
	matriz = []
	for i in range(n):
		matriz.append([])
		for j in range(m):
			matriz[i]+=[" "]
	vivas = list(listaVivas)
	for cel in vivas:
		matriz[cel[0]][cel[1]] = "X"
	return matriz


	#print(p)
	#print(q)
	
def calculaVizinhos(cel,matriz,n,m,cord = False):
	x,y = cel[0],cel[1]
	vizinhosComuns =[
			((x+1)%n,(y-1)%m),
			((x+1)%n,y),
			((x+1)%n,(y+1)%m),	 			
			((x-1)%n,(y+1)%m),	 			
			((x-1)%n,(y-1)%m),
			((x-1)%n,y),
			(x,(y+1)%m),
			(x,(y-1)%m)
]
	if cord:
		return vizinhosComuns		
	else:
		return sum([matriz[item[0]][item[1]] for item in vizinhosComuns])


def simulaQuad(n,m,lista,t):
	listOriginal = list(lista)	
	for t in range(t):
		matriz = geraMatriz(n,m,listOriginal)		
		listaViva = []
		for cel in listOriginal:
			#I - Células Sobreviventes		
			soma1 = calculaVizinhos(cel,matriz,n,m)			
			if any([soma1==2,soma1==3]):
				listaViva.append(cel)
			VizinhosMortas = [[cord,calculaVizinhos(cord,matriz,n,m)] for cord in calculaVizinhos(cel,matriz,n,m,cord = True)]
			listaViva.extend([morta[0] for morta in VizinhosMortas if morta[1]==3])			
		listOriginal = list(set(listaViva))		
	return listOriginal	
 		

def desenhaQuad(n,m,lista,figura):
	dim = (n,m)
	mImprime = np.zeros(dim)	
	for cel in lista:
		mImprime[cel[0]][cel[1]] = r.randint(50,100)	
	matriz = np.flipud(mImprime)

	plt.matshow(matriz , vmin=0, vmax=100, cmap="PuRd")
	plt.show()

def leEntrada(nome):
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = tuple([int(t) for t in content[x].split(",")])		
	return 0 if content[0]=="Q" else 1,content[1:]
	
	
if __name__ == '__main__':
	main()