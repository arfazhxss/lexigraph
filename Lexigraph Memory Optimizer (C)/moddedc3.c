#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "emalloc.h"

#include <stdbool.h>
#include <sys/types.h>
// #include "seng265-list.h"
#define LIST_MAXLEN_LSTRING 150

typedef struct node {
    char listedString [150];
    int listedValue;
    int listedStringSize;
    struct node *next;
} node;

node *newNode (char *string, int value) {
    assert(string!= NULL);

    node *newN = (node *)emalloc(sizeof(node));
    strncpy(newN->listedString, string, LIST_MAXLEN_LSTRING);
    newN->listedValue=value;
    newN->listedStringSize=strlen(newN->listedString);
    newN->next = NULL;
    return newN;
}

node *addFront (node *headNODE, node *newNODE) {
    newNODE->next = headNODE;
    return newNODE;
}

node *addEnd (node *headNODE, node *new) {
    node *curr;

    if (headNODE == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = headNODE; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return headNODE;
}

node *removeFront (node *headNODE) {
    node* currNODE = headNODE;
    if (currNODE == NULL) {return NULL;}
    else {
        headNODE=headNODE->next;
        free(currNODE);
    }
    return headNODE;
}

void applyAll (node *headNODE, void (*fn)(node *list, void *), void *arg) {
    for ( ; headNODE != NULL; headNODE = headNODE->next) {(*fn)(headNODE, arg);}
}

node *removeThis (node *headNODE, char *string) {
    node *curr, *prev;
    prev = NULL;
    for (curr=headNODE; curr!=NULL;curr=curr->next) {
        if (strcmp(string,curr->listedString)==0) {
            if (prev==NULL) {headNODE=curr->next;}
            else {prev->next=curr->next;}
            free(curr);
            return headNODE;
        }
        prev=curr;
    }
    fprintf(stderr,"removeThis: %s not in list", string);
    exit(1);
}

node *findThis (node *headNODE, char *string) {
    for (;headNODE!=NULL;headNODE=headNODE->next) {
        if (strcmp(string,headNODE->listedString)==0) {return headNODE;}
    } return NULL;
}

void printAll (node *headNODE) {
    if (headNODE==NULL) {printf("No node found to exist.\n");exit(0);}
    node *next;
    for (;headNODE!=NULL;headNODE=next) {
        printf("{%d}[%s] of size [%d]\n",headNODE->listedValue, headNODE->listedString, headNODE->listedStringSize);
        next=headNODE->next;
    }
}

void count (node *headNODE, void *arg) {
    int *i;
    i=(int*)arg;
    (*i)++;
}

void freeList (node *headNODE) {
    node *next;
    for (;headNODE!=NULL;headNODE=next) {
        next=headNODE->next;
        free(headNODE);
    }
}

node *replaceString (node* headNODE, char* stringmain, char* stringrep) {
    if (headNODE==NULL) {return NULL;}
    node *curr = NULL;
    node *prev = NULL;
    int iter=0;
    for (curr=headNODE; curr!=NULL;curr=curr->next) {
        if (strcmp(stringmain,curr->listedString)==0) {
            node *newNODE = newNode (stringrep,iter);
            // printf("%s of %d in %d\n",newNODE->listedString,newNODE->listedStringSize,newNODE->listedValue);
            if (prev==NULL) {
                // printf("SAY-YES\n");
                headNODE=removeFront(curr);
                headNODE=addFront(headNODE,newNODE);
                return headNODE;
            } else {
                prev->next=newNODE;
                newNODE->next=curr->next;
                return headNODE;
            }
        }
        iter++;
        prev=curr;
    }
    fprintf(stderr,"removeThis: %s not in list", stringmain);
    exit(1);
}

node *cleanThis (node *headNODE) {
    node* currNODE = headNODE;
    for (;currNODE!=NULL;currNODE=currNODE->next) {
        char* local=(char*)emalloc(sizeof(char));
        local=strdup(strtok(currNODE->listedString,"\n"));
        free(local);
    } free (currNODE);
    return headNODE;
}

node *capWHOLE (node* currNODE, int iter) {
    node *newNODE=NULL;
    char *capped = (char*)emalloc(sizeof(char));
    capped = strdup(currNODE->listedString);
    for (int i=0; i<(currNODE->listedStringSize);i++) {
        capped[i]=toupper(capped[i]);
    }
    newNODE=newNode(capped,iter);
    free(capped);
    return newNODE;
} 

// <https://stackoverflow.com/questions/5820810/case-insensitive-string-comparison-in-c>
int strcasecmp(char const *a, char const *b) {
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

node *sortedWords (node* headNODE) {
    node *currOne=headNODE;
    while (currOne) {
        // printf("currOne:[%s]\n",currOne->listedString);
        int temV1;
        node *currTwo=currOne->next;
        while (currTwo) {
            // printf("\tcurrTwo:[%s]\n",currTwo->listedString);
            if (strcasecmp(currOne->listedString,currTwo->listedString)>0) {
                char* temS = (char*)emalloc(sizeof(char));
                strcpy(temS,currOne->listedString);
                strcpy(currOne->listedString,currTwo->listedString);
                strcpy(currTwo->listedString,temS);
                temV1=currOne->listedValue;
                currOne->listedValue=currTwo->listedValue;
                currTwo->listedValue=temV1;
                free (temS);
            } currTwo=currTwo->next;
        } currOne=currOne->next;
    } return headNODE;
}

node *repeatedSentences (node* headWordNODE, node* headSenNode) {
    node *curr=headSenNode;
    node *headMAIN=NULL;
    int iterSENT=0;
    while (curr) {
        // printf("INSIDE:\tCURR IS:[%s]\n",curr->listedString);
        char* line = (char*)emalloc(sizeof(char));
        line=strdup(curr->listedString);
        char* word = (char*)emalloc(sizeof(char));
        word=strtok(line," ");
        if (!findThis(headWordNODE,word)) {
            headMAIN=addEnd(headMAIN,newNode(curr->listedString,iterSENT));
            // printf("\tTested Word{%d}:[%s]\n",iterSENT,word);
        }
        while ((word)) {
            word=strtok(NULL," ");
            if ((word)&&(!findThis(headWordNODE,word))) {
                headMAIN=addEnd(headMAIN,newNode(curr->listedString,iterSENT));
                // printf("\tTested Word{%d}:[%s]\n",iterSENT,word);
            }
        }
        free(word);
        free(line);
        iterSENT++;
        curr=curr->next;
    }   return headMAIN;
}

node *withoutExclusionWords (node* headWordNODE, node* headSenNode) {
    node *curr=headSenNode;
    node *headMAIN=NULL;
    int iterWORD=0;
    while (curr) {
        char* line = (char*)emalloc(sizeof(char));
        line=strdup(curr->listedString);
        char* word = (char*)emalloc(sizeof(char));
        word=strtok(line," ");
        if (!findThis(headWordNODE,word)) {
            headMAIN=addEnd(headMAIN,newNode(word,iterWORD));
            // printf("\tTested Word{%d}:[%s]\n",iterWORD,word);
        }
        while ((word)) {
            word=strtok(NULL," ");
            if ((word)&&(!findThis(headWordNODE,word))) {
                headMAIN=addEnd(headMAIN,newNode(word,iterWORD));
                // printf("\tTested Word{%d}:[%s]\n",iterWORD,word);
            }
        }
        free(word);
        free(line);
        iterWORD++;
        curr=curr->next;
    }   return headMAIN;
}

char *capStr (char *Str) {
    for (int i=0; i<strlen(Str); i++) {
        Str[i]=toupper(Str[i]);
    }
    return Str;
}

char *capMAIN (char *bigSTR, char *smolSTR) {
    // printf("BIG[%s]&MONTERRY[%s]\n",bigSTR,smolSTR);
    char* local = (char*)emalloc(sizeof(char));
    char* mainLINE = (char*)emalloc(sizeof(char));
    local = strtok(bigSTR, " ");
    if (!strcasecmp(local, smolSTR)) {
        // printf("1 ");
        // printf("%s\n",local);
        strcat(mainLINE,capStr(local));
        strcat(mainLINE," ");
    } else {strcat(mainLINE,local);strcat(mainLINE," ");}
    while (local) {
        local = strtok(NULL, " ");
        if ((local)&&(!strcasecmp(local, smolSTR))) {
            // printf("2 ");
            // printf("%s\n",local);
            local=capStr(local);
            strcat(mainLINE,capStr(local));
            strcat(mainLINE," ");
        } 
        else if (local) {strcat(mainLINE,local);strcat(mainLINE," ");}
    }
    // printf("SUR[%s]&MAVERICK[%s]\n",mainLINE,smolSTR);
    mainLINE[strlen(mainLINE)-1]='\0';
    strcpy(bigSTR, mainLINE);
    free(local);
// MALLOC ISSUE
    // free(mainLINE);
    return bigSTR;
}

node *modifiedSort (node *headNodeS, node *currNodeW) {
    node *currNodeS=headNodeS;
    node *currMAIN=NULL;
    node *headMAIN=NULL;
    char* lineMAIN=(char*)emalloc(sizeof(char));
    // int iterMAIN=0;
    while (currNodeW) {
        currNodeS=headNodeS;
        while (currNodeS) {
            // printf("{currNodeS->listedValue}:[%d] {currNodeW->listedValue}:[%d]\n",currNodeS->listedValue,currNodeW->listedValue);
            if (currNodeS->listedValue==currNodeW->listedValue) {
                // printf("\tS:[%d] W:[%d]\n",currNodeS->listedValue,currNodeW->listedValue);
                char* currLINE = (char*)emalloc(sizeof(char));
                currLINE=strdup(currNodeS->listedString);
                char* currWORD = (char*)emalloc(sizeof(char));
                currWORD=strtok(currLINE," ");
                if (!strcasecmp(currWORD,currNodeW->listedString)) {
                    // printf("{%d}[%s]\n",iterMAIN++,currNodeS->listedString);
                    currMAIN = newNode(currNodeS->listedString, currNodeS->listedValue);
                    headMAIN = addEnd(headMAIN, currMAIN);
                    strcpy(currNodeW->listedString,"");
                }
                while (currWORD) {
                    currWORD=strtok(NULL," ");
                    if ((currWORD)&&(!strcasecmp(currWORD,currNodeW->listedString))) {
                        currMAIN=newNode(currNodeS->listedString,currNodeS->listedValue);
                        headMAIN=addEnd(headMAIN,currMAIN);
                        strcpy(currNodeW->listedString,"");
                    }
                }
                free(currWORD);
                free(currLINE);
            }
            currNodeS=currNodeS->next;
        }   currNodeW=currNodeW->next;
    }   free(lineMAIN);
        return headMAIN;
}

// https://stackoverflow.com/questions/3893937/sorting-an-array-in-c
int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

node *valSORT (node *headNODE) {
    node *curr=headNODE;
    node *cnext=NULL;
    int count;
    int i;
    while (curr) {
        count=0;
        int *temp = (int*)emalloc(sizeof(int));
        temp[count++]=curr->listedValue;
        cnext=curr->next;
        // printf("curr is %s \n",curr->listedString);
        while (cnext&&(strcasecmp(curr->listedString,cnext->listedString)==0)) {
            // printf("\tcurr:{%d\\%s} cnext:{%d\\%s}\n",curr->listedValue,curr->listedString,cnext->listedValue,cnext->listedString);
            temp[count++]=cnext->listedValue;
            cnext = cnext->next;
        }
        if (count>1) {
            qsort(temp, count, sizeof(int),compare);
            i=0;
            while (i<count) {
                curr->listedValue=temp[i];
                i++;
                curr=curr->next;
            }
        }
        if (count==1) {curr=curr->next;}
        free (temp); 
    }   return headNODE;
}

bool isCAP (char *Str) {
    for (int i=0; i<strlen(Str); i++) {
        if (Str[i]!=toupper(Str[i])) {
            return false;
        }
    } return true;
    return Str;
}

char *rightLIST (char *mainLINE) {
    int charSIZE=0;
    char* line = (char*)emalloc(sizeof(char));
    line=strdup(mainLINE);
    char* rightLINE = (char*)emalloc(sizeof(char));
    rightLINE=strdup("");
    char* word = (char*)emalloc(sizeof(char));
    bool conditional = true;
    word=strtok(line," ");
    if (isCAP(word)) {conditional=false;} 
    else if (conditional) {
        strncat(rightLINE,word,strlen(word));
        strncat(rightLINE," ",1);
        charSIZE+=strlen(word);
        charSIZE+=1;
    }
    while (word!=NULL) {
        word=strtok(NULL," ");
        if (word!=NULL) {
            if (isCAP(word)) {conditional=false;} 
            else if (conditional) {
                strncat(rightLINE,word,strlen(word));
                strncat(rightLINE," ",1);
                charSIZE+=strlen(word);
                charSIZE+=1;
            }
        }
    }
    // printf("\nLINE1:[%s]\nACTUAL:[%s]\n\n",rightLINE,mainLINE);
    --charSIZE;
    // printf("CHARSIZE:[%d]\n",charSIZE);
    if (charSIZE>=20) {
        int targetSIZE=charSIZE-20;
        while (mainLINE[targetSIZE]!=' ') {
            // printf("we got [%c] at [%d] but we want a space!\n",mainLINE[targetSIZE],targetSIZE);
            targetSIZE++;
        }
        // printf("FoundTARGSize:[%d]\n",targetSIZE);
        int count=0;
        for (int i=targetSIZE+1; i<charSIZE; i++) {
            mainLINE[count]=rightLINE[i];
            // printf("\ni:{%d} [%c] VERSUS [%c]\n",i,rightLINE[i],mainLINE[count]);
            count++;
        }
        mainLINE[count++]=' ';
        mainLINE[count]='\0';
    }   else {
        mainLINE=strdup(rightLINE);
        free (rightLINE);
    }
// MALLOC ISSUE
    // free (rightLINE);
    free (line);
    free (word);
    return mainLINE;
}

char *leftLIST (char *mainLINE) {
    int charSIZE=0;
    char* line = (char*)emalloc(sizeof(char));
    line=strdup(mainLINE);
    char* leftLINE = (char*)emalloc(sizeof(char));
    leftLINE=strdup("");
    char* word = (char*)emalloc(sizeof(char));
    bool conditional = false;
    word=strtok(line," ");

    if (isCAP(word)) {
        conditional=true;
        strncat(leftLINE,word,strlen(word));
        strncat(leftLINE," ",1);
        charSIZE+=strlen(word);
        charSIZE+=1;
    }
    while (word!=NULL) {
        word=strtok(NULL," ");
        if (word!=NULL) {
            if (isCAP(word)) {
                conditional=true;
                strncat(leftLINE,word,strlen(word));
                strncat(leftLINE," ",1);
                charSIZE+=strlen(word);
                charSIZE+=1;
            }
            else if (conditional) {
                strncat(leftLINE,word,strlen(word));
                strncat(leftLINE," ",1);
                charSIZE+=strlen(word);
                charSIZE+=1;
            }
        }
    }
    // printf("SIZE[%d]\n",charSIZE);
    free (line);
    free (word);
    // leftLINE[--charSIZE]='\0';

    if (charSIZE>=30) {
        int targetSIZE=31;
        while (leftLINE[targetSIZE]!=' ') {
            // printf("we got [%c] at [%d] but we want a space!\n",mainLINE[targetSIZE],targetSIZE);
            targetSIZE--;
        }
        // printf("FoundTARGSize:[%d]\n",targetSIZE);
        int i=0;
        for (i=0; i<targetSIZE; i++) {
            mainLINE[i]=leftLINE[i];
            // printf("%d:[%c] VERSUS [%c]\n",i,leftLINE[i],mainLINE[i]);
        }
        mainLINE[targetSIZE]='\0';
    }   else {
        // free(leftLINE);
        mainLINE=strdup(leftLINE);
    }
// MALLOC ISSUE
    free(leftLINE);
    return mainLINE;
}


int main(int argc, char *argv[]) {
    ////////////////////////////////////////////////////////////////////////////////
    // START    ////////////////////////////////////////////////////////////////////
    FILE *in = stdin;
    FILE *out=stdout;
    
    //   CHECKING IF THERE IS AN INPUT    //////////////////////////////////////////
    if (in == NULL) {exit(1);}
    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/
    
    //   LIST OF ALL THE LINES     /////////////////////////////////////////////////
        int totalLines=0;
        node *currMAINLINE=NULL;
        node *headMAINLINE=NULL;
        char *line = (char*)emalloc(50*sizeof(char));
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, in)) != -1) {
            currMAINLINE = newNode(line,totalLines++);
            headMAINLINE = addEnd(headMAINLINE, currMAINLINE);
        } --totalLines;
        headMAINLINE = cleanThis(headMAINLINE);
        // headMAINLINE = replaceString(headMAINLINE,"2","THIS-IS-A-TEST");
        // printAll(headMAINLINE);
    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/

    //   LIST OF WORDS TO BE AVOIDED   /////////////////////////////////////////////
        int avoidedWords=0;
        node *currAVOIDEDWORDS=NULL;
        node *headAVOIDEDWORDS=NULL;
        currMAINLINE=findThis(headMAINLINE,"\'\'\'\'");
        while (findThis(currMAINLINE,"\"\"\"\"")) {
            if ((strcmp(currMAINLINE->listedString,"\"\"\"\""))&&(strcmp(currMAINLINE->listedString,"\'\'\'\'"))) {
                currAVOIDEDWORDS=newNode(currMAINLINE->listedString,avoidedWords++);
                headAVOIDEDWORDS=addEnd(headAVOIDEDWORDS, currAVOIDEDWORDS);
                currAVOIDEDWORDS=capWHOLE(currAVOIDEDWORDS, avoidedWords++);
                headAVOIDEDWORDS=addEnd(headAVOIDEDWORDS, currAVOIDEDWORDS);
            }
            currMAINLINE=currMAINLINE->next;
        } --avoidedWords;
    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/

    //   LIST OF SENTENCES TO BE WORKED UPON ///////////////////////////////////////
        int sentences=0;
        node *currSENTENCES=NULL;
        node *headSENTENCES=NULL;
        currMAINLINE=findThis(headMAINLINE,"\"\"\"\"");
        while ((currMAINLINE)!=NULL) {
            if (strcmp(currMAINLINE->listedString,"\"\"\"\"")) {
                currSENTENCES=newNode(currMAINLINE->listedString,sentences++);
                headSENTENCES=addEnd(headSENTENCES,currSENTENCES);
            }
            currMAINLINE=currMAINLINE->next;
        } --sentences;
        // printAll(headSENTENCES);
    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/

    //   LIST OF MAIN WORDS & SENTENCES SORTED    //////////////////////////////////

    node* primarySort=repeatedSentences(headAVOIDEDWORDS,headSENTENCES);
    node* headSortedWords=withoutExclusionWords(headAVOIDEDWORDS,headSENTENCES);
    headSortedWords=valSORT(sortedWords(headSortedWords));
    node* secondarySort=withoutExclusionWords(headAVOIDEDWORDS,headSENTENCES);
    secondarySort=valSORT(sortedWords(secondarySort));
    // printAll(headSortedWords);

    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/

    //   Sorting Lines by SortedWords   ////////////////////////////////////////////
    node *headSortedLines = modifiedSort (headSENTENCES,headSortedWords);
    // printAll(headSortedLines);

    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/
    freeList (headAVOIDEDWORDS);
    freeList (headSENTENCES);
    freeList (headSortedWords);
    freeList (headMAINLINE);
    freeList (currMAINLINE);

    node *currW=secondarySort;
    node *currS=headSortedLines;
    node *headList=NULL;
    node *currList=NULL;
    int iter=0;
    while (currW) {
        currList=newNode(capMAIN(currS->listedString,currW->listedString),iter++);
        headList=addEnd(headList,currList);
        currS=currS->next;
        currW=currW->next;
    }
    // printf("Listed Heads\n");
    // printAll(headList);

    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/

    char* testLineOne = "0000000001111111111222222222233333333334444444444555555555566666666667\n";
    char *testLineTwo = "1234567890123456789012345678901234567890123456789012345678901234567890\n";
    fputs(testLineOne, out);
    fputs(testLineTwo, out);
    node* curr=headList;
    while (curr) {
        char* temp = (char*)emalloc(sizeof(char));
        temp=strdup(curr->listedString);
        printf("%29s",rightLIST(temp));
        printf("%s\n",leftLIST(curr->listedString));
        curr=curr->next;
        free (temp);
    }

    /////ENDSCOPE/////////////////////////////////////////////////////////////////*/

    //   FREE ALL LISTS ////////////////////////////////////////////////////////////
    freeList (headSortedLines);
    freeList (primarySort);
    freeList (secondarySort);
    // freeList (headList);
    // freeList (currList);
    // printf("\n\n\n\t\t\\\\\\Afterwords\\\\\\\n\n\n");
    // printAll(currList);
    exit(0);
    // MAIN ENDS ///////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
}
