import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np
import random as r 
def main():
	#Entrada dos dados
	m = 28
	n = 17
	t = 11
	arquivo = "arquivo2.txt"

	
	#Gerador de Células Vivas Aleatórias (20 por vez. copiar do terminal p/ arquivo)
	s = [(np.random.randint(0,n-1),np.random.randint(0,m-1)) for t in range(50)]
	for t in s:
		t =  str(t).replace(" ","")
		print(t.strip("() "),sep="")
	
	tipo, listaVivas = leEntrada(arquivo)	
	
	if tipo==0:
		nova = simulaQuad(n,m,listaVivas,t)
		desenhaQuad(n,m,nova,"fig1.png")
	else:
		desenhaHex(n,m,listaVivas,"fig2.png")
		
def geraMatrizQ(n,m,listaVivas):	
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
		matriz = geraMatrizQ(n,m,listOriginal)		
		listaViva = []
		for cel in listOriginal:
			#I - Células Sobreviventes		
			soma1 = calculaVizinhosQ(cel,matriz,n,m)			
			if any([soma1==2,soma1==3]):
				listaViva.append(cel)
			VizinhosMortas = [[cord,calculaVizinhosQ(cord,matriz,n,m)] for cord in calculaVizinhosQ(cel,matriz,n,m,cord = True)]
			listaViva.extend([morta[0] for morta in VizinhosMortas if morta[1]==3])			
		listOriginal = list(set(listaViva))	#Remove entradas duplicadas	
	return listOriginal	
 		

def desenhaQuad(n,m,lista,figura):
	dim = (n,m)
	mImprime = np.zeros(dim)	
	for cel in lista:
		mImprime[cel[0]][cel[1]] = r.randint(10,100)	
	mImprime = np.flipud(mImprime)
	#Matplotlib
	fig = plt.figure(figsize=(4,3))
	ax = fig.add_subplot(111)	
	ax.matshow(mImprime, vmin=-5, vmax=100, cmap="gist_ncar_r")	
	ax.set_yticks(np.arange(0.5,m+(0.5)))
	ax.set_xticks(np.arange(0.5,n+(0.5)))	
	ax.set_xticklabels([])
	ax.set_yticklabels([])
	ax.grid()	
	fig.tight_layout()
	fig.savefig(figura, dpi = 300)	

def desenhaHex(n,m,lista,figura):
	
	#Variáveis Iniciais p/ Hexágono
	vizinhos = []
	patch_list = []
	hexagonRatio = 5
	indL,indC = 0 , 0	
	apothem = np.sin(np.pi/3)*hexagonRatio
	dx = 1.5 * hexagonRatio
	#Matriz p/ grade hexagonal n x m
	points_Y,points_X = (np.indices((n,m))+1)
	
	#Vizinhos TODO: OTIMIZAR AQUI!!
	for x,y in lista:
		if (y+1)%2==0:
			vizinhos.extend([[x+1,y],[x,y+1],[x-1,y+1],[x-1,y],[x-1,y-1],[x,y-1]])
		else:
			vizinhos.extend([[x+1,y+1],[x+1,y],[x+1,y-1],[x,y-1],[x-1,y],[x,y+1]])

	#Cores
	cor = [[1, 1 ,1] for x in range(n*m)]
	auxC = np.arange(0,n*m,m)	
	for x,y in lista:		
		cor[auxC[x]+y] = np.random.rand(3,1)
	for x,y in vizinhos:		
		cor[auxC[x]+y] = [0.5,0.5,1]		
	
	#Criação da lista de Patches com Hexágonos
	for c, x, y in zip(cor, points_X.flat, points_Y.flat):	
		#Coordenada coluna Ímpar
		cordI = (x*dx,apothem * (2*indL+1))
		#Coordenada coluna Par
		cordP = (cordI[0],cordI[1]+apothem)	
		#Tupla com ambas as coordenadas	
		tCordenadas = (cordP,cordI)	
		'''
		-->Se tenho colunas pares, a ordem estabelecida é a normal.
		-->Se tenho colunas ímpares, Preciso trocar a ordem a cada linha ,
			(ou seja, quando a linha for par a ordem é trocada, e se for ímpar
			 a ordem é mantida)
		'''
		if m%2==0:
			cord =  tCordenadas[0] if indC%2==0 else tCordenadas[1]
		else:
			ehPar = (indL%2==0)
			cord = tCordenadas[not(ehPar)] if indC%2==0 else tCordenadas[ehPar]	
		#Incrementa o Índice de colunas e o índice de linhas
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
	#Configurando e salvando a figura
	
	fig = plt.figure(figsize=(4,3))
	ax = fig.add_subplot(111)
	pc = PatchCollection(patch_list, match_original=True)
	ax.add_collection(pc)
	ax.set_xlim(0,cordI[0]+dx)
	ax.set_ylim(-hexagonRatio,cordI[1]+3*apothem)
	ax.set_aspect('equal')
	ax.set_xticks(())
	ax.set_yticks(())
	fig.tight_layout()
	fig.savefig(figura, dpi = 300)



def leEntrada(nome):
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = tuple([int(t) for t in content[x].split(",")])		
	return 0 if content[0]=="Q" else 1 , content[1:]
	
	
if __name__ == '__main__':
	main()