#!/usr/bin/env python
# -*- coding: utf-8 -*-
def main():
	print("----Verificador de repetição de dígitos---- \n")
	n = int(input("Digite um número inteiro positivo: "))	
	d = int(input("Digite um algarismo (0 até 9) : "))	
	t = n	
	cont = 0
	while t > 0:
		if t % 10 == d:
			cont += 1
		t = t // 10
	print(" O algarismo ",d," aparece ",cont," vezes no número ",n,".")


if __name__ == '__main__':
	main()