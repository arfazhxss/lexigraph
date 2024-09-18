#!/usr/bin/env python
import fileinput
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
        twoAV="2"
        beginAV = "''''"
        endAV = "\"\"\"\""

        #   Making a list of strings that have all the words to be avoided
        avoidWords=[]
        for words in fileinput.input():
            currWord=words[0:-1]
            if ((currWord)==endAV):
                break
            elif ((currWord==beginAV)or(currWord==twoAV)):
                continue
            avoidWords.append(currWord)
            avoidWords.append(currWord.capitalize())
        fileinput.close()

        #   Now looking at the rest of the lines
        mainLines=[]
        for lines in fileinput.input():
            mainLines.append(lines[0:-1])
        fileinput.close();

        # for lines in mainLines:
        #     print("--["+lines+"]--")

        #   Making a list of the words that we'll be working on
        mainWords=[]
        for lines in mainLines:
            for words in lines.split():
                if words in avoidWords:
                    continue
                mainWords.append(words)

        #   Now, sorting it, alphabetically
        SortedWords=mainWords[:]
        SortedWords.sort(key=str.lower)

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

        # print("0000000001111111111222222222233333333334444444444555555555566666666667")
        # print("1234567890123456789012345678901234567890123456789012345678901234567890")
        for lineIndex in range(0,count):
            currString1=lineStr1[lineIndex]
            currString1=" "+currString1;
            currString1=startTrim(currString1)
            currString2=lineStr2[lineIndex]
            currString2=currString2+" "
            currString2=endTrim(currString2)
            # print(f"{currString1:>29}"+currString2)
            print("{:>29}{}".format(currString1,currString2))

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