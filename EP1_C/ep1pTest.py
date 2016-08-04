import time
time1 = time.time()

def main():	
	mA = 0
	aN = 0
	som = 0
	for X in range(1,1000000):		
		som+=colz(X)	
	print("--- %s seconds ---" % (time.time() - time1))
	print('Soma = ',som)
	time2 = time.time()
	'''
	for X in range(1,1000000):		
		calculateSteps(X)
	print("--- %s seconds ---" % (time.time() - time2))
	'''

#Little optimized function
def colz(n):
	i = 0
		
	while n!=1:		
		while n%2!=0:
			n = (3*n + 1)/2
			i+=2
		while n%2==0:
			n /= 2
			i += 1
	return i

#Default function
def calculateSteps(n):
	c = 0
	while n!=1:		
		n = 3*n+1 if n%2!=0 else n/2
		c+=1
	return c
		

if __name__ == '__main__':
	main()