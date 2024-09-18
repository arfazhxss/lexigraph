#!/usr/bin/env python
import select
import sys
import re

def initialEndTrim (string):
    return "".join(string.rstrip())

def startTrim (string):
    string=string[-21:].split(" ",1)
    return string[-1]

def endTrim (string):
    string=(string[:32].rsplit(" ",1))
    return string[0]

def main():
    # (<>-<>) https://stackoverflow.com/questions/3762881/how-do-i-check-if-stdin-has-some-data
    if select.select([sys.stdin, ], [], [], 0.0)[0]:
        #   If we're here, we have found an input file (hopefully a .txt file)
        #   inputLine is going to make a list of all the lines inside the system input
        inputLines = sys.stdin.readlines()
        twoAV="2"
        beginAV = "''''"
        endAV = "\"\"\"\""
        # VersionFound is going to check if it's indeed of version "2" or not. If not, system will exit.
        verFound=False

        #   Making a list of strings that have all the words to be avoided
        avoidWords=[]
        for words in inputLines:
            currWord=words[0:-1]
            if ((currWord)==endAV):
                break
            elif (currWord==beginAV):
                continue
            elif (currWord==twoAV):
                verFound=True
                continue
            avoidWords.append(currWord)
            avoidWords.append(currWord.capitalize())

        #   Now looking at the rest of the lines in our inputLine
        mainLines=[]
        for lines in inputLines:
            if lines[0:-1] in avoidWords:
                continue
            elif (lines[0:-1]==beginAV):
                continue
            elif (lines[0:-1]==endAV):
                continue
            elif (lines[0:-1]==twoAV):
                continue
            mainLines.append(lines[0:-1])

        #   Here, if twoAV (Version2) wasn't found, the system would exit with the version name that was put on, say version 1
        if (verFound==False):
            twoAV=inputLines[0]
            sys.exit("Input is version {}, concord2.py expected version 2".format(twoAV[:-1]))

        #   Making a list of the words that we'll be working on (excluding the words-to-be-skipped [AVOIDWORDS])
        mainWords=[]
        for lines in mainLines:
            for words in lines.split():
                if words in avoidWords:
                    continue
                mainWords.append(words)

        #   Now, sorting the words excluding the words-to-be-skipped, alphabetically, non-case-sensitive-ly
        SortedWords=mainWords[:]
        SortedWords.sort(key=str.lower)

        # <74-91> is gonna 
        #       1   Make a sortedWord copy
        #       2   for each lines in our main paragraph, it will look for words that aren't exclusion/avoid words,
        #           if found, it will delete all leading and trailing spaces of each lines, remove the word from the 
        #           copied sortedWord list, all the words before the word-to-be-capped in one of the string
        #           add the rest to a different string
        #       3   The body will also have a counter working inside
        #       4   The body will also capitalize the main word to be capped
        count=0
        lineStr1=[]
        lineStr2=[]
        sortedWordsA=SortedWords[:]
        for word in sortedWordsA:
            for lines in mainLines:
                tempStr=""
                for currWord in lines.split():
                    if (currWord==word):
                        lines=lines.strip()
                        sortedWordsA[count]=""
                        lineString=re.sub(tempStr,"",lines,1)
                        lineString=re.sub(currWord,currWord.upper(),lineString)
                        lineStr1.append(tempStr)
                        lineStr2.append(lineString)
                        count+=1
                        break;
                    tempStr+=(currWord+" ")

        # <99-113> is going to read each lines from both strings lists, 
        #           slice both strings into specific limits, as given
        #           put the first stringA before width 29th
        #           put the rest from width 30th to 60th
        for lineIndex in range(0,count):
            currString1=lineStr1[lineIndex]
            currString1=" "+currString1;
            currString1=startTrim(currString1)
            currString2=lineStr2[lineIndex]
            currString2=currString2+" "
            currString2=endTrim(currString2)
            print("{:>29}{}".format(currString1,currString2))

        # This is for checking the char widths of the indentations
        # print("0000000001111111111222222222233333333334444444444555555555566666666667")
        # print("1234567890123456789012345678901234567890123456789012345678901234567890")
    else:
        print("ERROR: NO ARGUMENTS FOUND")


if __name__ == "__main__":
    main()

# USEFUL LINKS I'VE CHECKED: 
# 1 --> https://stackoverflow.com/questions/9989334/create-nice-column-output-in-python
# 2 --> https://unix.stackexchange.com/questions/506534/multiple-replacements-using-regular-expressions-in-python
# 3 --> https://stackoverflow.com/questions/9989334/create-nice-column-output-in-python
# 4 --> https://stackoverflow.com/questions/8450472/how-to-print-a-string-at-a-fixed-width
# 5 --> https://stackoverflow.com/questions/30636248/split-a-string-only-by-first-space-in-python
# 6 --> https://stackoverflow.com/questions/36139/how-to-sort-a-list-of-strings