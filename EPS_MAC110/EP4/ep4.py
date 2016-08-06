#.n Juliano Garcia de Oliveira
#.u 9277086
import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon
from matplotlib.collections import PatchCollection
import numpy as np
import random as r

def main():
	'''
	-Função main() do programa

	Variáveis:
		n - num. linhas da matriz (>0)
		m - colunas da matriz (>0)
		t - número de iterações (>=0) (se ==0, imprime a conf. Original)
		arquivo - nome do arquivo para ser lido.		
	'''

	#Dados Iniciais	
	n = 9
	m = 8
	t = 0
	arquivo = "arquivo2.txt"
	
	#Lê arquivo inicial
	tipo, listaVivas = leEntrada(arquivo)	
	listaVivas = set(listaVivas) #Remove possíveis coordenadas duplicadas

	#Executa o programa de acordo com o tipo (quadrada ou hexagonal)
	if tipo==0:
		#Regra padrão Quad : b="3" e s="23" (N3S23)
		nova = simulaQuadGenerica(n,m,listaVivas,t,"3","23")
		print("Há repetições = ",haRepeticoes(n,m,listaVivas,t))
		desenhaQuad(n,m,nova,"fig1")
	elif tipo==1:
		#Regra padrão Hex : b="35" e s="2" (N35S2)
		nova = simulaHexGenerica(n,m,listaVivas,t,"35","2")		
		desenhaHex(n,m,nova,"fig2")
		
def geraMatriz(n,m,listaVivas):	
	'''
	- Função que gera a matriz de 0's e 1's de dimensão (n x m).
	  Células vivas tem valor 1 e mortas valor 0.	  
	'''
	dim = (n,m)
	matriz = np.zeros(dim)
	vivas = list(listaVivas)
	for cel in vivas:
		matriz[cel[0]][cel[1]] = 1
	return matriz

def simulaQuadGenerica(n,m,lista,t,b,s):
	'''
	-Função para simular o jogo da vida quadrado em 't' iterações;
	
	Algoritmo:	  
	-->Por 't' vezes:

	    I) Para cada célula viva, calcula a soma dos vizinhos dela na matriz;
		II) Se a soma é igual a algum termo de 's', então a célula sobrevive;
		III) Para cada célula viva, calcula as coordenadas dos vizinhos dela;
			-->Para cada um desses vizinhos, calcula a soma dos vizinhos destes na matriz;
			-->Se a soma dos vizinhos é igual a algum termo de 'b' (e ela está morta),
			   então ela nasce;
		IV) A lista inicial de células é substituída com a nova lista gerada;
		V) Volta para o início do loop com a lista nova de células vivas;

	-->Retorna a lista final após 't' iterações.
	'''
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
		listOriginal = list(set(listaViva))	#Remove possíveis coordenadas duplicadas
	return listOriginal

def calculaVizinhosQ(cel,matriz,n,m,cord = False):
	'''
	-Função que calcula as coordenadas / soma dos vizinhos da célula 'cel',
	 na grade Quadrada;

	* cord = False por padrão, retorna a soma dos vizinhos;
		    Se True, retorna as coordenadas dos vizinhos;
	'''
	x,y = cel[0],cel[1]
	#Usando '%' p/ também calcular vizinhos extremos na matriz
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
	'''
	 Função que salva o grafico do jogo em uma grade quadrada.

	 I) Gera a matriz 'mImprime', igual a função geraMatriz(), porém as células
		vivas recebem valores aleatórios entre 10 e 100.
	II) Inverte as linhas da matriz, para ficar igual ao modelo na especificação
		 do EP4 ( (0,0) é a coluna inferior esquerda, não superior )
   III) Cria a figura usando o matplotlib, com configurações de exibição específicas.
		 A função usada é a matshow(), que recebe a 'mImprime' como argumento.
		 Uso o colorMap "gist_ncar_r", e então cada célula viva recebe uma cor aleatória,
		  de acordo com o valor aleatório gerado no item I).
	IV) Salva a figura com o nome especificado pela variável 'figura'.

	'''
	dim = (n,m)
	mImprime = np.zeros(dim)

	for cel in lista:
		mImprime[cel[0]][cel[1]] = r.randint(10,100) #Cores aleatórias, why not?	
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
	fig.savefig(figura+".png", dpi = 300)	

