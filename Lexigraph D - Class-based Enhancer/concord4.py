#!/usr/bin/env python3

#   IMPORTANT NOTE:
#       all files can be tested using the shell file <test5.sh>
#       in the command line, type:
#           --> bash test5.sh
#       or
#           --> chmod 777 test5.sh
#           --> /.test5.sh
#       the test5 does a routein test from test1 to test4 running between 
#       <in01.txt> to <in15.txt> and making diff test with <out01.txt> to <out15.txt>
#       also makes files <_out01.txt> to <_out15.txt> which is the output from the script
#       
#       a dummy fault-version file of <in16.txt> checking with <out16.txt> can also be found
#       
#       @arfazhxss 
#       06/12/2022


import re
import sys

class SentenceIterator:
    def __init__(self, words):
        self.words = words
        self.index = 0
    def __next__(self):
        try:
            word = self.words[self.index]
        except IndexError:
            raise StopIteration() # needed by Python to terminate a `for` loop
        self.index += 1 # update our current "position" in the sequence
        return word
    def __iter__(self):
        return self

class concord:
    def __init__(self, input=None, output=None):
        self.input=sys.stdin.readlines() if (input==None) else input.readlines()
        if (output!=None):
            self.output=output.write(concord.__repr__(self))
            self.output+=output.write('\n')
        else:
            self.output=output

    def __repr__(self):
        return '\n'.join(concord.full_concordance(self))

    def __iter__(self):
        return SentenceIterator(concord.full_concordance(self))
    
    #   <<<< EXCLUSION WORDS >>>>
    #       initially named as 'avoidwords' string in ASSIGNMENT1 <concord1.c>
    #       --> takes all words between '''' AND """"
    #       --> checks if there's a version 2 in the beginning of the .txt files
    #   
    #   Function to make a list of EXCLUSION WORDS
    #   --> IF VERSION 2 ISN'T FOUND, IT RETURNS 'FALSE' TO ___MAINS___, ___MAINW___
    # 
    def __avoidWords__ (self):
        cond=False
        string=[]
        for element in self.input:
            newstr=""
            if (re.search(r"^''''",element)!=None): continue
            elif (re.search(r"^2",element)!=None): 
                cond=True
                continue
            elif (re.search(r"^\"\"\"\"",element)!=None): break
            for a in re.finditer(r".",element): newstr += a.group()
            string.append(newstr)
            string.append(newstr.capitalize())
        if (cond==False): return False
        return string

    #   <<<< MAIN SENTENCES >>>>
    #   
    #   Function to sort out the SENTENCES
    #   --> IF VERSION 2 ISN'T FOUND, IT RETURNS 'FALSE' TO __MAINSTR__
    # 
    def __mainS__ (self):
        sent=[]
        avoid=concord.__avoidWords__(self)
        if (avoid==False): return False
        for element in self.input:
            newstr=""
            if (re.search(r"^''''",element)!=None): continue
            elif (re.search(r"^2",element)!=None): continue
            elif (re.search(r"^\"\"\"\"",element)!=None): continue
            for a in re.finditer(r".",element): newstr += a.group()
            if newstr in avoid: continue
            else: sent.append(newstr)
        return sent

    #   <<<< MAIN WORDS >>>>
    #   
    #   Function to sort out the IMPORTANT WORDS out of the SENTENCES excluding all EXCLUSION WORDS
    #   --> IF VERSION 2 ISN'T FOUND, IT RETURNS 'FALSE' TO ___MAINW___
    #   --> This function sorts the words by capital letters 
    #   --> in the start of all the words taken out 
    #   --> from the SENTENCES
    #   
    def __mainW__ (self):
        if (concord.__mainS__(self)==False): return False
        words=[]
        for sents in concord.__mainS__(self):
            for svoids in sents.split():
                avoids = concord.__avoidWords__(self)
                if (avoids==False): return False
                if (svoids in avoids): continue
                words.append(svoids)
        words.sort(key=str.lower)
        return words
    
    #   Function to strip (get rid of any spaces) start and end of SENTENCES
    def initialEndTrim (string):
        return "".join(string.rstrip())
    
    #   Function to strip start of SENTENCES
    def startTrim (string):
        string=string[-21:].split(" ",1)
        return string[-1]
    
    #   Function to strip end of SENTENCES
    def endTrim (string):
        string=(string[:32].rsplit(" ",1))
        return string[0]
    
    #    <<<< MAIN STRING >>>>
    #    <119-141>
    #       1   Make a sortedWord copy
    #       2   for each lines in our main paragraph, it will look for words that aren't exclusion/avoid words,
    #           if found, it will delete all leading and trailing spaces of each lines, remove the word from the 
    #           copied sortedWord list, all the words before the word-to-be-capped in one of the string
    #           add the rest to a different string
    #       3   The body will also have a counter working inside
    #       4   The body will also capitalize the main word to be capped
    # 
    #   <142-150>  
    #       --> is going to read each lines from both strings lists, 
    #       --> slice both strings into specific limits, as given
    #       --> put the first stringA before width 29th
    #       --> put the rest from width 30th to 60th
    def __mainSTR__ (self): 
        if (concord.__mainW__(self)==False): return ["Input is version {}, concord4.py expected version 4".format(self.input[0].strip())]
        mainSTR=[]
        count=0
        lineStr1=[]
        lineStr2=[]
        sortedWordsA=concord.__mainW__(self)[:]
        slen=len(sortedWordsA)
        for word in sortedWordsA:
            for line in concord.__mainS__(self):
                tempStr=""
                for currWord in line.split():
                    if (currWord==word):
                        line=line.strip()
                        sortedWordsA[count]=""
                        # print(str(count)+"\tcurrW:["+)
                        lineString=re.sub(tempStr,"",line,1)
                        lineString=re.sub(currWord,currWord.upper(),lineString)
                        lineStr1.append(tempStr)
                        lineStr2.append(lineString)
                        count+=1
                        break
                    tempStr+=(currWord+" ")
        for lineIndex in range(0,count):
            currString1=lineStr1[lineIndex]
            currString1=" "+currString1
            currString1=concord.startTrim(currString1)
            currString2=lineStr2[lineIndex]
            currString2=currString2+" "
            currString2=concord.endTrim(currString2)
            mainSTR.append("{:>29}{}".format(currString1,currString2))
        return mainSTR

    #   RETURNS MAIN STRING
    def full_concordance (self):
        return concord.__mainSTR__(self)