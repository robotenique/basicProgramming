from math import ceil
import re
def main():	
	fileName = "job.txt";
	cols     = int(input("Cols number:"))
	
	text	 = readEntry(fileName)	
	text     = text.split('\n\n')
	text	 = [re.split('\n| ',t) for t in text]
	#testWhile()	
	
	#for paragraph in text:
	justifyParagraph(text[0],cols)
	
	
'''

	For 2 words, 1 space!
	That means, if I read n words, then i'll have math.ceil(n/2) spaces

	I found out that I need to parse by paragraph, not by line.
	I need to;
	1. Separate in paragraphs, detecting blank lines
	2. For each paragraph, remove all \n in the strings. 
	3. For each paragraph, process the string and create a new string which
	will hold the justified paragraph. I need to do this by making the 
	mathematics into the string.

'''









#TODO: IMPLEMENT CASE WHEN THE SINGLE WORD IS LARGER THAN COLUMNS
def justifyParagraph(paragraph,cols):
	print(len(paragraph))
	bufferW = ""
	i = 0
	while i <= len(paragraph) -1 :
		sL = ""		
		sumT = 0
		j = i
		if len(paragraph[i])
		
		while i + 1 < len(paragraph) and sumT + len(paragraph[i+1]) + ceil(i-j+2)/2 <= cols:			
			sumT+= len(paragraph[i+1]) + ceil(i-j+2)/2
			i += 1
		print("I agora = ",i)			

		for x in range(j,i):
			sL += paragraph[x]+"_"			
		sL = sL[:len(sL)-1]
		sL += "\n"
		bufferW += sL
	print(bufferW)



		
		




def readEntry(file_x):
	with open(file_x) as f:
		content = f.read()
	return content



if __name__ == '__main__':
	main()