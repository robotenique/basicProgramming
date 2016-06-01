import matplotlib.pyplot as plt
import numpy as np
import random as r 
def main():
	tipo, listaVivas = leEntrada("arquivo.txt")	
	nova = simulaQuad(10,10,listaVivas,1)	
	
	print(listaVivas)
	print(type(listaVivas))
	n = m = 10
	print(nova)

	print(geraMatriz(m,n,listaVivas))
	desenhaQuad(n,m,listaVivas,0)

def geraMatriz(n,m,listaVivas):	
	dim = (n,m)
	matriz = np.zeros(dim)
	vivas = list(listaVivas)
	for cel in vivas:
		matriz[cel[0]][cel[1]] = 1
		#valorVizinhos = sum([matriz[item[0]][item[1]] for item in vizinhosComuns])
	matriz = np.flipud(matriz)
	return matriz



	#print(p)
	#print(q)
	
def leEntrada(nome):
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = [int(t) for t in content[x].split(",")]
	return 0 if content[0]=="Q" else 1,content[1:]

def simulaQuad(n,m,lista,t):
	listOriginal = list(lista)
	listaViva = []
	for cel in lista:
		x,y  = cel[0],cel[1] 
		controle = 0 			 				
		vizinhosComuns =[
			[(x+1)%n,(y-1)%m],
			[(x+1)%n,y],
			[(x+1)%n,(y+1)%m],	 			
			[(x-1)%n,(y+1)%m],	 			
			[(x-1)%n,(y-1)%m],
			[(x-1)%n,y],
			[x,(y+1)%m],
			[x,(y-1)%m]
]
		for vizinho in vizinhosComuns:
			print("vizinho = ",vizinho)
			if any((vizinho==celViva for celViva in listOriginal)):
				listOriginal.remove(vizinho)
				controle+=1
				if controle>3:
					break 			
		if controle==2 or controle==3: 			
			print("APPENDANDO",cel)
			listaViva.append(cel)
	return listaViva	
 		

def desenhaQuad(n,m,lista,figura):	
	plt.matshow(geraMatriz(n,m,lista), vmin=0, vmax=1, cmap="PuRd")	
	plt.show()


	
	
if __name__ == '__main__':
	main()