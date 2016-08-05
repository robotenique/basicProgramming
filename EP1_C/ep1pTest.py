import sys

static const

def main():	
	mA = 0
	aN = 0
	som = 0

	#List of 2^n numbers up until 2^32:
	
	listPow = []
	for x in range(1,60):
		listPow.append(2**x)	

	
	orig_stdout = sys.stdout
	f = open('out.txt', 'w')
	sys.stdout = f
	for x in listPow:
		print(x)
	sys.stdout = orig_stdout
	f.close()
	
	print("--- %s seconds ---" % (time.time() - time1))
	



	'''
	time2 = time.time()
	
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



def is2(num):
	return ((num & (num - 1)) == 0) and num != 0

#Default function
def calculateSteps(n):
	c = 0
	while n!=1:		
		n = 3*n+1 if n%2!=0 else n/2
		c+=1
	return c
		

if __name__ == '__main__':
	main()