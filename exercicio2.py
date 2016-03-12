#!/usr/bin/env python
# -*- coding: utf-8 -*-
def main():
	n = int(input("Digite a quantidade de números da sequência: "))	
	t = n
	maior = int(input("Digite um número: "))
	t -= 1
	while t != 0:
		t -= 1
		num = int(input("Digite um número: "))
		if  num > maior:
			maior = num		
	print("O maior número da sequência de ",n, "números é o ",maior)
			







if __name__ == '__main__':
	main()