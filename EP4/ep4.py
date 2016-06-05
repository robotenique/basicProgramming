import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np
import random as r 
def main():
#-->Entrada dos dados<--
	#Linhas
	n = 20
	#Colunas
	m = 20
	#Iterações
	t = 7
	#Nome do arquivo
	arquivo = "arquivo.txt"
	
	tipo, listaVivas = leEntrada(arquivo)	
	listaVivas = set(listaVivas)
	if tipo==0:
		#Regra padrão Quad : b="3" e s="23" (N3S23)
		nova = simulaQuadGenerica(n,m,listaVivas,t,"3","23")
		print("Há repetições = ",haRepeticoes(n,m,listaVivas,t))
		desenhaQuad(n,m,nova,"fig1.png")
	elif tipo==1:
		#Regra padrão Hex : b="35" e s="2" (N35S2)
		nova = simulaHexGenerica(n,m,listaVivas,t,"35","2")		
		desenhaHex(n,m,nova,"fig2.png")
		
def geraMatriz(n,m,listaVivas):	
	dim = (n,m)
	matriz = np.zeros(dim)
	vivas = list(listaVivas)
	for cel in vivas:
		matriz[cel[0]][cel[1]] = 1
	return matriz

def simulaQuadGenerica(n,m,lista,t,b,s):
	vB , vS = [int(val) for val in b],[int(val) for val in s]
	listOriginal = list(lista)
	for t in range(t):
		matriz = geraMatriz(n,m,listOriginal)
		listaViva = []
		for cel in listOriginal:
			VizinhosMortas = []
			#I - Células Sobreviventes		
			soma1 = calculaVizinhosQ(cel,matriz,n,m)			
			if any([soma1==s for s in vS]):
				listaViva.append(cel)
			#Células que vão nascer
			for cord in calculaVizinhosQ(cel,matriz,n,m,cord = True):
				if matriz[cord[0]][cord[1]]!=1:	
					VizinhosMortas.append([cord,calculaVizinhosQ(cord,matriz,n,m)])
			listaViva.extend([novaCel[0] for novaCel in VizinhosMortas if any(novaCel[1]==b for b in vB)])	
		listOriginal = list(set(listaViva))	#Remove elementos duplicados
	return listOriginal

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
	return sum([matriz[item[0]][item[1]] for item in vizinhosComuns])

def desenhaQuad(n,m,lista,figura):
	dim = (n,m)
	mImprime = np.zeros(dim)	
	for cel in lista:
		mImprime[cel[0]][cel[1]] = r.randint(10,100)	
	mImprime = np.flipud(mImprime)
	#Matplotlib
	fig = plt.figure(figsize=(4,3))
	ax = fig.add_subplot(111)	
	ax.matshow(mImprime, vmin=0, vmax=100, cmap="gist_ncar_r")	
	ax.set_yticks(np.arange(0.5,m+(0.5)))
	ax.set_xticks(np.arange(0.5,n+(0.5)))	
	ax.set_xticklabels([])
	ax.set_yticklabels([])
	ax.grid()	
	fig.tight_layout()
	fig.savefig(figura, dpi = 300)	

def simulaHexGenerica(n,m,lista,t,b,s):
	vB , vS = [int(val) for val in b],[int(val) for val in s]
	listOriginal = list(lista)
	for t in range(t):
		matriz = geraMatriz(n,m,listOriginal)
		listaViva = []
		for cel in listOriginal:
			VizinhosMortas = []	
			#Células Sobreviventes
			soma1 = calculaVizinhosH(cel,matriz,n,m)			
			if any([soma1==s for s in vS]):
				listaViva.append(cel)
			#Células que vão nascer					
			for cord in calculaVizinhosH(cel,matriz,n,m,cord=True):			
				if matriz[cord[0]][cord[1]]!=1:					
					VizinhosMortas.append([cord,calculaVizinhosH(cord,matriz,n,m)])
			listaViva.extend([novaCel[0] for novaCel in VizinhosMortas if any(novaCel[1]==b for b in vB)])			
		listOriginal = list(set(listaViva)) #Remove elementos duplicados
	return listOriginal		    		

def calculaVizinhosH(cel,matriz,n,m,cord=False):
	'''
	1. Calcular as coordenadas:
		I) Verifica se o número de colunas é ímpar
		II) Se for ímpar, adiciono uma coluna a mais (a tal da ponte invisível)
		III) Faço os calculos das coordenadas dos vizinhos da célula. Para a grid hexagonal,
			esse cálculo é diferente se a célula em questão é par ou ímpar.
		IV) Se o número de colunas é ímpar, ele remove os 'vizinhos' que estão na 'coluna invisivel'

	'''
	isOdd = (m%2!=0)
	m += isOdd
	x,y = cel[0],cel[1]
	if (y+1)%2==0:
		vizinhos = [((x+1)%n,y),(x,(y+1)%m),((x-1)%n,(y+1)%m),((x-1)%n,y),((x-1)%n,(y-1)%m),(x,(y-1)%m)]	
	else:
		vizinhos = [((x+1)%n,(y+1)%m),((x+1)%n,y),((x+1)%n,(y-1)%m),(x,(y-1)%m),((x-1)%n,y),(x,(y+1)%m)]
	if isOdd:
		for cel in list(vizinhos):			
			if cel[1]==(m-1):
				vizinhos.remove(cel)
	if cord:
		return vizinhos
	return sum([matriz[item[0]][item[1]] for item in vizinhos])

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

	#Cores
	nColor = np.random.rand(3,1)
	cor = [[0.9, 0.85 ,0.9] for x in range(n*m)]
	auxC = np.arange(0,n*m,m)	
	vizinhos = []
	matriz = geraMatriz(n,m,lista)
	for x,y in lista:
		cor[auxC[x]+y] = [0.3, 0.9 ,0.3]

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

def haRepeticoes(n,m,lista,t):
	listOriginal = [list(lista)]
	for i in range(t):
		listOriginal.append(simulaQuadGenerica(n,m,listOriginal[i],1,"3","23"))
	for padrao in listOriginal:
		nLista = list(listOriginal)	
		nLista.remove(padrao)	
		if any((set(padrao) == set(confCel) for confCel in nLista)):
			return True
	return False

	'''
	for padrao in listOriginal:
		if any((padrao == confCel for confCel in listOriginal)):
			return True
	return False
	'''
def leEntrada(nome):
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = tuple([int(t) for t in content[x].split(",")])		
	return 0 if content[0]=="Q" else 1 , content[1:]
	
	
if __name__ == '__main__':
	main()