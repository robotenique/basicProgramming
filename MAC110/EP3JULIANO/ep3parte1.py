#!/usr/bin/env python
# -*- coding: utf-8 -*-
#.n Juliano Garcia de Oliveira
#.u 9277086
import random
import numpy as np
import math as mat
import matplotlib.pyplot as plt


	
def main():	
	
	Hlist = list()
	listaHistogramas = list()
	nomeArquivos=["hist_escala_tranlacao","hist_soma","hist_raiz","hist_normal_Z0","hist_normal_Z1"]
	
	#Entrada do usuário
	n = int(input("\nDigite o n  : "))	
	while n==0 :
		n = int(input("\nDigite o n (Inteiro Positivo) : "))
	a = float(input("\nDigite o a : "))
	b = float(input("\nDigite o b : "))

	#Criação dos Vetores iniciais (O cálculo do M se dá através da Rice Rule!)
	m = mat.ceil(1.2 * 2 * mat.pow(n,1/3))
	V1 = np.empty(n)
	V2 = np.empty(n)
	V3 = uniformVetor(n)
	V4 = np.zeros(n)
	V5 = np.zeros(n)

	#Aplica todos as funções de transformação linear nos vetores.
	V1 = transformacaoEscala(uniformVetor(n),V1,n,a,b)	
	V2 = somaVetores(uniformVetor(n),uniformVetor(n),V2,n)	
	V3 = raizVetor(V3,n)
	V4,V5 = normalTransform(uniformVetor(n),uniformVetor(n),V4,V5,n)
	
	#Calcula os histogramas de cada vetor e adiciona na listaHistogramas
	listaHistogramas.append(histogram(V1,n,Hlist,m))
	listaHistogramas.append(histogram(V2,n,Hlist,m))
	listaHistogramas.append(histogram(V3,n,Hlist,m))
	listaHistogramas.append(histogram(V4,n,Hlist,m))
	listaHistogramas.append(histogram(V5,n,Hlist,m))

	#Itera sobre a lista listaHistogramas e dá plot e salva o arquivo com o nome correspondente
	for ind in range(5):
		salvaHistogram(listaHistogramas[ind],nomeArquivos[ind])



'''
 Funções de transformação vetorial.
 Especificação de cada uma está no EP3.

'''
		
def transformacaoEscala(U,V,n,a,b):
	V = [a+i*(b-a+1) for i in U]
	return V
def raizVetor(U,n):
	U = [mat.sqrt(i) for i in U]
	return U
def somaVetores(U1,U2,U,n):	
	U = [U1[i]+U2[i] for i in range(n)]
	return U
def normalTransform(U1,U2,Z1,Z2,n):		
	Z1 = [mat.cos(2*mat.pi*U2[i])*mat.sqrt(-2*mat.log(U1[i]))  for i in range(n)]
	Z2 = [mat.sin(2*mat.pi*U2[i])*mat.sqrt(-2*mat.log(U1[i]))  for i in range(n)]
	return Z1,Z2


'''
 #histogram()

 Função para cálculo do Histograma.
 
 #ARGS:
  * U -list- Lista com os valores para calcular o histograma
  * n -int-  Tamanho da lista U
  * H -list- Lista vazia, a qual será transformada e será armazenado o cálculo do Histograma
  * m -int-  Número de intervalos para dividir os valores de U

 #RETURN:
  *[mTemp,H,bins,cor,amplitude] -list- Lista que contém dados necessários para plotar e salvar
o histograma. mTemp é a quantidade de intervalos para dividir, H é a lista do histograma já
calculado, cor é uma list com valores rgb aleatórios para plotar o gráfico, e a amplitude é
o valor de cada intervalo (ex, amplitude 1.5 : intervalos [1 2.5], ]2.5,5.5] , ]5.5,7] ... etc)
'''

