#!/usr/bin/env python
# -*- coding: utf-8 -*-
def main():
	print("----Verificador de números triangulares---- \n")
	num = int(input("Digite um número inteiro positivo: "))	
	t = 1 
	prod = 6
	
	while prod < num:
		t += 1
		prod = t * (t+1) * (t+2)

	if prod == num:
		print("O número ",num, "é triangular!")
	else:
		print("O número ",num, "não é triangular!")


if __name__ == '__main__':
	main()