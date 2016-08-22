#!/usr/bin/env python
# -*- coding: utf-8 -*-
#.n Juliano Garcia de Oliveira
#.u 9277086


import math
import random


# getPonto(r): Função que retorna um ponto aleatório na circunferência. 
# I ) Gera um Ângulo aleatório entre 0 e 2pi
# II) Os pontos x e y são calculados pelo seno e cosseno desse ângulo
# III) retorna os pontos x,y
def getPonto(r):
	angulo = random.uniform(0,2*math.pi) 		
	x = math.cos(angulo)* r
	y = math.sin(angulo)*r
	return x,y

# metodo1(r,n): Função que aplica o primeiro método para o cálculo da probabilidade!
# I ) Calcula o lado L do triângulo equilátero inscrito na circunferência de raio r
# II) Calcula 2 pontos aleatórios na circunferência: A e B
# III) Calcula a distância AB entre o ponto A e ponto B
# IV) Verifica se AB é maior que o lado L
# V) Retorna a razão entre a quantidade de vezes que a corda AB foi maior que o lado L
def metodo1(r,n):	
	#lado do triangulo equilatero inscrito na circunferencia de raio r
	ntemp = n
	L = math.sqrt(3)*r			
	cont1 = 0
	

	while ntemp>0:
		#Ponto A (Ax,Ay)
		Ax,Ay = getPonto(r)		
		#ponto B (Bx,By)
		Bx,By = getPonto(r)				
		
		# ARCO AB = r*math.acos((Ax*Bx+Ay*By)/(math.sqrt(Ax**2+Ay**2)*math.sqrt(Bx**2+By**2)))		

		# Calculando a corda AB
		AB = math.sqrt((Ax-Bx)**2+(Ay-By)**2)

		if AB > L:
			cont1 += 1
		ntemp -= 1
	
	prob1 = cont1/n
	return prob1

# metodo2(r,n) : Função que aplica o segundo método para o cálculo da probabilidade!
# I ) Calcula um ponto aleatório C na circunferência
# II) Calcula um ponto aleatório P da reta OC (Origem até o ponto C)
# III) Calcula a distância d entre o ponto P e a origem
# IV) Verifica se 'd' é maior que metade do raio
# V) Retorna a razão entre a quantidade de vezes que a distancia 'd' foi maior que metade do raio
def metodo2(r,n):
	cont2 = 0
	ntemp = n

	while ntemp>0:
		Cx,Cy = getPonto(r)
		
		val = random.random()
		Px = val*Cx
		Py = val*Cy
				
		d = math.sqrt(Px**2+Py**2)		

		if d < (r/2):
			cont2 += 1
		ntemp -= 1
	
	prob2 = (cont2/n)
	return prob2



# metodo3(r,n) : Função que aplica o terceiro método para o cálculo da probabilidade!
# I ) Calcula um ponto aleatório P DENTRO DA CIRCUNFERÊNCIA
# II) Calcula a distancia 'd' entre o ponto P e a origem
# III) Verifica se 'd' é maior que metade do raio
# IV) Retorna a razão entre a quantidade de vezes que a distancia 'd' foi maior que metade do raio
def metodo3(r,n):	
	cont3 = 0
	ntemp = n

	while ntemp > 0:	
		
		# Método Utilizado: Ângulo e raiz de número aleatório
		# I) Gera um número randômico, tira sua raiz e multiplica pelo raio
		# II) Gera um ângulo aleatório entre 0 e 2pi
		# III) Gera um ponto P dentro da circunferência
		# OBS = Tentei vários métodos de gerar números dentro da circunferência,
		# esse era o método que gerava os pontos mais uniformemente 
		# (relacionado ao fato de raiz quadrada de um número entre 0 e 1, que é maior que o numero original..)
		intervalo = math.sqrt(random.random())*r			
		theta = random.uniform(0,2*math.pi)
		Px = math.cos(theta)*intervalo
		Py = math.sin(theta)*intervalo
		
		d = math.sqrt(Px**2+Py**2)
		if d < (r/2):
			cont3 += 1

		ntemp -= 1
	prob3 = (cont3/n)
	
	
	return prob3
	



def main():
	# Entrada de dados pelo usuário
	r = float(input("Digite o raio da circunferência: "))
	while r<=0:
		r = float(input("\nDigite o raio (deve ser maior que zero): "))
	n = int(input("\nDigite o n : "))
	while n<=0:
		n = int(input("\nDigite o n (deve ser maior que zero): "))

	# Chama as funções e imprime os valores
	valor1 = metodo1(r,n)
	print("Método 1 = ",valor1)
	valor2 = metodo2(r,n)
	print("Método 2 = ",valor2)
	valor3 = metodo3(r,n)
	print("Método 3 = ",valor3)

if __name__ == '__main__':
	main()