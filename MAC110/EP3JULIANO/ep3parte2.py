#!/usr/bin/env python
# -*- coding: utf-8 -*-
#.n Juliano Garcia de Oliveira
#.u 9277086
import random
import numpy as np
import math as mat
import matplotlib.pyplot as plt
from matplotlib import collections  as mc
import ep2julian as ep2
def main():
	#Cores 

	# Entrada de dados pelo usuário
	r = float(input("Digite o raio da circunferência: "))
	while r<=0:
		r = float(input("\nDigite o raio (deve ser maior que zero): "))
	n = int(input("\nDigite o n : "))
	while n<=0:
		n = int(input("\nDigite o n (deve ser maior que zero): "))
	#Cálculo das cordas
	cordasM1 = ep2.listaCordasM1(r,n)
	cordasM2 = ep2.listaCordasM2(r,n)
	cordasM3 = ep2.listaCordasM3(r,n)
	#Cálculo da distribuicaoBorda
	distribuicaoBorda(r,cordasM1)
	distribuicaoBorda(r,cordasM2)
	distribuicaoBorda(r,cordasM3)
	#Cálculo da distribuicaoRadial
	distribuicaoRadial(r,cordasM1)	
	distribuicaoRadial(r,cordasM2)	
	distribuicaoRadial(r,cordasM3)
	#Cálculo da distribuicaoArea
	distribuicaoArea(r,cordasM1)	
	distribuicaoArea(r,cordasM2)	
	distribuicaoArea(r,cordasM3)
	#Cálculo da distribuicaoCordas	
	distribuicaoCordas(r,cordasM3)
	distribuicaoCordas(r,cordasM2)
	distribuicaoCordas(r,cordasM1)
		
			
def exibeGrafico(r,xs,ys,cores,hist,nome,isBorda):	
	
	plt.figure(figsize=(28,15))
	
	############################SUBPLOT - CÍRCULO##############################
	plt.subplot(121,aspect='equal')
	plt.title("A circunferência",fontsize=40)
	#plt.axis([1,2.5*r,0,2.5*r],hold=True)
	#plt.axes().set_aspect("equal")	
	ax = plt.gca()
	ax.spines['bottom'].set_position(('data',0))
	ax.spines['left'].set_position(('data',0))	
	if isBorda:
		plt.text(1.1*r, 0.4*r, 'C1', ha='center', va='center',size=24, alpha=.5)
		plt.text(r/2, 1.1*r, 'C2', ha='center', va='center', size=24, alpha=.5)
		plt.text(-r/2, 1.1*r, 'C3', ha='center', va='center', size=24, alpha=.5)
		plt.text(-1.1*r, 0.4*r, 'C4', ha='center', va='center',size=24, alpha=.5)
		plt.text(-1.1*r, -0.4*r, 'C5', ha='center', va='center',size=24, alpha=.5)
		plt.text(-r/2, -1.1*r, 'C6', ha='center', va='center',size=24, alpha=.5)
		plt.text(r/2, -1.1*r, 'C7', ha='center', va='center',size=24, alpha=.5)
		plt.text(1.1*r, -0.4*r, 'C8', ha='center', va='center',size=24, alpha=.5)	
	an = np.linspace(0, 2*np.pi, 100)
	if len(xs)<1000 :
		plt.plot(r*np.cos(an), r*np.sin(an),alpha=0.5)
	plt.scatter(xs,ys,s =100 ,c = cores)		
	plt.yticks(())
	plt.xticks(())
	
	
	############################SUBPLOT - HISTOGRAMA###########################
	eixo = plt.subplot(122)
	bins = [1,2,3,4,5,6,7,8]
	cor = [[ 1, 0, 0.85],[ 0.4,0,0.8520772],[0,0,1],[0.2,1,1],[0.2,1,0],
[0.9,0.973553065884,0.09],[1,0.407421725309,0],[1,0,0]]
	bars = plt.bar(bins, hist, width = 1)	
	for i in range(len(bars)):
		bars[i].set_color(cor[i])
	bins = [t+0.5 for t in bins]	
	plt.title("Histograma",fontsize=40)
	eixo.set_xticks(bins)
	eixo.set_xticklabels(('C1', 'C2', 'C3', 'C4', 'C5','C6','C7','C8'))	
	plt.tight_layout()	
	print('Salvando...',nome)
	plt.savefig(nome+".png")
	
	


