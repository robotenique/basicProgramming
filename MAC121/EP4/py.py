import string
import random as rnd



# Return a random string, provided a placeholder
# The placeholder tells which position of the generated string will me random
def rndString(max):
    xStr = [rnd.choice(string.ascii_lowercase) for x in range(rnd.randint(3,max + 1))]
    return "".join(xStr)

c = 0
x = 150000
while(x > 0):
	c += 1
	print(rndString(10),sep="",end="")
	if c%10 == 0:
		print("")
	else:
		print(" ",end="")
	x -= 1



rndString(10)

