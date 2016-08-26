from math import ceil
import re
def main():	
	fileName = "job.txt";
	cols     = int(input("Cols number:"))
	
	text	 = readEntry(fileName)	
	text     = text.split('\n\n')
	#Dealing with paragraphs
	for x in range(len(text)):
		text[x] = text[x].replace("\n"," ")
		text[x] += "\n\n"
	for p in text:
		pass
	
	
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

def justifyWords(p,cols):
	bufferW = []
	firstW  = 0
	lineLen = 0
	while()









def fullJustify(p, cols):
    
    bufferW = []
    firstWordIdx = 0
    lineLen = len(p[0])
    for i in range(1, len(p)):
        if lineLen + 1 + len(p[i]) <= cols:
            lineLen += (1 + len(p[i]))
        else:
            line = generateEvenSpacedLine(firstWordIdx, i - 1, cols, p, lineLen)
            bufferW.append(line)
            firstWordIdx = i
            lineLen = len(p[i])
            
    lastLine = generateLeftJustifiedLine(firstWordIdx, len(p) - 1, cols, p, lineLen)
    bufferW.append(lastLine)
    return bufferW
        
def generateEvenSpacedLine(firstWordIdx, lastWordIdx, maxWidth, words, lineLen):
    numWords = lastWordIdx - firstWordIdx + 1
    if numWords == 1:
        return words[firstWordIdx] + '_'*(maxWidth - lineLen)
     
    numGaps = numWords - 1   
    spaceToDistr = maxWidth - lineLen
    gapSpace, extraGaps = divmod(spaceToDistr, numGaps)
    line = words[firstWordIdx]
    
    for i in xrange(firstWordIdx + 1, lastWordIdx + 1):
        line += ('_'*(gapSpace + 1))
        if extraGaps > 0:
            line += '_'
            extraGaps -= 1
        
        line += words[i]
            
    return line
        
def generateLeftJustifiedLine(firstWordIdx, lastWordIdx, maxWidth, words, lineLen):
    line = words[firstWordIdx]
    for i in xrange(firstWordIdx + 1, lastWordIdx + 1):
        line += ('_' + words[i])
    line += ('_'*(maxWidth - len(line)))
    return line




#TODO: IMPLEMENT CASE WHEN THE SINGLE WORD IS LARGER THAN COLUMNS
def justifyParagraph(p,cols):
	print(len(p))
	bufferW = ""
	i = 0
	while i <= len(p):
		sL = ""		
		sumT = 0
		j = i
		if len(p[i]) >= cols:
			bufferW  += p[i]+"\n"
			i += 1

		print("I = ",i)
		
		while i + 1 < len(p) and sumT + len(p[i+1]) + ceil(i-j+2)/2 <= cols:			
			sumT+= len(p[i+1]) + ceil(i-j+2)/2
			i += 1

		for x in range(j,i):
			sL += p[x]+"_"			
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