def histogram(U,n,H,m):
	data = U
	mTemp = 0 if max(data) == min(data) and not n==1 else  m
	cor = np.random.rand(3,1) #Cor aleatória
	amplitude = (max(data)-min(data))/mTemp if mTemp!=0 else 0
	
	if mTemp==0:
		'''
		Caso o vetor seja apenas dados iguais. Por ex: [1,1,1,1,1,1]
		'''		
		bins = np.array([min(data),min(data)+0.1])		
		H = [n]
	else:
		if not n==1:
			'''
			Situação padrão normal. Calcula os bins usando mTemp, e então
			calcula o Histograma.
			'''
			#Limite da divisão de intervalos = 400
			mTemp = 400 if mTemp > 400 else mTemp
			amplitude = (max(data)-min(data))/mTemp
			H = [0 for i in range(mTemp)]			
			bins = np.linspace(min(data),max(data),mTemp+1)			
			'''
			Algoritmo para cálculo do Histograma:
			I) Verifica se o número está dentro de um intervalo;
			
			II) Se estiver dentro do intervalo, remove o número da list (para não
			verificar denovo!)

			III) Se não estiver, verifica o próximo número, e assim por diante, 
			intervalo por intervalo.
			'''
			for x in range(mTemp):				
				i = 0
				while i<len(data):	
					if data[i]>=bins[x] and data[i]<bins[x+1]:
						data.remove(data[i])
						H[x] += 1
					else:
						i += 1
			#Arredondamento do bins p/ 3 casas decimais
			bins = [round(item,3) for item in bins]
		else:
			'''
			Caso o vetor seja apenas tamanho 1. Exemplo: [1]
			Há uma exceção apenas para o gráfico ficar mais bonito e legível.
			'''
			H = np.array([1])			
			bins = np.array([min(data),min(data)+0.1])
	return [mTemp,H,bins,cor,amplitude]

'''
 #salvaHistogram()

 Função para plotar e salvar o histograma.
 
 #ARGS:  
  * hist -list-   Lista que contém valores necessários para plotar o histograma:
mTemp,H,bins,cor,amplitude 
  * nome -string- String com o nome da imagem a ser salva
 
 #RETURN:

'''
def salvaHistogram(hist,nome):	
	#Associação de variáveis (Objetivo puramente mnemônico)
	mTemp = hist[0]
	H = hist[1]
	bins = hist[2]
	cor = hist[3]
	amplitude = hist[4]

	if mTemp==0:
		#Se possuo apenas valores iguais no array original
		plt.figure(figsize=(15,10))		
		plt.bar(bins[:-1], H, width = 0.1,color=cor)		
		plt.xlim(min(bins)-0.09, max(bins)+0.09)		  				
	else:
		#Imprime o nome do arquivo para melhor controle no terminal
		print(nome) 	
		if not amplitude==0:	
			#Situação normal de histogramas

			#Caso a divisão seja muito grande, aumenta a imagem
			if mTemp<16: 
				plt.figure(figsize=(15,10))					 
			else:				
				plt.figure(figsize=(25,15))			
			plt.bar(bins[:-1], H, width = amplitude,color=cor)			
			plt.xlim(min(bins),max(bins))
		else:	
			#Caso o vetor original possua tamanho 1
			plt.bar(bins[:-1], H, width = 0.1,color=cor)					
			plt.xlim(min(bins)-0.1,max(bins)+0.1)
	#Só exibe os labels no eixo X se a quantidade de intervalos é menor que 35
	if mTemp<35:		
		plt.xticks(bins)

	plt.savefig(nome+".png")
	
'''
 #uniformVetor()

 Função para gerar uma list com valores uniformemente distribuídos
 
 #ARGS:  
  * n -int- Tamanho da lista que será gerada
 
 #RETURN:
  * -list- Lista com valores uniformemente distríbuidos entre 0 e 1 (Não incluíndo o zero)

'''
def uniformVetor(n):
	#Não pode retornar o 0 por causa do cálculo de ln!
	return [random.uniform(10**(-15),1) for num in range(n)] 

if __name__ == '__main__':
	main()