def distribuicaoBorda(r,listaCordas):
	xs =[]
	ys =[]
	cores = []
	HBorda = np.zeros(8)
	for t in range(len(listaCordas)):
		xs.append(listaCordas[t][0][0])
		xs.append(listaCordas[t][1][0])	
		ys.append(listaCordas[t][0][1])
		ys.append(listaCordas[t][1][1])		
		#CALCULAR O HISTOGRAMA DA DISTRIBUIÇÃO DOS ÂNGULOS
		cor1,HBorda = corAngulo(mat.atan2(listaCordas[t][0][1],listaCordas[t][0][0]),HBorda)
		cor2,HBorda = corAngulo(mat.atan2(listaCordas[t][1][1],listaCordas[t][1][0]),HBorda)	
		cores.append(cor1)
		cores.append(cor2)		
	exibeGrafico(r,xs,ys,cores,HBorda,"distribuicao_borda",True)

def corAngulo(angulo,HBorda):
	cor = [[ 1, 0, 0.85],[ 0.4,0,0.8520772],[0,0,1],[0.2,1,1],[0.2,1,0],
[0.9,0.973553065884,0.09],[1,0.407421725309,0],[1,0,0]]
	'''
	Divide o círculo em 8 arcos, cada 1 com ângulo interno correspondente de 45°.
	Verifica em qual dos 8 arcos o ângulo do ponto com a circuferência pertence,
	somando 1 ao valor no Histograma e retornando a cor corresponde do arco em questão. 
	'''
	if angulo<mat.pi/4 and angulo>=0:
		s = cor[0]
		HBorda[0]+=1
	elif angulo<mat.pi/2 and angulo>=mat.pi/4:
		s = cor[1]
		HBorda[1]+=1
	elif angulo<3*mat.pi/4 and angulo>=mat.pi/2:
		s = cor[2]
		HBorda[2]+=1
	elif angulo<mat.pi and angulo>=3*mat.pi/4:
		s = cor[3]
		HBorda[3]+=1
	elif angulo<0 and angulo>= - mat.pi/4:
		s = cor[4]
		HBorda[4]+=1
	elif angulo<- mat.pi/4 and angulo>= - mat.pi/2:
		s = cor[5]
		HBorda[5]+=1
	elif angulo<-mat.pi/2 and angulo>= -3*mat.pi/4:
		s = cor[6]
		HBorda[6]+=1
	else:
		s = cor[7]
		HBorda[7]+=1
	
	return s,HBorda


def distribuicaoRadial(r,listaCordas):
	listaMed = ep2.determinaPontosMedios(listaCordas)	
	HRadial = np.zeros(8)
	xs =[]
	ys =[]
	cores = []
	for t in range(len(listaMed)):
		xs.append(listaMed[t][0])		
		ys.append(listaMed[t][1])			
		#CALCULAR O HISTOGRAMA DA DISTRIBUIÇÃO DAS COROAS CIRCULARES
		cor1,HRadial = corRadial(listaMed[t][0],listaMed[t][1],HRadial,r)		
		cores.append(cor1)	
	exibeGrafico(r,xs,ys,cores,HRadial,"distribuicaoRadial",False)


def corRadial(x,y,HRadial,r):
	cor  = [[ 1, 0, 0.85],[ 0.4,0,0.8520772],[0,0,1],[0.2,1,1],[0.2,1,0],
[0.9,0.973553065884,0.09],[1,0.407421725309,0],[1,0,0]]
	'''
	Divide o círculo em 8 coroas circulares. 
	 I) Verifica se o ponto está dentro a menor circunferência senão, se está na
	 segunda menor, senão na terceira menor, e assim por diante.
	 II) Escolhe a cor e adiciona 1 a posição do histograma correspondente.
	'''			
	if x**2 + y**2 <= (r/8)**2:
		s = cor[0]
		HRadial[0]+=1
	elif x**2 + y**2 <= (r/4)**2:
		s = cor[1]
		HRadial[1]+=1
	elif x**2 + y**2 <= (3*r/8)**2:
		s = cor[2]
		HRadial[2]+=1
	elif x**2 + y**2 <= (r/2)**2:
		s = cor[3]
		HRadial[3]+=1
	elif x**2 + y**2 <= (5*r/8)**2:
		s = cor[4]
		HRadial[4]+=1
	elif x**2 + y**2 <= (3*r/4)**2:
		s = cor[5]
		HRadial[5]+=1
	elif x**2 + y**2 <= (7*r/8)**2:
		s = cor[6]
		HRadial[6]+=1
	else:
		s = cor[7]
		HRadial[7]+=1
	return s,HRadial

def distribuicaoArea(r,listaCordas):
	listaMed = ep2.determinaPontosMedios(listaCordas)
	HArea = np.zeros(8)
	xs = []
	ys = []
	cores = []
	for t in range(len(listaMed)):
		xs.append(listaMed[t][0])
		ys.append(listaMed[t][1])
		cor1,HArea = corArea(listaMed[t][0],listaMed[t][1],HArea,r)
		cores.append(cor1)
	exibeGrafico(r,xs,ys,cores,HArea,"distribuicao_area",False)