def simulaHexGenerica(n,m,lista,t,b,s):
	'''
	-Função para simular o jogo da vida hexagonal em 't' iterações;
	
	Algoritmo:	  
	-->Por 't' vezes:

	    I) Para cada célula viva, calcula a soma dos vizinhos dela na matriz;
		II) Se a soma é igual a algum termo de 's', então a célula sobrevive;
		III) Para cada célula viva, calcula as coordenadas dos vizinhos dela;
			-->Para cada um desses vizinhos, calcula a soma dos vizinhos destes na matriz;
			-->Se a soma dos vizinhos é igual a algum termo de 'b' (e ela está morta),
			   então ela nasce;
		IV) A lista inicial de células é substituída com a nova lista gerada;
		V) Volta para o início do loop com a lista nova de células vivas;

	-->Retorna a lista final após 't' iterações.
	'''
	vB , vS = [int(val) for val in b],[int(val) for val in s]
	listOriginal = list(lista)
	#Mais uma coluna se é ímpar!
	m += (m%2!=0)
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
	-Função que calcula as coordenadas / soma dos vizinhos da célula 'cel',
	 na grade HEXAGONAL;
	
	1. Calcular as coordenadas:
		I) Verifica se o número de colunas é ímpar
		II) Se for ímpar, adiciona uma coluna a mais (a tal da ponte invisível)
		III) Faz os calculos das coordenadas dos vizinhos da célula. Para a grid hexagonal,
			esse cálculo é diferente se a célula em questão é par ou ímpar		
	2. Retorna a soma dos vizinhos de uma determinada célula.

	'''	
	x,y = cel[0],cel[1]
	if (y+1)%2==0:
		vizinhos = [((x+1)%n,y),(x,(y+1)%m),((x-1)%n,(y+1)%m),((x-1)%n,y),((x-1)%n,(y-1)%m),(x,(y-1)%m)]	
	else:
		vizinhos = [((x+1)%n,(y+1)%m),((x+1)%n,y),((x+1)%n,(y-1)%m),(x,(y-1)%m),((x-1)%n,y),(x,(y+1)%m)]	
	if cord:		
		return vizinhos
	return sum([matriz[item[0]][item[1]] for item in vizinhos])

def desenhaHex(n,m,lista,figura):
	'''
	-Função que gera uma grid hexagonal (n x m), e salva uma figura com 
	 os valores passados através da 'lista'.
	'''
	
	#Variáveis Iniciais p/ Hexágono
	'''
	Variáveis Iniciais:
	  patch_list - Lista que irá conter todos os Hexágonos da grid
	  hexagonRatio - O "raio" do hexágono. Valor padrão é 5
	  indL , indC - indíces da Linha e da Coluna, respectivamente
	  apothem - apótema do hexágono
	  dx - valor para variar a coordenada x do centro de cada hexágono
	  points_Y - Valores das coordenadas Y
	  points_X - Valores das coordenadas X
	'''	
	#Se for ímpar, remove todas as células vivas da coluna invisível!	
	if m%2!=0:
		for x,y in list(lista):
			if y==m:
				lista.remove((x,y))
	patch_list = []
	hexagonRatio = 5
	indL,indC = 0 , 0	
	apothem = np.sin(np.pi/3)*hexagonRatio
	dx = 1.5 * hexagonRatio
	#Matriz p/ grade hexagonal n x m
	points_Y,points_X = (np.indices((n,m))+1)

	#Cores	
	cor = [[0.9, 0.85 ,0.9] for x in range(n*m)]
	auxC = np.arange(0,n*m,m)	
	matriz = geraMatriz(n,m,lista)
	#As células vivas recebem a cor RANDOM!
	for x,y in lista:
		cor[auxC[x]+y] = np.random.rand(3,1) #[0.3, 0.9 ,0.3]

	#Criação da lista de Patches com Hexágonos
	for c, x, y in zip(cor, points_X.flat, points_Y.flat):
		#Coordenada coluna Ímpar
		cordI = (x*dx,apothem * (2*indL+1))
		#Coordenada coluna Par
		cordP = (cordI[0],cordI[1]+apothem)	
		#Tupla com ambas as coordenadas	
		tcoordenadas = (cordP,cordI)	
		'''
		-->Se tenho colunas pares, a ordem estabelecida é a normal.
		-->Se tenho colunas ímpares, Preciso trocar a ordem a cada linha ,
			(ou seja, quando a linha for par a ordem é trocada, e se for ímpar
			 a ordem é mantida)
		'''
		if m%2==0:
			cord =  tcoordenadas[0] if indC%2==0 else tcoordenadas[1]
		else:
			ehPar = (indL%2==0)
			cord = tcoordenadas[not(ehPar)] if indC%2==0 else tcoordenadas[ehPar]	
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
	pc = PatchCollection(patch_list, match_original=True) #Manter as cores originais
	ax.add_collection(pc)
	ax.set_xlim(0,cordI[0]+dx)
	ax.set_ylim(-hexagonRatio,cordI[1]+3*apothem)
	ax.set_aspect('equal')
	ax.set_xticks(())
	ax.set_yticks(())
	fig.tight_layout()
	fig.savefig(figura+".png", dpi = 300)

def haRepeticoes(n,m,lista,t):
	'''
	Função que verifica se houve repetição de algum padrão em alguma
	  das 't' simulações do jogo da vida na grade quadrada, incluindo o
	  padrão inicial.

	I) Cria uma lista com todas as listas de células vivas a cada iteração
   II) Verifica se algum padrão se repetiu. Caso sim, retorna True.
  III) Se nenhum padrão foi observado, retorna False.
	'''
	listOriginal = [list(lista)]
	for i in range(t):
		listOriginal.append(simulaQuadGenerica(n,m,listOriginal[i],1,"3","23"))
	for padrao in listOriginal:
		nLista = list(listOriginal)	
		nLista.remove(padrao)	
		if any((set(padrao) == set(confCel) for confCel in nLista)):
			return True
	return False

def leEntrada(nome):
	'''
	Função que lê o arquvo de entrada e retorna o tipo e a lista de células vivas.	
	'''
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = tuple([int(t) for t in content[x].split(",")])		
	return 0 if content[0]=="Q" else 1 , content[1:]
	
	
if __name__ == '__main__':
	main()