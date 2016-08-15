import sys

def main():	
	maxVal = 23
	for n in range(2,maxVal+1):
		print("Colz(",n,") = ",colz(n))


'''
Correct sequence from 1 to 23:
Colz( 2 ) =  1
Colz( 3 ) =  7
Colz( 4 ) =  2
Colz( 5 ) =  5
Colz( 6 ) =  8
Colz( 7 ) =  16
Colz( 8 ) =  3
Colz( 9 ) =  19
Colz( 10 ) =  6
Colz( 11 ) =  14
Colz( 12 ) =  9
Colz( 13 ) =  9
Colz( 14 ) =  17
Colz( 15 ) =  17
Colz( 16 ) =  4
Colz( 17 ) =  12
Colz( 18 ) =  20
Colz( 19 ) =  20
Colz( 20 ) =  7
Colz( 21 ) =  7
Colz( 22 ) =  15
Colz( 23 ) =  15
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