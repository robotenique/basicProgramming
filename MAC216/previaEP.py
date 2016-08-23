from math import ceil
import re
def main():	
	fileName = "job.txt";
	cols     = int(input("Cols number:"))
	
	text	 = readEntry(fileName)	
	text     = text.split('\n\n')
	text	 = [re.split('\n| ',t) for t in text]
	
	justifyParagraph(text[0],cols)
	print(text[0])

	#for paragraph in text:
	#	justifyParagraph(paragraph,cols)
	
	
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
	bufferW = ""	
	count   = 0
	i       = 0
	if(len(paragraph)%2!=0):
		paragraph.append("")	
	#While the actual numbers of characters + length of next word + number of spaces is lower|equal to cols
	while (count + len(paragraph[i+1]) + ceil(i+2)/2 <= cols) and (i < len(paragraph) - 1):
		print("BufferW <- p[",i,"] + p[",i+1,"]")
		bufferW += paragraph[i] + "_" + paragraph[i+1]
		count   += len(paragraph[i])
		i += 2
			
	bufferW += "\n"
	#print(bufferW)


	'''hi
	OLD ONE
	bufferW = ""
	words   = line.strip(" ")
	wLength = [len(s) for s in words] 
	count,i = 0

	while True:
		if wLength[i] >= count:
			return wLength[i],bufferW
		count   += wLength[i]
		bufferW += words[i]
		if not (count + ceil((i+1)/2) <= cols and i < len(wLength)):
			break;
		i += 1
	'''





		
		




def readEntry(file_x):
	with open(file_x) as f:
		content = f.read()
	return content



if __name__ == '__main__':
	main()