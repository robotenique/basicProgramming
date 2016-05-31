def main():
	p, q = leEntrada("arquivo.txt")
	simulaQuad(10,10,q,1)

	print(p)
	print(q)
	
def leEntrada(nome):
	with open(nome) as f:
		content = [x.strip("\n") for x in f.readlines()]	
	for x in range(1,len(content)):
		content[x] = [int(t) for t in content[x].split(",")]
	return 0 if content[0]=="Q" else 1,content[1:]

def simulaQuad(n,m,lista,t):
 	
	'''
	Células que vivem!
	'''
 	listOriginal = lista.copy()
 	listaViva = []
 	for cel in lista:
 		x,y  = cel[0],cel[1] 
 		controle = 0
 		'''
		Quando a célula não está no extremo
		'''		
 		if all([x!=0,x!=n-1,y!=0,y!=m-1]): 			
 			for x in [[x+1,y-1],[x+1,y],[x+1,y+1],[x,y+1],[x-1,y+1],[x-1,y],[x-1,y-1]]:
 				print("x = ",x)
 				if any((x==item for item in listOriginal)): 					
 					listOriginal.remove(x)
 					controle+=1
 					if controle>3:
 						break 			
 			if controle==2 or controle==3: 			
	 				print("APPENDANDO",cel)
 				listaViva.append(cel)
 		'''
 		Quando a célula está no extremo
 		'''
 		else:
 			pass

def 

	
	
if __name__ == '__main__':
	main()