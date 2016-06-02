import matplotlib.pyplot as plt
import numpy as np
import random as r 
def main():
	n = m = 24
	n = 24
	t = 11
	arquivo = "arquivo.txt"
	tipo, listaVivas = leEntrada(arquivo)	
	if tipo=="Q":
		nova = simulaQuad(n,m,listaVivas,t)
		desenhaQuad(n,m,nova,"fig1.png")

def geraMatriz(n,m,listaVivas):	
	dim = (n,m)
	matriz = np.zeros(dim)
	vivas = list(listaVivas)
	for cel in vivas:
		matriz[cel[0]][cel[1]] = 1
	return matriz
	
def calculaVizinhosQ(cel,matriz,n,m,cord = False):
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
			soma1 = calculaVizinhosQ(cel,matriz,n,m)			
			if any([soma1==2,soma1==3]):
				listaViva.append(cel)
			VizinhosMortas = [[cord,calculaVizinhosQ(cord,matriz,n,m)] for cord in calculaVizinhosQ(cel,matriz,n,m,cord = True)]
			listaViva.extend([morta[0] for morta in VizinhosMortas if morta[1]==3])			
		listOriginal = list(set(listaViva))		
	return listOriginal	
 		

def desenhaQuad(n,m,lista,figura):
	dim = (n,m)
	mImprime = np.zeros(dim)	
	for cel in lista:
		mImprime[cel[0]][cel[1]] = r.randint(10,100)	
	mImprime = np.flipud(mImprime)
	fig = plt.figure(figsize=(4,3))
	ax = fig.add_subplot(111)	
	ax.matshow(mImprime, vmin=0, vmax=100, cmap="gist_ncar_r")
	ax.set_yticks(())
	ax.set_xticks(())
	fig.savefig(figura, dpi = 300)	
	

def leEntrada(nome):
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = tuple([int(t) for t in content[x].split(",")])		
	return 0 if content[0]=="Q" else 1,content[1:]
	
	
if __name__ == '__main__':
	main()