def corArea(x,y,HArea,r):
	cor  = [[ 1, 0, 0.85],[ 0.4,0,0.8520772],[0,0,1],[0.2,1,1],[0.2,1,0],
[0.9,0.973553065884,0.09],[1,0.407421725309,0],[1,0,0]]
	'''
	Divide o círculo em 8 partes de mesma área. A divisão funciona
	basicamente no estilo 'yin yang'. 
	Funciona assim:

	I) Divido o raio em 8 partes iguais
	II) Na parte de cima da circunferência, da esquerda com a direita,
	faço semi circunferências cujo raio começa com r/8, e vão aumentando
	numa progressão aritmética de razão r/8, até chega na circunferência de raio r.
	III) Na parte de baixo da circunferência, faço a mesma coisa, porém da direita 
	para esquerda (Sentido oposto)
	IV) No final, o círculo foi divido em 8 áreas iguais,  a soma das áreas equivale a
	circunferência inteira.

	'''	
	if y>=0:
		if (x+(7/8)*r)**2 +y **2 <= (r/8)**2 :				
			s = cor[0]
			HArea[0] += 1
		elif (x+(3/4)*r)**2 + y**2 <= (r/4)**2:
			s = cor[1]
			HArea[1] += 1
		elif (x+(5/8)*r)**2 + y**2 <= (3*r/8)**2:
			s = cor[2]
			HArea[2] += 1
		elif (x+(1/2)*r)**2 + y**2 <= (r/2)**2:
			s = cor[3]
			HArea[3] += 1
		elif (x+(3/8)*r)**2 + y**2 <= (5*r/8)**2:
			s = cor[4]
			HArea[4] += 1
		elif (x+(1/4)*r)**2 + y**2 <= (3*r/4)**2:
			s = cor[5]
			HArea[5] += 1
		elif (x+(1/8)*r)**2 + y**2 <= (7*r/8)**2:
			s = cor[6]
			HArea[6] += 1
		else:
			s = cor[7]			
			HArea[7] += 1
	else:
		if (x-(7/8)*r)**2 +y **2 <= (r/8)**2 :				
			s = cor[7]
			HArea[7] += 1
		elif (x-(3/4)*r)**2 + y**2 <= (r/4)**2:
			s = cor[6]
			HArea[6] += 1
		elif (x-(5/8)*r)**2 + y**2 <= (3*r/8)**2:
			s = cor[5]
			HArea[5] += 1
		elif (x-(1/2)*r)**2 + y**2 <= (r/2)**2:
			s = cor[4]
			HArea[4] += 1
		elif (x-(3/8)*r)**2 + y**2 <= (5*r/8)**2:
			s = cor[3]
			HArea[3] += 1
		elif (x-(1/4)*r)**2 + y**2 <= (3*r/4)**2:
			s = cor[2]
			HArea[2] += 1
		elif (x-(1/8)*r)**2 + y**2 <= (7*r/8)**2:
			s = cor[1]
			HArea[1] += 1
		else:
			s = cor[0]
			HArea[0] += 1
	return s,HArea
	

'''
Função que dá plot e salva o gráfico da distribuição de cordas.

Como na distribuição de cordas eu não preciso calcular o histograma, o gráfico
é plotado e salvo na própria função, diferentemente das anteriores acima.


'''
def distribuicaoCordas(r,listaCordas):
	#Cores diferentes: Se a corda for maior que o lado do triângulo equilátero inscrito,
	# então fica VERDE. Caso contrário, é VERMELHA.
	novaCor = [0,1,0.1]	
	novaCor2 = [1,0,0.1]
	#lado do triângulo equilátero inscrito na ircunferência
	dist = r*mat.sqrt(3)
	colores = []
	for t in listaCordas:
		dp = mat.sqrt((t[0][0]-t[1][0])**2 + (t[0][1]-t[1][1])**2)
		if dp > dist:
			colores.append(novaCor)
		else:
			colores.append(novaCor2)
	fig, ax = plt.subplots(figsize=(28,15))
	fig.set_size_inches(18.5, 10.5)
	ax.spines['bottom'].set_position(('data',0))
	ax.spines['left'].set_position(('data',0))
	an = np.linspace(0, 2*np.pi, 100)
	if len(listaCordas)<1000 :
		plt.plot(r*np.cos(an), r*np.sin(an),alpha=0.5)	
	lc = mc.LineCollection(listaCordas, colors=colores, linewidths=2)	
	ax.add_collection(lc)
	ax.autoscale()
	ax.margins(0.1)
	ax.set_xticks(())
	ax.set_yticks(())
	ax.set_title("A circunferência",fontsize=40)	
	ax.set_aspect("equal")
	plt.tight_layout()
	plt.yticks(())
	plt.xticks(())
	
	print('Salvando... distribuicao_cordas')
	plt.savefig("distribuicao_cordas.png")

	
if __name__ == '__main__':
	main()