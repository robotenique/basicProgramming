#!/usr/bin/env python
# -*- coding: utf-8 -*-
#.n Juliano Garcia de Oliveira
#.u 9277086
import math
import random

'''
 Funções que gera as cordas de acordo com o EP2.
'''

def listaCordasM1(r,n):		
	listPoints = []
	for x in range(n):
		p1 = getPonto(r)
		p2 = getPonto(r)
		while p1==p2:
			p1 = getPonto(r)
			p2 = getPonto(r)
		listPoints.append((p1,p2))
	
	return listPoints

def listaCordasM2(r,n):
	midPoints = []
	for x in range(n):
		c = getPonto(r)		
		val = random.random()
		p = (val*c[0],val*c[1])
		midPoints.append(p)	
	 
	return determinaPontosExtremos(r,midPoints)

def listaCordasM3(r,n):	
	midPoints = []
	for x in range(n):
		intervalo = math.sqrt(random.random())*r			
		theta = random.uniform(0,2*math.pi)
		midPoints.append((math.cos(theta)*intervalo,math.sin(theta)*intervalo))
	return determinaPontosExtremos(r,midPoints)	 


'''
Função que determina os pontos extremos dado os pontos médios.
'''
def determinaPontosExtremos(r,listaPontosMedios):	
	listExtremos = []	
	for ptMed in listaPontosMedios:

		'''
		Algoritmo para cálculo dos extremos:
		--Seja p o ponto médio e O a origem.
		
		I) Calcula o ponto 'c' da intersecção da reta OP com a circuferência, 
		que tem o mesmo sinal que o ponto p.
		II) Calcula o cos e o seno do ângulo para rotacionar o ponto c.
		III) Rotaciona o ponto c positiva e negativamente pelo ângulo encontrado
		IV)Os dois pontos são os pontos extremos da corda

		'''
		c = (r*math.cos(math.atan2(ptMed[1],ptMed[0])),r*math.sin(math.atan2(ptMed[1],ptMed[0])))
		cos = math.sqrt(ptMed[0]**2+ptMed[1]**2)/r
		sen = math.sqrt(1 - cos**2) #Relação fundamental da trigonometria
		# Rotacionar o ponto C ... Matrizes de Rotação
		rotPos = (cos*c[0] - sen*c[1] , sen*c[0] + cos*c[1])
		rotNeg = (cos*c[0] + sen*c[1] , cos*c[1] - sen*c[0])
		listExtremos.append((rotPos,rotNeg))		
	return listExtremos	
'''
Função que determina os pontos médios a partir de pontos extremos
'''
def determinaPontosMedios(listaExtremos):
	ptsMed = []	
	for x in range(len(listaExtremos)):
		#Apenas tira a média: de (x1 + x2) / 2, e de (y1 + y2) / 2
		xMed = (listaExtremos[x][0][0]+listaExtremos[x][1][0])/2
		yMed = (listaExtremos[x][0][1]+listaExtremos[x][1][1])/2	
		ptsMed.append((xMed,yMed))
	return ptsMed


# getPonto(r): Função que retorna um ponto aleatório na circunferência. 
# I ) Gera um Ângulo aleatório entre 0 e 2pi
# II) Os pontos x e y são calculados pelo seno e cosseno desse ângulo
# III) retorna o ponto (x,y)
def getPonto(r):
	angulo = random.uniform(0,2*math.pi) 		
	x = math.cos(angulo)* r
	y = math.sin(angulo)*r
	ponto = (x,y)
	return ponto






	
		
